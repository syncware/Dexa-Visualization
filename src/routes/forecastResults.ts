import express, { Request, Response } from 'express';
import {
  ForecastInputDeck,
  ForecastInputDeckProperties,
} from '../models/forecastInputDeck';
import {
  ForecastParameters,
  ForecastParametersProperties,
} from '../models/forecastParameters';
import {
  ForecastResults,
  ForecastResultsProperties,
} from '../models/forecastResults';
import {
  chartDataByModulesOrAggregate,
  chartDataByModulesOrAggregate2,
  getForecastResultsVariableUnits,
} from '../utils/chart/reformChartData';
import { GetForecastTreeview } from '../utils/forecast/forecastUtils';

import MergeStream from 'merge-stream';
import { Stream } from 'stream';
import { BadRequestError } from '../errors/bad-request-error';
import { Edit_Validation } from '../middlewares/edit.middleware';
import {
  ChartData_Validation,
  Data_Columns_Validation,
  Save_Forecast_Validation,
} from '../middlewares/forecast.middleware';
import { volumeforecastModule } from '../productionforecast/optimizer';
import { SuccessResponse } from '../success/successResponse';

import {
  GetEquipmentConnections,
  GetEquipmentsCapacitiesSheetData,
  GetEquipmentsCrudeLossesSheetData,
  GetEquipmentsDefermentsSheetData,
  GetEquipmentsFlaredGasSheetData,
  GetEquipmentsGasOwnUseSheetData,
  GetInternalExternalEquipmentNames,
} from '../utils/data_transform/reformNodeNames';

import * as dotenv from 'dotenv';
import { pick } from 'lodash';
import {
  ForecastProfileEntity,
  ForecastProfiles,
  ForecastProfilesProperties,
} from '../models/forecastProfiles';
import {
  RampUpDeck,
  RampUpProperties,
  RampUpScheduleEntity,
} from '../models/rampUp';
import {
  ReroutingDeck,
  ReroutingProperties,
  ReroutingScheduleEntity,
} from '../models/reRouting';
import {
  ShutinOpenupDeck,
  ShutinOpenupProperties,
  ShutinOpenupScheduleEntity,
} from '../models/shutinOpenup';
import {
  WellDeclineParameterProperties,
  WellDeclineParameters,
} from '../models/wellDeclineParameters';
import {
  ProductionPrioritizationModel,
  WellPrioritization,
  WellPrioritizationProperties
} from '../models/wellPrioritization';

import {
  EquipmentCapacitiesModelling,
  EquipmentCapacitiesProperties,
} from '../models/equipmentCapacities';

import {
  EquipmentCrudeLossesModelling,
  EquipmentCrudeLossesProperties,
} from '../models/equipmentCrudeLosses';

import {
  EquipmentDefermentsModelling,
  EquipmentDefermentsProperties,
} from '../models/equipmentDeferments';

import { FlareGasModelling, FlareGasProperties } from '../models/flareGas';

import { OwnUseGasModelling, OwnUseGasProperties } from '../models/ownUseGas';

import { SaveForecastResultsByModuleMonthlyData } from '../utils/forecast/forecastExtension';
import { ValidateForecastProfiles } from '../utils/validate-forecastPriofiles';
import { GetForecastResultHeaders } from '../utils/variable/variableUnitUtils';

import { stringify } from 'csv-stringify';
import os from 'os';
import {
  FacilitiesInput,
  FacilitiesInputProperties,
} from '../models/facilitiesInput';
import {
  FacilitiesInputDeck,
  FacilitiesInputDeckProperties,
} from '../models/facilitiesInputDeck';
import {
  ForecastInput,
  ForecastInputProperties,
} from '../models/forecastInput';
import { ForecastResultsByModule } from '../models/forecastResultsByModule';
import { getTransposedForecastReport } from '../utils/forecast/forecastResultTableTransposed';
import {
  getNodalPrioritization,
  getPrioritization,
  getProductionPrioritization,
} from '../utils/forecast/prioritizationConfiguration';
import { exportToJsonFile } from '../utils/io/exportToJsonFile';
import { importJsonFile } from '../utils/io/importJsonFile';

dotenv.config();

const forecastResultsRouter = express.Router();

// Store forecast results in variable after it is generated
let globalForecastResults = {} as Record<string, any>;

// Store forecast results by id in variable after it is generated
let globalForecastResultsById = {} as Record<string, any>;

// Store forecast results payload after forecast results is generated
let globalForecastResultsPayload = {} as Record<string, any>;
//
let forecastInputDataFileName = "files/forecast_input_data.json";
let forecastOutputDataFileName = "files/forecast_output_data.json";

