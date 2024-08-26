import { set, sum, zip } from 'lodash';
import { volumeforecastModule } from '../../productionforecast/optimizer';
import {
  GetForecastResultsByScenario,
  GetForecastResultsByScenario2,
} from '../forecast/forecastExtension';
import { getForecastResult } from '../forecast/reformForecastResult';
import { 
  forecastResultsVariableUnits
 } from "../../utils/constants/wellsDeckBaseUnits";
import { exportToJsonFile } from '../io/exportToJsonFile';
import { importJsonFile, importJsonFile2 } from '../io/importJsonFile';

const delimeter = '@#$%';
const forecastChatInputDataFileName = "forecast_chat_data_input.json";
const forecastOutputDataFileName = "forecast_chat_data_output.json";

function GetScenarioNames(selectedModulePaths: string[]): string[] {
  const scenarioNames: string[] = [];
  for (const path of selectedModulePaths) {
    const parts = path.split(delimeter);
    const scenario = parts[0];
    if (scenarioNames.findIndex((x) => x == scenario) < 0) {
      scenarioNames.push(scenario);
    }
  }
  return scenarioNames;
}

function GetFacilityNames(selectedModulePaths: string[]): string[] {
  const facilityNames: string[] = [];
  for (const path of selectedModulePaths) {
    const parts = path.split(delimeter);
    const facility = parts[1];
    if (facilityNames.findIndex((x) => x == facility) < 0) {
      facilityNames.push(facility);
    }
  }
  return facilityNames;
}

export function getForecastResultsVariableUnits(selectedVariables: string[]) {
  const units = {} as any;
  for(const selectedVariable of selectedVariables){
    let forecastResultsVariableUnit = selectedVariable as any;
    units[forecastResultsVariableUnit] = forecastResultsVariableUnits[forecastResultsVariableUnit];
  }
  return units;
}

