import { AnyKindOfDictionary } from 'lodash';
import { ForecastScenarioCase } from '../../models/resultModel/ForecastResult';
import {
  ReConstructFacilityModel,
  GetChartTreeModel,
  GetChartOrganizedModel,
} from '../forecast/forecastUtils';

export function Get_Tree_UniqueYear_Model(
  forecastResult: any,
  networkId: any
): any {
  let treeModel: Object[] = [];
  let uniqueYears: any = null;
  //Generate tree model
  try {
    let forecastResultPayload = forecastResult;

    let forecastResultKeys = Object.keys(forecastResultPayload);

    for (let i = 0; i < forecastResultKeys.length; i++) {
      const fcase = forecastResultKeys[i];

      let scenarioBasecase = {} as ForecastScenarioCase;
      scenarioBasecase.networkId = networkId;

      let value = forecastResultPayload[fcase];
      scenarioBasecase.facilities = ReConstructFacilityModel(value);

      let chartTreeResult = GetChartTreeModel(fcase, scenarioBasecase) as any;

      treeModel.push(chartTreeResult.tree);

      if (uniqueYears == null) {
        uniqueYears = chartTreeResult.uniqueYears;
      }
    }
  } catch (er) {
    throw er;
  }

  return { treeModel: treeModel, uniqueYears: uniqueYears };
}

export function Generate_Chart_Model(forecastResult: any, networkId: any): any {
  let chartModel = {} as any;
  //Generate tree model
  try {
    let forecastResultPayload = forecastResult;

    let forecastResultKeys = Object.keys(forecastResultPayload);

    for (let i = 0; i < forecastResultKeys.length; i++) {
      const fcase = forecastResultKeys[i];

      let scenarioBasecase = {} as ForecastScenarioCase;
      scenarioBasecase.networkId = networkId;

      let value = forecastResultPayload[fcase];
      scenarioBasecase.facilities = ReConstructFacilityModel(value);

      let chartTreeResult = GetChartOrganizedModel(
        fcase,
        scenarioBasecase
      ) as any;
      chartModel[fcase] = chartTreeResult.chart;
    }
  } catch (er) {
    throw er;
  }

  return { chartModel: chartModel };
}