forecastResultsRouter.get(
  '/forecast-result-headers',
  async (_: Request, res: Response) => {
    const result = GetForecastResultHeaders();

    res.send(SuccessResponse.Success(result));
  }
);

forecastResultsRouter.delete(
  '/:forecastResultsId/:projectId',
  async (req: Request, res: Response) => {
    const result = await ForecastResults.findByIdAndUpdate(
      req.params.forecastResultsId,
      {
        isDeleted: true,
      }
    );

    res.send(SuccessResponse.Success(result != null));
  }
);

forecastResultsRouter.get(
  '/light/:projectId',
  async (req: Request, res: Response) => {
    const projectId = req.params?.projectId;
    const item = await ForecastResults.find(
      { projectId, isDeleted: false },
      {
        title: true,
        description: true,
        networkId: true,
        networkTitle: true,
        facilitiesInputDeckTitle: true,
        forecastInputDeckTitle: true,
        forecastingParametersTitle: true,
        forecastDuration: true,
        createdAt: true,
        treeResult: true,
        saved: 'Saved',
      }
    );

    if (!item) {
      throw new BadRequestError('Forecast result is empty.');
    }

    res.send(SuccessResponse.Success(item));
  }
);

forecastResultsRouter.get(
  '/treeview/:forecastResultsId',
  async (req: Request, res: Response) => {
    const forecast = (await ForecastResults.findOne({
      _id: req.params.forecastResultsId,
      isDeleted: false,
    })) as ForecastResultsProperties;
    if (!forecast) {
      throw new BadRequestError('Forecast result is empty.');
    }

    const treesStream = Stream.Readable.from(
      `${JSON.stringify({ tree: forecast.treeResult })}\n\n`
    );

    const allStreams = MergeStream(treesStream);
    allStreams.on('error', () => {
      res.status(401).send();
    });
    allStreams.on('end', () => {
      res.status(200).send();
    });

    allStreams.pipe(res);
  }
);