export async function chartDataByModulesOrAggregate(
  selectedModulePaths: string[],
  selectedVariables: string[],
  isMonthly: boolean,
  forecastSolutionSpaceNames: string[],
  forecastResultsByModule: any,
  forecastResultsId: string,
  shouldAggregate: boolean
) {
  const scenarioNames = GetScenarioNames(selectedModulePaths);
  const facilityNames = GetFacilityNames(selectedModulePaths);
  const solutionCase_ForecastResult = {} as any;

  for (let index2 = 0; index2 < forecastSolutionSpaceNames.length; index2++) {
    const forecastSolutionSpaceName = forecastSolutionSpaceNames[index2];
    for (let index = 0; index < scenarioNames.length; index++) {
      const _scenarioName = scenarioNames[index];

      const case_scenario_Name = (
        forecastSolutionSpaceName + _scenarioName
      ).toUpperCase();

      const iforecastResult = GetForecastResultsByScenario(
        forecastResultsByModule,
        _scenarioName,
        forecastSolutionSpaceName,
        facilityNames
      );
      solutionCase_ForecastResult[case_scenario_Name] = iforecastResult;
    }
  }

  const lstWellsObject = {} as any;
  for (const forecastSolutionSpaceName of forecastSolutionSpaceNames) {
    const lstWells = [];
    for (const path of selectedModulePaths) {
      const parts = path.split(delimeter);
      const scenario = parts[0] as string;
      const station = parts[1];
      const moduleName = parts[2];
      const case_senario_name = forecastSolutionSpaceName + scenario;
      const scenarioResult =
        solutionCase_ForecastResult[case_senario_name.toUpperCase()];
      const facilitiesResult = scenarioResult[station];
      const moduleNameResult = facilitiesResult[moduleName];

      if (moduleNameResult) {
        lstWells.push(moduleNameResult);
      }
    }
    lstWellsObject[forecastSolutionSpaceName] = lstWells;
  }

  const results_OutputObject = {} as any;
  const lstWellsObjectKeys = Object.keys(lstWellsObject);
  for (let index = 0; index < lstWellsObjectKeys.length; index++) {
    const lstWells = lstWellsObject[lstWellsObjectKeys[index]] as any[];
    var inputOjbect = {
      wells: lstWells,
      isByYear: !isMonthly,
      isForChart: false,
      nWells: lstWells.length,
    };

    //await exportToJsonFile(inputOjbect, forecastChatInputDataFileName);

    /* const result_Output = await new Promise((resolve, reject) => {
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
    */

    //======================For Debugging=====================//

    const result_Output = await importJsonFile(forecastOutputDataFileName);
    const results_Output = Object.keys(result_Output["response"]).map((chatRowKey:any) => {
      return {...result_Output["response"][chatRowKey]}
    });

    results_OutputObject[lstWellsObjectKeys[index]] = results_Output;
  }

  const res2 = {} as any;

  const results_OutputObjectKeys = Object.keys(results_OutputObject);
  for (let index = 0; index < results_OutputObjectKeys.length; index++) {
    const results_Output = results_OutputObject[
      results_OutputObjectKeys[index]
    ] as any[];
    let well = results_Output[0] as any;
    let table = well.resultWells as string;
    const nWells = selectedModulePaths.length;
    let i = 0;
    let j = 0;
    const outputData: any[] = [];

    for (j = 0; j < nWells; j++) {
      well = results_Output[j] as any;
      table = well.resultWells as string;
      const resultWells = getForecastResult(table) as [];
      const yObjs = {} as any;
      for (let k = 0; k < selectedVariables.length; k++) {
        const nTimes = resultWells.length;
        const x = [] as any[];
        const y = [] as any[];
        let uniqueId = '';
        let moduleN = '';
        for (i = 0; i < nTimes; i++) {
          const rowData = resultWells[i] as any;
          uniqueId = rowData.uniqueId;
          moduleN = rowData.module;
          y.push(rowData[selectedVariables[k]]);
          const day = rowData.day as number;
          const month = rowData.month as number;
          const year = rowData.year as number;
          x.push(new Date(year, month, day));
        }

        const yObj = {
          forecastResultId: forecastResultsId,
          id: uniqueId,
          name: moduleN,
          title: moduleN,
          path: selectedModulePaths[j],
          y,
          x,
        } as any;
        yObjs[selectedVariables[k]] = yObj;
      }
      outputData.push(yObjs);
    }

    const res = {
      '1P_1C': {},
      '2P_2C': {},
      '3P_3C': {},
    } as any;

    for (let k = 0; k < selectedVariables.length; k++) {
      res['1P_1C'][selectedVariables[k]] = [];
      res['2P_2C'][selectedVariables[k]] = [];
      res['3P_3C'][selectedVariables[k]] = [];
    }

    for (i = 0; i < outputData.length; i++) {
      for (let k = 0; k < selectedVariables.length; k++) {
        if (outputData[i][selectedVariables[k]].path.includes('1P_1C')) {
          res['1P_1C'][selectedVariables[k]].push(
            outputData[i][selectedVariables[k]]
          );
        }

        if (outputData[i][selectedVariables[k]].path.includes('2P_2C')) {
          res['2P_2C'][selectedVariables[k]].push(
            outputData[i][selectedVariables[k]]
          );
        }

        if (outputData[i][selectedVariables[k]].path.includes('3P_3C')) {
          res['3P_3C'][selectedVariables[k]].push(
            outputData[i][selectedVariables[k]]
          );
        }
      }
    }
    res2[results_OutputObjectKeys[index]] = res;
  }

  const _scenarioObjects = {
    '1P_1C': {},
    '2P_2C': {},
    '3P_3C': {},
  } as any;

  const res2Keys = Object.keys(res2);

  for (let index2 = 0; index2 < res2Keys.length; index2++) {
    const solutionCaseObject = res2[res2Keys[index2]];
    _scenarioObjects['1P_1C'][res2Keys[index2]] = solutionCaseObject['1P_1C'];
    _scenarioObjects['2P_2C'][res2Keys[index2]] = solutionCaseObject['2P_2C'];
    _scenarioObjects['3P_3C'][res2Keys[index2]] = solutionCaseObject['3P_3C'];
  }

  // Aggregate if shouldAggregate === true
  let aggregatedScenarioObjects = {};
  if (shouldAggregate) {
    for (const forecastCase in _scenarioObjects) {
      const forecastCaseMap = _scenarioObjects[forecastCase];
      for (const solutionCase in forecastCaseMap) {
        const solutionCaseMap = forecastCaseMap[solutionCase];
        for (const forecastVariable in solutionCaseMap) {
          const forecastVariableArray = solutionCaseMap[forecastVariable];
          const x = forecastVariableArray?.[0]?.x;
          const yAgg = aggregateY(
            forecastVariableArray.map((row: any) => row.y)
          );

          // TODO: Gabriel - change forecastResultId to forecastResultsId
          const pathWithDelimeter = `${forecastCase}@#$%${solutionCase}@#$%${forecastVariable}`;
          const path = `${forecastCase}.${solutionCase}.${forecastVariable}`;
          const data = {
            forecastResultsId,
            id: pathWithDelimeter,
            name: pathWithDelimeter,
            title: pathWithDelimeter,
            path: pathWithDelimeter,
            y: yAgg,
            x,
          };

          // Set data in aggregatedScenarioObjects
          set(aggregatedScenarioObjects, path, data);
        }
      }
    }
  }

  return shouldAggregate ? aggregatedScenarioObjects : _scenarioObjects;
}

const aggregateY = (forecastVariableArray: number[][]) => {
  return zip(...forecastVariableArray).map((group) => sum(group));
};

export async function chartDataByModulesOrAggregate2(
  forecastResultsByModule: any
) {
  const scenarioNames = ['1P_1C', '2P_2C', '3P_3C'];
  const solutionCase_ForecastResult = {} as any;

  const forecastSolutionSpaceNames = [
    'potential',
    'deliverability',
    'availability',
    'offtake',
  ] as string[];

  const facilityNames = [
    'ABU_FS1',
    'ABU_FS2',
    'ABU_FS3',
    'ABU_FS4',
    'ABU_FS5',
    'ABU_FS6',
    'ABU_FS7',
    'REO_GP1',
    'REO_GP2',
    'REO_GP3',
    'REO_GP4',
    'REO_GP5',
  ];

  for (let index2 = 0; index2 < forecastSolutionSpaceNames.length; index2++) {
    const forecastSolutionSpaceName = forecastSolutionSpaceNames[index2];
    let scenarios = {} as any;
    for (let index = 0; index < scenarioNames.length; index++) {
      const _scenarioName = scenarioNames[index];

      const iforecastResult = GetForecastResultsByScenario2(
        forecastResultsByModule,
        _scenarioName,
        forecastSolutionSpaceName,
        facilityNames
      );
      scenarios[_scenarioName] = iforecastResult;
    }
    solutionCase_ForecastResult[forecastSolutionSpaceName] = { ...scenarios };
  }

  return solutionCase_ForecastResult;
}
