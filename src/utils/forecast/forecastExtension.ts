import * as constantNames from '../../ConstantNames';
import {
  ForecastResultsByModule,
  ForecastResultsByModuleDoc,
  ForecastResultsByModuleProperties,
} from '../../models/forecastResultsByModule';
import {
  ForecastScenario,
  ForecastScenarioDoc,
  ForecastScenarioProperties,
} from '../../models/forecastScenario';
import { volumeforecastModule } from '../../productionforecast/optimizer';
import { getForecastReport, getForecastResult } from './reformForecastResult';

export interface IForecastResultCompact {
  forecastResults: object;
  forecastStringifyObject: any;
}
export interface IForecastResult {
  forecastResults: object;
}
export interface IForecastChartModel {
  forecastChartModel: object;
}

export async function GetForecastResultsByForecastId(
  forecastResultsId: string
) {
  const forecastModulesCompleteObject = await ForecastResultsByModule.find({
    forecastResultsId: forecastResultsId,
  });

  return forecastModulesCompleteObject;
}

export async function GetYearlyAggregatedForecastResults(
  forecastModulessCompleteObject: ForecastResultsByModuleDoc[]
) {
  let lstWells = [] as any[];

  for (let i = 0; i < forecastModulessCompleteObject.length; i++) {
    let forecastModuleCompleteObject = forecastModulessCompleteObject[i];
    const forecastResults =
      forecastModuleCompleteObject.forecastResults as string;

    let moduleResultMonthly = {
      resultWells: getForecastResult(forecastResults),
    };

    lstWells.push(moduleResultMonthly);
  }

  //forecastModulesPerFacility[i]
  // .forecastResults as string
  var inputOjbect = {
    wells: lstWells,
    isByYear: true,
    isForChart: false,
    nWells: lstWells.length,
  };

  const result_Output = await new Promise((resolve, reject) => {
    volumeforecastModule.GetYearlyForcastResultModulesNewAsync(
      inputOjbect,
      ModuleYearlyResult
    );
    function ModuleYearlyResult(err: any, aggregatedResult: []) {
      if (err) {
        return reject(err);
      } else {
        resolve(aggregatedResult);
      }
    }
  });

  const results_Output: any[] = result_Output as [];
  return results_Output;
}

export async function GetStructuredForecastResultsByForecastId(
  forecastModulessCompleteObject: ForecastResultsByModuleDoc[],
  scenarioNames: string[],
  solutionSpaces: string[],
  facilityNames: string[],
  isMonthly: boolean
) {
  let yearlyResults = [] as any[];
  if (isMonthly == false) {
    yearlyResults = await GetYearlyAggregatedForecastResults(
      forecastModulessCompleteObject
    );
  }

  let solutionSpacesObjects = {} as any;
  let counter = -1;
  for (let i = 0; i < solutionSpaces.length; i++) {
    let scenariosObjects = {} as any;
    for (let j = 0; j < scenarioNames.length; j++) {
      let facilitiesObjects = {} as any;
      for (let k = 0; k < facilityNames.length; k++) {
        let modulesList = forecastModulessCompleteObject.filter((x) => {
          return (
            x.solutionSpace == solutionSpaces[i] &&
            x.scenarioName == scenarioNames[j] &&
            x.facilityName == facilityNames[k]
          );
        });

        let modulesObjects = {} as any;
        for (const moduleObject of modulesList) {
          let table = '';
          let wellName = '';
          let deckObject = {} as any;
          counter++;
          if (isMonthly === false) {
            table = yearlyResults[counter].resultWells as string;

            deckObject = {
              resultWells: getForecastResult(table),
            } as any;
            wellName = moduleObject.moduleName as string;
          } else {
            table = moduleObject.forecastResults as string;

            deckObject = {
              resultWells: getForecastResult(table),
            } as any;
            wellName = moduleObject.moduleName as string;
          }
          modulesObjects[wellName] = deckObject;
        }

        facilitiesObjects[facilityNames[k]] = modulesObjects;
      }
      scenariosObjects[scenarioNames[j]] = facilitiesObjects;
    }
    solutionSpacesObjects[solutionSpaces[i]] = scenariosObjects;
  }

  return solutionSpacesObjects;
}

export function GetForecastResultsByScenario(
  forecastModulesCompleteObject: ForecastResultsByModuleDoc[],
  scenarioName: string,
  solutionSpace: string,
  facilityNames: string[]
) {
  const forecastModulesPerScenario = forecastModulesCompleteObject.filter(
    (x) => {
      return x.scenarioName == scenarioName && x.solutionSpace == solutionSpace;
    }
  );

  let i = 0;
  let j = 0;
  const nFacilities = facilityNames.length;
  const facilitiesMonthly: any = {};
  for (j = 0; j < nFacilities; j++) {
    const forecastModulesPerFacility = forecastModulesPerScenario.filter(
      (x) => {
        return x.facilityName == facilityNames[j];
      }
    );

    const nModules = forecastModulesPerFacility.length;
    const wellsMonthly: any = {};
    for (i = 0; i < nModules; i++) {
      const forecastResults = forecastModulesPerFacility[i]
        .forecastResults as string;

      const moduleResultMonthly = {
        resultWells: getForecastResult(forecastResults),
      };

      wellsMonthly[forecastModulesPerFacility[i].moduleName] =
        moduleResultMonthly;
    }
    facilitiesMonthly[facilityNames[j]] = wellsMonthly;
  }

  return facilitiesMonthly;
}