// Generate forecast results
forecastResultsRouter.get(
  '/run/facilitiesInputId=:facilitiesInputId/forecastInputId=:forecastInputId/forecastParametersId=:forecastParametersId',
  async (req: Request, res: Response) => {
    //================To be taken care of by Sir Giddy on the frontend==========================//

    const forecastSolutionSpaces = [
      'potential',
      'deliverability',
      'availability',
      'offtake',
    ];

    const forecastSolutionSpacesIsDURConstrained = [
      false, 
      false, 
      false, 
      true
      ];

    //=====================================================================================//

    // Record start time for forecast run
    const forecastRunStartTime = Date.now();

    const userId = '';
    const facilitiesInputId = req.params.facilitiesInputId;
    const forecastInputId = req.params.forecastInputId;
    const forecastParametersId = req.params.forecastParametersId;

    /**
     * Facilities Input
     */
    const facilitiesInput = (await FacilitiesInput.findById(
      facilitiesInputId
    )) as FacilitiesInputProperties;
    if (!facilitiesInput) {
      throw new BadRequestError('Facilities data not found.');
    }

    const facilitiesInputDeckId =
      facilitiesInput.facilitiesInputModel?.facilitiesInputDeckOption?.id;
    const equipmentCapacitiesId =
      facilitiesInput.facilitiesInputModel?.equipmentCapacitiesOption?.id;
    const equipmentCrudeLossesId =
      facilitiesInput.facilitiesInputModel?.equipmentCrudeLossesOption?.id;
    const equipmentDefermentsId =
      facilitiesInput.facilitiesInputModel?.equipmentDefermentOption?.id;
    const flareGasId = facilitiesInput.facilitiesInputModel?.flareGasOption?.id;
    const ownUseGasId =
      facilitiesInput.facilitiesInputModel?.ownUseGasOption?.id;

    /**
     * Forecast Input
     */
    const forecastInput = (await ForecastInput.findById(
      forecastInputId
    )) as ForecastInputProperties;
    if (!forecastInput) {
      throw new BadRequestError('Forecast modules data not found.');
    }
    const forecastInputDeckId =
      forecastInput.forecastInputModel?.forecastInputDeckOption?.id;
    const rampupScheduleId =
      forecastInput.forecastInputModel?.rampupScheduleOption?.id;
    const reroutingScheduleId =
      forecastInput.forecastInputModel?.reroutingStrategyOption?.id;
    const shutinOpenupScheduleId =
      forecastInput.forecastInputModel?.shutinOpenupScheduleOption?.id;

    /**
     * Forecast parameters
     */
    const forecastParameters = (await ForecastParameters.findById(
      forecastParametersId
    )) as ForecastParametersProperties;

    if (!forecastParameters) {
      throw new BadRequestError('Forecast Parameter not found.');
    }

    try {
      /**
       * Facilties Input deck
       */
      const facilitiesInputDeck = (await FacilitiesInputDeck.findById(
        facilitiesInputDeckId
      )) as FacilitiesInputDeckProperties;
      if (!facilitiesInputDeck) {
        throw new BadRequestError('Facility Input Deck not found.');
      }

      /**
       * Forecast Input deck
       */
      const forecastInputDeck = (await ForecastInputDeck.findById(
        forecastInputDeckId
      ).lean()) as ForecastInputDeckProperties;
      if (!forecastInputDeck) {
        throw new BadRequestError('Forecast Input Deck not found.');
      }

      /**
       * Get facilites and their connections
       */
      const internalExternalFacilitiesNames = GetInternalExternalEquipmentNames(
        facilitiesInputDeck.productionEquipments as any[]
      );
      //res.send({ data: internalExternalFacilitiesNames });
      const { numberOfNodes, equipmentConnectionListUpdated } =
        GetEquipmentConnections(
          facilitiesInputDeck.inputDeckData as any[],
          internalExternalFacilitiesNames as any[]
        );
      const equipmentConnections = equipmentConnectionListUpdated as any[];

      /**
       * Equipment Capacities
       */
      const equipmentCapacitiesDeck =
        (await EquipmentCapacitiesModelling.findById(
          equipmentCapacitiesId
        )) as EquipmentCapacitiesProperties;
      if (!equipmentCapacitiesDeck) {
        throw new BadRequestError('Equipment Capacities Deck not found.');
      }
      const equipmentCapacities = GetEquipmentsCapacitiesSheetData(
        equipmentCapacitiesDeck.equipmentCapacitiesModel,
        internalExternalFacilitiesNames as any[]
      );
      /**
       * Equipment deferments
       */
      let deferments = [] as any[];
      if (equipmentDefermentsId) {
        const equipmentDefermentsDeck =
          (await EquipmentDefermentsModelling.findById(
            equipmentDefermentsId
          )) as EquipmentDefermentsProperties;
        if (equipmentCapacitiesDeck) {
          deferments = GetEquipmentsDefermentsSheetData(
            equipmentDefermentsDeck.equipmentDefermentsModel
          );
        }
      }

      /**
       * Crudelosses Schedule
       */
      let crudeOilLosses = [] as any[];
      if (equipmentCrudeLossesId) {
        const equipmentCrudeLossesDeck =
          (await EquipmentCrudeLossesModelling.findById(
            equipmentCrudeLossesId
          )) as EquipmentCrudeLossesProperties;
        if (equipmentCapacitiesDeck) {
          crudeOilLosses = GetEquipmentsCrudeLossesSheetData(
            equipmentCrudeLossesDeck.equipmentCrudeLossesModel
          );
        }
      }

      /**
       * Flared Gas
       */
      let flaredGases = [] as any[];
      if (flareGasId) {
        const equipmentFlareGasDeck = (await FlareGasModelling.findById(
          flareGasId
        )) as FlareGasProperties;
        if (equipmentFlareGasDeck) {
          flaredGases = GetEquipmentsFlaredGasSheetData(
            equipmentFlareGasDeck.flareGasModel
          );
        }
      }

      /**
       * Gas Own Use
       */
      let gasOwnUse = [] as any[];
      if (ownUseGasId) {
        const equipmentOwnUseGasDeck = (await OwnUseGasModelling.findById(
          ownUseGasId
        )) as OwnUseGasProperties;
        if (equipmentOwnUseGasDeck) {
          gasOwnUse = GetEquipmentsGasOwnUseSheetData(
            equipmentOwnUseGasDeck.ownUseGasModel
          );
        }
      }

      /**
       * Rampup Schedule
       */
      let rampUpSchedules = [] as RampUpScheduleEntity[];
      if (rampupScheduleId) {
        const rampUpInputDeck = (await RampUpDeck.findById(
          rampupScheduleId
        )) as RampUpProperties;
        if (rampUpInputDeck) {
          rampUpSchedules = rampUpInputDeck.rampupModel.schedule;
        }
      }

      /**
       * Rerouting Schedule
       */
      let reroutingSchedules = [] as ReroutingScheduleEntity[];
      if (reroutingScheduleId) {
        const reroutingInputDeck = (await ReroutingDeck.findById(
          reroutingScheduleId
        )) as ReroutingProperties;
        if (reroutingInputDeck) {
          reroutingSchedules = reroutingInputDeck.reroutingModel.schedule;
        }
      }

      /**
       * Shutin/Open-up Schedule
       */
      let shutinOpenUpSchedules = [] as ShutinOpenupScheduleEntity[];
      if (shutinOpenupScheduleId) {
        const shutinOpenupInputDeck = (await ShutinOpenupDeck.findById(
          shutinOpenupScheduleId
        )) as ShutinOpenupProperties;
        if (shutinOpenupInputDeck) {
          shutinOpenUpSchedules =
            shutinOpenupInputDeck.shutinOpenupModel.schedule;
        }
      }

      /**
       * Prioritization
       */
      const wellPrioritizationId = forecastParameters.wellPrioritizationId;
      const declineParametersId = forecastParameters.declineParametersId;
      let isForecastProfiles = forecastParameters.isForecastProfiles;
      const forecastProfilesId = forecastParameters.forecastProfilesId;

      const startDate = new Date(
        forecastParameters.parametersEntity.startYear,
        forecastParameters.parametersEntity.startMonth,
        forecastParameters.parametersEntity.startDay
      );
      const stopDate = new Date(
        forecastParameters.parametersEntity.stopYear,
        forecastParameters.parametersEntity.stopMonth,
        forecastParameters.parametersEntity.stopDay
      );

      /**
       * Forecast Duration
       */
      const forecastExpectedRunDuration =
        Number(process.env.FORECAST_RUN_DURATION) || 30;
      const diff = stopDate.getTime() - startDate.getTime();
      const forecastDuration = Number((diff / 31536000000).toFixed(0));

      if (forecastDuration > forecastExpectedRunDuration) {
        throw new BadRequestError(
          'Forecast duration must not be greater than 50 years.'
        );
      }

      /**
       * Use Forecast Input deck or Forecast profiles
       */
      let wellPrioritization = (await WellPrioritization.findById(
        wellPrioritizationId
      ).lean()) as WellPrioritizationProperties;

      const wellDeclineParameters = (await WellDeclineParameters.findById(
        declineParametersId
      )) as WellDeclineParameterProperties;

      let forecastProfiles = {} as ForecastProfilesProperties;

      if (
        isForecastProfiles == 'internal' ||
        !forecastProfilesId ||
        !isForecastProfiles ||
        !forecastProfilesId
      ) {
        isForecastProfiles = 'internal';
        forecastProfiles.inputDeckData = [] as ForecastProfileEntity[];
      } else {
        forecastProfiles = (await ForecastProfiles.findById(
          forecastProfilesId
        )) as ForecastProfilesProperties;

        if (!forecastProfiles) {
          throw new BadRequestError('Forecast Profiles not found.');
        }

        const validateProfiles: any = ValidateForecastProfiles(
          forecastProfiles.inputDeckData,
          forecastInputDeck.inputDeckData
        );
        forecastProfiles.inputDeckData =
          validateProfiles.forecastProfiles as ForecastProfileEntity[];
        if (!validateProfiles.checkModuleNames) {
          throw new BadRequestError(
            'Forecast profiles module names do not match with forecast input deck module names.'
          );
        }

        if (!validateProfiles.checkHydrocarbonStreams) {
          throw new BadRequestError(
            'Forecast profiles hydrocarbon streams do not match with forecast input deck hydrocarbon streams.'
          );
        }
      }

      let productionPrioritizationModel = {} as ProductionPrioritizationModel;

      if (wellPrioritization) {
        productionPrioritizationModel =
          wellPrioritization.productionPrioritizationModel;
      } else {
        throw new BadRequestError('Well prioritization can not be empty.');
      }

      if (!wellDeclineParameters) {
        throw new BadRequestError('Well Decline Paramete not found.');
      }

      const forecastingParameterModel = forecastParameters;
      const productionPrioritization = getProductionPrioritization(
        productionPrioritizationModel
      );
      const prioritization = getPrioritization(productionPrioritizationModel);
      const nodalPriotizations = getNodalPrioritization(
        productionPrioritizationModel
      );

      for (let i = 0; i < forecastInputDeck.inputDeckData.length; i++) {
        forecastInputDeck.inputDeckData[i].forecastVersion =
          wellDeclineParameters.declineParameters?.[i]?.forecastVersion;
        forecastInputDeck.inputDeckData[i].asset =
          wellDeclineParameters.declineParameters?.[i]?.asset;
        forecastInputDeck.inputDeckData[i].field =
          wellDeclineParameters.declineParameters?.[i]?.field;
        forecastInputDeck.inputDeckData[i].reservoir =
          wellDeclineParameters.declineParameters?.[i]?.reservoir;
        forecastInputDeck.inputDeckData[i].drainagePoint =
          wellDeclineParameters.declineParameters?.[i]?.drainagePoint;
        forecastInputDeck.inputDeckData[i].string =
          wellDeclineParameters.declineParameters?.[i]?.string;
        forecastInputDeck.inputDeckData[i].module =
          wellDeclineParameters.declineParameters?.[i]?.module;
        forecastInputDeck.inputDeckData[i].initOilGasRate1P1C =
          wellDeclineParameters.declineParameters?.[i]?.initOilGasRate1P1C;
        forecastInputDeck.inputDeckData[i].initOilGasRate2P2C =
          wellDeclineParameters.declineParameters?.[i]?.initOilGasRate2P2C;
        forecastInputDeck.inputDeckData[i].initOilGasRate3P3C =
          wellDeclineParameters.declineParameters?.[i]?.initOilGasRate3P3C;
        forecastInputDeck.inputDeckData[i].rateofChangeRate1P1C =
          wellDeclineParameters.declineParameters?.[i]?.rateofChangeRate1P1C;
        forecastInputDeck.inputDeckData[i].rateofChangeRate2P2C =
          wellDeclineParameters.declineParameters?.[i]?.rateofChangeRate2P2C;
        forecastInputDeck.inputDeckData[i].rateofChangeRate3P3C =
          wellDeclineParameters.declineParameters?.[i]?.rateofChangeRate3P3C;
        forecastInputDeck.inputDeckData[i].declineExponent1P1C =
          wellDeclineParameters.declineParameters?.[i]?.declineExponent1P1C;
        forecastInputDeck.inputDeckData[i].declineExponent2P2C =
          wellDeclineParameters.declineParameters?.[i]?.declineExponent2P2C;
        forecastInputDeck.inputDeckData[i].declineExponent3P3C =
          wellDeclineParameters.declineParameters?.[i]?.declineExponent3P3C;
        forecastInputDeck.inputDeckData[i].declineMethod =
          wellDeclineParameters.declineParameters?.[i]?.declineMethod;

        forecastInputDeck.inputDeckData[i].rateOfChangeGORCGR1P1C =
          wellDeclineParameters.declineParameters?.[i]?.rateOfChangeGORCGR1P1C;
        forecastInputDeck.inputDeckData[i].rateOfChangeGORCGR2P2C =
          wellDeclineParameters.declineParameters?.[i]?.rateOfChangeGORCGR2P2C;
        forecastInputDeck.inputDeckData[i].rateOfChangeGORCGR3P3C =
          wellDeclineParameters.declineParameters?.[i]?.rateOfChangeGORCGR3P3C;
        forecastInputDeck.inputDeckData[i].rateOfChangeBSWWGR1P1C =
          wellDeclineParameters.declineParameters?.[i]?.rateOfChangeBSWWGR1P1C;
        forecastInputDeck.inputDeckData[i].rateOfChangeBSWWGR2P2C =
          wellDeclineParameters.declineParameters?.[i]?.rateOfChangeBSWWGR2P2C;
        forecastInputDeck.inputDeckData[i].rateOfChangeBSWWGR3P3C =
          wellDeclineParameters.declineParameters?.[i]?.rateOfChangeBSWWGR3P3C;
      }

      // Forecast Run parameters
      var inputData = {
        decks: forecastInputDeck.inputDeckData,
        facilities: facilitiesInputDeck.inputDeckData,
        runparameters: forecastingParameterModel.parametersEntity,
        productionPrioritization,
        prioritization,
        nodalPriotizations,
        nNodalPriotizations: nodalPriotizations.length,
        forecastProfiles: forecastProfiles.inputDeckData,
        isForecastProfiles,
        nDecks: forecastInputDeck.inputDeckData.length,
        nProductionPrioritization: productionPrioritization.length,
        nFacilities: facilitiesInputDeck.inputDeckData.length,
        nForecastProfiles: forecastProfiles.inputDeckData.length,
        wellRerouteDecks: reroutingSchedules,
        nWellRerouteDecks: reroutingSchedules.length,
        wellRampUpDecks: rampUpSchedules,
        nWellRampUpDecks: rampUpSchedules.length,
        wellShutInOpenUpDecks: shutinOpenUpSchedules,
        nWellShutInOpenUpDecks: shutinOpenUpSchedules.length,
        internalExternalFacilitiesNames,
        nInternalExternalFacilitiesNames:
          internalExternalFacilitiesNames.length,
        equipmentConnections,
        nEquipmentConnections: equipmentConnections.length,
        deferments,
        nDeferments: deferments.length,
        crudeOilLosses,
        nCrudeOilLosses: crudeOilLosses.length,
        equipmentCapacities,
        nEquipmentCapacities: equipmentCapacities.length,
        numberOfNodes,
        gasOwnUse,
        nGasOwnUse: gasOwnUse.length,
        flaredGases,
        nFlaredGases: flaredGases.length,
        forecastSolutionSpaces,
        nForecastSolutionSpaces: forecastSolutionSpaces.length,
        forecastSolutionSpacesIsDURConstrained,
        nForecastSolutionSpacesIsDURConstrained:
          forecastSolutionSpacesIsDURConstrained.length
      }

      var payload = {
        "payload" : inputData
      }

      await exportToJsonFile(payload, forecastInputDataFileName);

      // Run Forecast
      const _runForecastResults = await new Promise((resolve, reject) => {
        volumeforecastModule.runForecastAsync(
          inputData,
          runForecastAsyncWorkerCompletion
        );
        async function runForecastAsyncWorkerCompletion(
          err1: any,
          runForecastResult: any
        ) {
          if (err1) {
            return reject(err1);
          } else {
            resolve(runForecastResult);
          }
        }
      });

      // Store forecast results payload
      const forecastResultsPayload = {
        userId,
        facilitiesInputId: facilitiesInputId,
        forecastInputId: forecastInputId,
        forecastParametersId: forecastParametersId,
        facilitiesInputTitle: facilitiesInput.title,
        forecastInputTitle: forecastInput.title,
        forecastingParametersTitle: forecastParameters.title,
      } as ForecastResultsProperties;
      globalForecastResultsPayload = forecastResultsPayload;

      // Store forecast results in static variable pending save operation
      globalForecastResults = _runForecastResults as any;

      // Add run-time statistics
      const forecastRunEndTime = Date.now();
      const forecastRunTimeDuration = forecastRunEndTime - forecastRunStartTime;

      // Gather system information
      const resourceUsage = process.resourceUsage();
      const operatingSystem = os.type();
      const usedRAM = resourceUsage.maxRSS;
      const cpus = os.cpus();
      const numberOfCPUs = cpus.length;
      const cpuSpeed = cpus[0].speed; // Assuming all CPUs have the same speed
      const memoryUsage = process.memoryUsage();
      const maxPhysicalMemoryUsedPerCore = memoryUsage.rss / numberOfCPUs;
      const runTimeStatistics = {
        operatingSystem,
        numberOfCPUs,
        cpuSpeed,
        maxPhysicalMemoryUsedPerCore,
        usedRAM,
        forecastRunTimeDuration,
      };
      globalForecastResults.runTimeStatistics = runTimeStatistics;

      res.send(
        SuccessResponse.Success({ status: 'success', runTimeStatistics })
      );
    } catch (er) {
      throw er;
    }
  }
);

