import { v4 } from 'uuid';
import * as constantNames from '../../ConstantNames';
import {
  ForecastFacility,
  ForecastResult,
  ForecastResultsByModule,
  ForecastScenarioCase,
} from '../../models/resultModel/ForecastResult';

const scenarioNames = [
  constantNames.SCENARIO_1P_1C,
  constantNames.SCENARIO_2P_2C,
  constantNames.SCENARIO_3P_3C,
];

export function GetForecastTreeview(forecastResultsByModule: any): any {
  const treeModelList: Object[] = [];
  const delimeter = '@#$%';

  const forecastSolutionSpacesNames = Object.keys(forecastResultsByModule);
  const forecastSolutionSpace_Potential =
    forecastResultsByModule[forecastSolutionSpacesNames[0]];
  const _scenarioObjectNames = Object.keys(forecastSolutionSpace_Potential);
  const scenarios = forecastSolutionSpace_Potential;
  const facilities = Object.keys(scenarios[_scenarioObjectNames[0]]) as any;
  const facilityCount = facilities.length;

  for (let index = 0; index < scenarioNames.length; index++) {
    const scenerioName = scenarioNames[index];
    const treeModel = {} as any;

    treeModel.id = v4();
    treeModel.name = scenerioName;
    treeModel.title = scenerioName;
    treeModel.children = [];
    treeModel.count = facilityCount;

    for (let i = 0; i < facilityCount; i++) {
      const facKey = facilities[i];

      const modules = Object.keys(
        scenarios[_scenarioObjectNames[0]][facKey]
      ) as any;
      const moduleCount = modules.length;

      const model = {} as any;
      model.id = v4();
      model.name = facKey;
      model.title = facKey;
      model.path = `${scenerioName}${delimeter}${facKey}`;
      model.children = [];
      model.count = moduleCount;
      treeModel.children.push(model);

      for (let k = 0; k < moduleCount; k++) {
        const modKey = modules[k];
        const model2 = {} as any;
        const modid = v4();
        model2.id = modid;
        model2.name = modKey;
        model2.title = modKey;
        model2.path = `${scenerioName}${delimeter}${facKey}${delimeter}${modKey}`;
        model.children.push(model2);
      }
    }
    treeModelList.push(treeModel);
  }

  return treeModelList;
}

export function ReConstructFacilityModel(
  forecastResultScenario: any
): ForecastFacility[] {
  const facilities: ForecastFacility[] = [];

  const forecastResultScenarioKeys = Object.keys(forecastResultScenario);

  for (let i = 0; i < forecastResultScenarioKeys.length; i++) {
    const fac = forecastResultScenarioKeys[i];

    const _facility: ForecastFacility = {} as ForecastFacility;
    _facility.title = fac;
    _facility.modules = Array<ForecastResultsByModule>();
    const value_module = forecastResultScenario[fac];
    facilities.push(_facility);

    if (Object.keys(value_module).length > 0) {
      const value_moduleKeys = Object.keys(value_module);

      for (let k = 0; k < value_moduleKeys.length; k++) {
        const mod = value_moduleKeys[k];

        const _module: ForecastResultsByModule = {} as ForecastResultsByModule;
        _module.title = mod;
        _facility.modules.push(_module);

        const value_well = value_module[mod];
        if (Object.keys(value_well).length > 0) {
          const wells = value_well['resultWells'];
          _module.forecastResults = wells as ForecastResult[];
        }
      }
    }
  }

  return facilities;
}

export function GetChartTreeModel(
  scenerioName: string,
  facScenario: ForecastScenarioCase
): object {
  facScenario.id = v4();

  const { uniqueYears } = GetModuleNamesAndDates(facScenario);

  const { treeModel } = GetForecastTreeviwModel(scenerioName, facScenario);

  const finalResult = { tree: treeModel, uniqueYears: uniqueYears };

  return finalResult;
}

export function GetChartOrganizedModel(
  scenerioName: string,
  facScenario: ForecastScenarioCase
): object {
  const facilityObj = {} as any;
  let key_dates: string[] = [];
  facScenario.id = v4();

  const { uniqueModuleNames, uniqueDates, uniqueDates_Year_Month_Day } =
    GetModuleNamesAndDates(facScenario);

  const { module_Key_Id } = GetModuleKey(scenerioName, facScenario);

  for (let i = 0; i < facScenario.facilities.length; i++) {
    const fac = facScenario.facilities[i];

    key_dates = uniqueDates;
    fac.id = v4();

    const moduleObj: object[] = [];

    for (let k = 0; k < uniqueDates.length; k++) {
      const _date = uniqueDates[k];

      const forecastingObject: object[] = [];

      for (let j = 0; j < uniqueModuleNames.length; j++) {
        const moduleName = uniqueModuleNames[j];

        var foundModule = fac.modules.find(
          (x) => x.title === moduleName
        ) as ForecastResultsByModule;
        if (foundModule != null) {
          foundModule.id = module_Key_Id[GetUniqueName(fac.title, moduleName)];
          var foundForecastResults = foundModule.forecastResults.filter(
            (x) => getDate(x) === _date
          );
          if (foundForecastResults.length > 0) {
            foundForecastResults.forEach((forecastResult) => {
              const _idd = module_Key_Id[GetUniqueName(fac.title, moduleName)]; //  module_Key_Id[moduleName];

              forecastResult.id = _idd;
              const wellObj = forecastResult as any;
              wellObj.id = forecastResult.id;
              wellObj.module = moduleName;
              forecastingObject.push(wellObj);
            });
          } else {
            // No forecastResult found
            const nonForecastResult = CloneObject(); // ({} as ForecastResult) as any;

            nonForecastResult.id =
              module_Key_Id[GetUniqueName(fac.title, moduleName)];
            nonForecastResult.module = moduleName;
            nonForecastResult.year = uniqueDates_Year_Month_Day[_date][0];
            nonForecastResult.month = uniqueDates_Year_Month_Day[_date][1];
            nonForecastResult.day = uniqueDates_Year_Month_Day[_date][2];

            nonForecastResult.APEX = 'APEX';
            forecastingObject.push(nonForecastResult);
          }
        } else {
          // No module found
          const nonForecastResult = CloneObject(); // ({} as ForecastResult) as any;

          nonForecastResult.id = v4(); // module_Key_Id[moduleName];
          nonForecastResult.module = moduleName;
          nonForecastResult.year = uniqueDates_Year_Month_Day[_date][0];
          nonForecastResult.month = uniqueDates_Year_Month_Day[_date][1];
          nonForecastResult.day = uniqueDates_Year_Month_Day[_date][2];
          nonForecastResult.module = moduleName;
          nonForecastResult.APEX = 'NO_APEX';
          forecastingObject.push(nonForecastResult);
        }
      }

      const dateResult = {} as any;
      dateResult[_date] = forecastingObject;
      moduleObj.push(dateResult);
    }

    facilityObj[fac.title] = moduleObj;
  }

  const finalResult = { chart: facilityObj };

  return finalResult;
}