export function GetForecastResultsByScenario2(
  forecastModulesCompleteObject: ForecastResultsByModuleDoc[],
  scenarioName: string,
  solutionSpace: string,
  facilityNames: string[]
) {
  const forecastModulesPerScenario = forecastModulesCompleteObject.filter(
    (x) => {
      return x.scenarioName == scenarioName && x.solutionSpace == solutionSpace;
    }
  );

  let i = 0;
  let j = 0;
  const nFacilities = facilityNames.length;
  const facilitiesMonthly: any = {};
  for (j = 0; j < nFacilities; j++) {
    const forecastModulesPerFacility = forecastModulesPerScenario.filter(
      (x) => {
        return x.facilityName == facilityNames[j];
      }
    );

    const nModules = forecastModulesPerFacility.length;
    const wellsMonthly: any = {};
    for (i = 0; i < nModules; i++) {
      const forecastResults = forecastModulesPerFacility[i]
        .forecastResults as string;
      const moduleResultMonthly = {
        resultWells: forecastResults,
      };
      wellsMonthly[forecastModulesPerFacility[i].moduleName] =
        moduleResultMonthly;
    }
    facilitiesMonthly[facilityNames[j]] = wellsMonthly;
  }

  return facilitiesMonthly;
}

export async function GetForecastResultCompact(
  forecastResultsId: string,
  scenarioNames: string[]
): Promise<IForecastResultCompact> {
  const parseforecastResults = {} as any;
  const stringifyResultObject = {} as any;

  let k = 0;
  const scenarioCount = scenarioNames.length;
  const forecastScenariosCompleteObject = await ForecastScenario.find({
    forecastResultsId: forecastResultsId,
  }); //as ForecastScenarioProperties;
  for (k = 0; k < scenarioCount; k++) {
    const scenarioName = scenarioNames[k];
    let streamResult = '';

    const forecastScenarios = forecastScenariosCompleteObject.filter((x) => {
      return x.scenarioName == scenarioName;
    });

    forecastScenarios.forEach((x: any) => {
      streamResult = streamResult.concat(x.forecastResults.toString());
    });
    const parseObject_LightWeight = JSON.parse(`${streamResult}`);
    stringifyResultObject[scenarioName] = streamResult;

    const data = {} as any;
    data[scenarioName] = parseObject_LightWeight;
    const resultObject = getForecastReport(data);

    parseforecastResults[scenarioName] = resultObject[scenarioName];
  }

  const forecastResults = parseforecastResults;
  const result = {
    forecastResults: forecastResults,
    forecastStringifyObject: stringifyResultObject,
  } as IForecastResultCompact;

  return result;
}

function getForecastModel_Monthly(
  forecastResultsId: string,
  scenarioName: string,
  stringifyResult: string
): ForecastScenarioDoc[] {
  const forecastScenarioModelList: ForecastScenarioDoc[] = [];
  const result_json = stringifyResult;
  let currentCount = result_json.length;
  const defaultLength = 10000000; //9100000;
  let index_result = 0;

  while (true) {
    const newResult = result_json.substr(index_result, defaultLength) as Object;
    currentCount -= defaultLength;
    index_result += defaultLength;

    const forecastScenario = {} as ForecastScenarioProperties;
    forecastScenario.forecastResultsId = forecastResultsId;
    forecastScenario.scenarioName = scenarioName;
    forecastScenario.forecastResults = newResult;
    const forecastScenarioModel = ForecastScenario.build(forecastScenario);
    forecastScenarioModelList.push(forecastScenarioModel);

    if (currentCount <= 0) {
      break;
    }
  }
  return forecastScenarioModelList;
}

export async function SaveForecastResultsByModuleMonthlyData(
  forecastResultsId: string,
  forecastInputId: string,
  monthlyReport: any
) {
  const forecastModuleModelList: ForecastResultsByModuleDoc[] = [];
  const forecastCaseKeys = Object.keys(monthlyReport);
  let i = 0;
  let j = 0;
  let k = 0;
  let ii = 0;
  for (i = 0; i < forecastCaseKeys.length; i++) {
    const forecastCase = monthlyReport[forecastCaseKeys[i]];
    const scenariosKeys = Object.keys(forecastCase);

    j = 0;
    for (j = 0; j < scenariosKeys.length; j++) {
      const scenario = forecastCase[scenariosKeys[j]];
      const facilitiesKeys = Object.keys(scenario);
      k = 0;
      for (k = 0; k < facilitiesKeys.length; k++) {
        const facility = scenario[facilitiesKeys[k]];
        const wellKeys = Object.keys(facility);
        ii = 0;
        for (ii = 0; ii < wellKeys.length; ii++) {
          const well = facility[wellKeys[ii]];
          const table = well['resultWells'];
          const forecastResultsByModule =
            {} as ForecastResultsByModuleProperties;
          forecastResultsByModule.forecastResultsId = forecastResultsId;
          forecastResultsByModule.moduleName = wellKeys[ii];
          forecastResultsByModule.facilityName = facilitiesKeys[k];
          forecastResultsByModule.scenarioName = scenariosKeys[j];
          forecastResultsByModule.moduleKey = `${forecastCaseKeys[i]}/${scenariosKeys[j]}/${facilitiesKeys[k]}/${wellKeys[ii]}`;
          forecastResultsByModule.solutionSpace = forecastCaseKeys[i];
          forecastResultsByModule.forecastResults = table;
          forecastResultsByModule.forecastInputId = forecastInputId;
          const forecastModuleModel = ForecastResultsByModule.build(
            forecastResultsByModule
          );
          forecastModuleModelList.push(forecastModuleModel);
        }
      }
    }
  }

  if (forecastModuleModelList.length > 0) {
    await ForecastResultsByModule.insertMany(forecastModuleModelList);
  }

  return forecastModuleModelList;
}