// Save forecast results
forecastResultsRouter.get(
  '/save/projectId=:projectId/title=:title/description=:description',
  Save_Forecast_Validation,
  async (req: Request, res: Response) => {
    const projectId = req.params?.projectId;
    const title = req.params?.title;
    const description = req.params?.description;

    const forecastResultsPayload = {
      projectId,
      title,
      description,
      ...globalForecastResultsPayload,
      userId: 'gideon',
    } as ForecastResultsProperties;
    const forecastResultsModel = ForecastResults.build(forecastResultsPayload);

    // Compute Forecast Results Tree
    const monthlyForecastResults = globalForecastResults.monthlyReport;
    const treeModel = GetForecastTreeview(monthlyForecastResults);
    forecastResultsModel.treeResult = {
      treeModel,
    };

    // Save forecast results payload to Db
    const forecastResponse = await forecastResultsModel.save();

    // Save monthly forecast results by module to Db
    // Results can be returned monthly to ui or aggregated
    // by year. Also save to memory using forecastResultsId as a key
    if (!!forecastResponse) {
      const forecastResultsId = (forecastResponse as any)._id;
      const forecastInputId = globalForecastResultsPayload.forecastInputId;
      const forecastResultsByModule =
        await SaveForecastResultsByModuleMonthlyData(
          forecastResultsId,
          forecastInputId,
          monthlyForecastResults
        );
      globalForecastResultsById[forecastResultsId] = forecastResultsByModule;
    }

    /**
     * Return Forecast Results Tree stream to UI
     */
    const treesStream = Stream.Readable.from(
      `${JSON.stringify({ tree: treeModel })}\n\n`
    );
    const allStreams = MergeStream(treesStream);

    allStreams.on('error', () => {
      res.status(401).send();
    });
    allStreams.on('end', () => {
      res.status(200).send();
    });

    allStreams.pipe(res);
  }
);