function CloneObject() {
  const model = {
    oilrate: 0,
    gasRate: 0,
    waterRate: 0,
    liquidRate: 0,
    cumOilProd: 0,
    cumGasProd: 0,
    cumWaterProd: 0,
    gOR: 0,
    bSW: 0,
    cGR: 0,
    wGR: 0,
    cutBack: 0,
    hydrocarbonStream: 'gas',
    uRo: 0,
    uRg: 0,
    ownUseGas: 0,
    gasDemand: 0,
    crudeOilLossess: 0,
    cutBackRatio: 0,
    declineRate: 0,
  } as any;

  // Object.keys(sourceObject).forEach(x => {
  //     const value = sourceObject[x];

  //     if (typeof value === "number") {
  //
  //         value = 0;
  //     } else {
  //
  //     }
  //     model[x] = value;
  // })
  //
  return model;
}

function GetModuleNamesAndDates(facScenario: ForecastScenarioCase) {
  const uniqueModuleNames: string[] = [];
  const uniqueDates: string[] = [];
  const uniqueYears: number[] = [];
  const uniqueDates_Year_Month_Day = {} as any;

  let n: number = 1;
  for (let i = 0; i < facScenario.facilities.length; i++) {
    const facility = facScenario.facilities[i];

    for (let k = 0; k < facility.modules.length; k++) {
      const module = facility.modules[k];
      if (uniqueModuleNames.find((x) => x === module.title) == null) {
        uniqueModuleNames.push(module.title);
      }
      if (n == 1) {
        n++;
        for (let j = 0; j < module.forecastResults.length; j++) {
          const well = module.forecastResults[j];
          const _date = getDate(well);

          if (uniqueYears.find((x) => x === well.year) === undefined) {
            uniqueYears.push(well.year);
          }
          if (uniqueDates.find((x) => x === _date) == null) {
            uniqueDates.push(_date);
            uniqueDates_Year_Month_Day[_date] = [];
            uniqueDates_Year_Month_Day[_date][0] = well.year;
            uniqueDates_Year_Month_Day[_date][1] = well.month;
            uniqueDates_Year_Month_Day[_date][2] = well.day;
          }
        }
      }
    }
  }

  return {
    uniqueModuleNames,
    uniqueDates,
    uniqueDates_Year_Month_Day,
    uniqueYears,
  };
}

function GetUniqueName(facilityName: string, moduleName: string): string {
  return `${facilityName}-${moduleName}`;
}

function GetForecastTreeviwModel(
  scenerioName: string,
  facScenario: ForecastScenarioCase
): any {
  const treeModel = {} as any;
  const delimeter = '@#$%';

  treeModel.id = facScenario.id;
  treeModel.name = scenerioName;
  treeModel.title = scenerioName;
  treeModel.children = [];
  treeModel.count = facScenario.facilities.length;
  const module_Key_Id = {} as any;

  for (let i = 0; i < facScenario.facilities.length; i++) {
    const fac = facScenario.facilities[i];

    const model = {} as any;
    model.id = v4();
    model.name = fac.title;
    model.title = fac.title;
    model.path = `${scenerioName}${delimeter}${fac.title}`;
    model.children = [];
    model.count = fac.modules.length;
    treeModel.children.push(model);

    for (let k = 0; k < fac.modules.length; k++) {
      const mod = fac.modules[k];
      const model2 = {} as any;
      mod.id = v4();
      module_Key_Id[GetUniqueName(fac.title, mod.title)] = mod.id;
      model2.id = mod.id;
      model2.name = mod.title;
      model2.title = mod.title;
      model2.path = `${scenerioName}${delimeter}${fac.title}${delimeter}${mod.title}`;
      model.children.push(model2);
    }
  }

  return { treeModel, module_Key_Id };
}

function GetModuleKey(
  scenerioName: string,
  facScenario: ForecastScenarioCase
): any {
  const module_Key_Id = {} as any;
  for (let i = 0; i < facScenario.facilities.length; i++) {
    const fac = facScenario.facilities[i];

    fac.modules.forEach((mod) => {
      mod.id = v4();
      module_Key_Id[GetUniqueName(fac.title, mod.title)] = mod.id;
    });
  }

  return { module_Key_Id };
}

function getDate(obj: ForecastResult): string {
  return `${obj.year}-${obj.month}-${obj.day}`;
}