// Save forecast results
forecastResultsRouter.post(
  '/save-json',
  async (req: Request, res: Response) => {

    const {
      projectId,
      title,
      description,
      userId,
      facilitiesInputId,
      forecastInputId,
      forecastParametersId,
      facilitiesInputTitle,
      forecastInputTitle,
      forecastingParametersTitle
    } = req.body;

    const forecastResultsPayload = {
      projectId,
      title,
      description,
      userId,
      facilitiesInputId,
      forecastInputId,
      forecastParametersId,
      facilitiesInputTitle,
      forecastInputTitle,
      forecastingParametersTitle
    } as ForecastResultsProperties;

    
    const forecastResultsModel = ForecastResults.build(forecastResultsPayload);

    // Compute Forecast Results Tree
    const localforecastResults = await importJsonFile(forecastOutputDataFileName);
    const monthlyForecastResults = localforecastResults.monthlyReport;
    const treeModel = GetForecastTreeview(monthlyForecastResults);
    forecastResultsModel.treeResult = {
      treeModel,
    };

    // Save forecast results payload to Db
    const forecastResponse = await forecastResultsModel.save();

    // Save monthly forecast results by module to Db
    // Results can be returned monthly to ui or aggregated
    // by year. Also save to memory using forecastResultsId as a key
    if (!!forecastResponse) {
      const forecastResultsId = (forecastResponse as any)._id.toString();
      const forecastResultsByModule =
        await SaveForecastResultsByModuleMonthlyData(
          forecastResultsId,
          forecastInputId,
          monthlyForecastResults
        );
    }

    /**
     * Return Forecast Results Tree stream to UI
     */
    const treesStream = Stream.Readable.from(
      `${JSON.stringify({ tree: treeModel })}\n\n`
    );
    const allStreams = MergeStream(treesStream);

    allStreams.on('error', () => {
      res.status(401).send();
    });
    allStreams.on('end', () => {
      res.status(200).send();
    });

    allStreams.pipe(res);
  }
);

// Visualize Forecast Results
forecastResultsRouter.post(
  '/chart-data',
  ChartData_Validation,
  async (req: Request, res: Response) => {
    // const userId = "FG";
    const forecastResultsIds = req.body.forecastResultsIds as string[];
    const selectedModulePaths = req.body.selectedModulePaths;
    const selectedVariables = req.body.selectedVariables;
    const shouldAggregate = req.body.shouldAggregate;
    const forecastSolutionSpaces = req.body.forecastSolutionSpaces;
    const isMonthly = false;
    const forecastResultsId = forecastResultsIds[0];

    if (selectedModulePaths?.length === 0) {
      res.send({ data: {} });
    }

    let i = 1;
    let resultMap = {} as Record<string, any>;
    for (const forecastResultsId of forecastResultsIds) {
      try {
        const forecast = (await ForecastResults.findById(
          forecastResultsId
        )) as ForecastResultsProperties;
        if (!forecast) {
          throw new BadRequestError('Forecast result is empty in chartData.');
        }

        // Get the forecast results from the global map
        // or fetch from db and store in gobal map if not yet stored
        let forecastResultsByModule =
          globalForecastResultsById?.[forecastResultsId];
        if (!forecastResultsByModule) {
          const forecastResults = await ForecastResultsByModule.find({
            forecastResultsId,
          }).lean();
          globalForecastResultsById[forecastResultsId] = forecastResults;
          forecastResultsByModule = forecastResults;
        } 

        // Get chart data
        // TODO: Gabriel also return an object with variable as key and unit as value
        // like this: {oilRate: bbl/d, condensateRate: bbl/d, gasRate: MMscf/d, etc}


        const inputData = {
          forecastResults: forecastResultsByModule,
          chatInputData: {
            selectedModulePaths,
            selectedVariables,
            isMonthly,
            forecastSolutionSpaces,
            forecastResultsIds,
            shouldAggregate
          }
        }

        const result = await new Promise((resolve, reject) => {
          volumeforecastModule.plotChartAsync(
            inputData,
            plotChartAsynccWorkerCompletion
          );
          async function plotChartAsynccWorkerCompletion(
            err1: any,
            plotChatResult: any
          ) {
            if (err1) {
              return reject(err1);
            } else {
              resolve(plotChatResult);
            }
          }
        }); 

        // Reset forecastResultsByModule to free memory
        forecastResultsByModule = {} 

        // Add result to resultMap
        resultMap[String(i)] = result;

        i += 1;
      } catch (err) {
        throw new BadRequestError('Error in filtering forecast chart data');
      }
    }
    const units = getForecastResultsVariableUnits(selectedVariables);
    res.send({ data: resultMap, units });
  }
);

forecastResultsRouter.put(
  '/:forecastResultsId',
  Edit_Validation,
  async (req: Request, res: Response) => {
    const forecastResultsId = req.params.forecastResultsId;
    const { title, description, projectId } = req.body;

    const foundAssets = await ForecastResults.find({
      title: title,
      projectId: projectId,
    });

    const foundItem = foundAssets.find((x) => x.id != forecastResultsId);
    if (foundItem) {
      throw new BadRequestError('Title already exists.');
    }

    const update = { title: title, description: description };
    const result = await ForecastResults.findByIdAndUpdate(
      { _id: forecastResultsId },
      update
    );

    res.send(SuccessResponse.Success(result));
  }
);

forecastResultsRouter.get(
  '/forecast-input-deck/data-columns',
  Data_Columns_Validation,
  async (req: Request, res: Response) => {
    const forecastInputDeckId = req.body.forecastInputDeckId;
    const dataColumns = req.body.dataColumns;
    const forecastInputDeck = (await ForecastInputDeck.findById(
      forecastInputDeckId
    )) as ForecastInputDeckProperties;

    if (forecastInputDeck == null) {
      throw new BadRequestError('Forecast Input Deck not found.');
    }

    const filteredResult = forecastInputDeck.inputDeckData.reduce(
      (acc, row) => {
        const filteredRow = pick(row, dataColumns) as Record<
          string,
          string | number
        >;
        acc.push(filteredRow);
        return acc;
      },
      [] as Record<string, string | number>[]
    );

    res.send(SuccessResponse.Success({ data: filteredResult }));
  }
);

// Display forecast results on table
forecastResultsRouter.get(
  '/forecast-report/*',
  async (req: Request, res: Response) => {
    const isMonthly = false;

    const params = req.params[0]?.split('/');
    const forecastResultsId = params[0];
    const page = parseInt(params[1]) || 1;
    const limit = parseInt(params[2]) || 50;
    const startIndex = (page - 1) * limit;

    let forecastResultsByForecastId =
      globalForecastResultsById?.[forecastResultsId];
    let totalCount = forecastResultsByForecastId?.length;

    if (!forecastResultsByForecastId) {
      forecastResultsByForecastId = await ForecastResultsByModule.find({
        forecastResultsId,
      });
      totalCount = await ForecastResultsByModule.countDocuments();
    }

    const transposedResult = await getTransposedForecastReport(
      forecastResultsByForecastId,
      isMonthly
    );
    
    const pagedForecastResultsById = transposedResult.slice(startIndex, limit);

    res.send(
      SuccessResponse.Success({
        // data: [{ a: 1, b: 2 }],
        data: pagedForecastResultsById,
        // data: transposedResult,
        meta: { totalCount },
      })
    );
  }
);

// Download forecast result
forecastResultsRouter.get(
  '/download-forecast-report/*',
  async (req: Request, res: Response) => {
    const params = req.params[0]?.split('/');
    const forecastResultsId = params[0];

    const forecastResultsByModule = await ForecastResultsByModule.find({
      forecastResultsId,
    });

    const monthlyReport = await chartDataByModulesOrAggregate2(
      forecastResultsByModule
    );

    // Set the headers for the response to indicate a file attachment
    res.setHeader('Content-Type', 'text/csv');
    res.setHeader(
      'Content-Disposition',
      'attachment; filename=forecast-results.csv'
    );

    // Use csv-stringify to convert data to CSV
    stringify(monthlyReport, { header: true }, (err, output) => {
      if (err) {
        return res.status(500).send('Error generating CSV');
      }

      // Send the CSV content in the response
      res.send(
        SuccessResponse.Success({
          data: output,
        })
      );
    });
  }
);

export { forecastResultsRouter };