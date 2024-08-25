import { volumeforecastModule } from "../../productionforecast/optimizer";
import { getForecastResult } from "../forecast/reformForecastResult";
import { generateModuleVariablesMap } from "./generateModuleVariablesMap";
const merge = require("lodash/merge");

export interface IFilterChartData {
  chartData: any;
  selectedVariable: string;
  moduleNames: string[];
  paths: string[];
}

let delimeter = "@#$%";

export async function filterChartData(
  forecastResultsId: string,
  chartData: IFilterChartData["chartData"],
  selectedVariable: IFilterChartData["selectedVariable"],
  paths: IFilterChartData["paths"]
) {
  let lstWells = [];

  const moduleVariablesMap = generateModuleVariablesMap(chartData, paths);
  for (const path of paths) {
    var wellData = {
      resultWells: moduleVariablesMap[path],
    };
    lstWells.push(wellData);
  }

  const filterdPaths = paths;
  let i = 0;
  let nWells = filterdPaths.length;

  var inputOjbect = {
    wells: lstWells,
    isByYear: true,
    isForChart: true,
  };
  let result_Output = await new Promise((resolve, reject) => {
    volumeforecastModule.GetYearlyForcastResultModulesAsync(
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

  let results_Output: any[] = result_Output as [];
  let well = results_Output[0] as any;
  let table = well.resultWells as string;
  let resultWells: any[] = getForecastResult(table) as [];

  const nYears = resultWells.length;

  const xAxesData: any[] = [];
  const uniqueYears: any[] = [];
  const monthsData: any[] = [];

  let j = 0;
  for (i = 0; i < nYears; i++) {
    let xData: any = {};
    let monthData: any = {};
    let resultWells: any[] = [];
    for (j = 0; j < nWells; j++) {
      well = results_Output[j] as any;
      table = well.resultWells as string;
      resultWells = getForecastResult(table) as [];
      const rowData = resultWells[i] as any;
      if (rowData != undefined) {
        if (uniqueYears.indexOf(rowData["year"]) === -1) {
          uniqueYears.push(rowData["year"]);
        }
        xData[filterdPaths[j]] = rowData[selectedVariable];
        monthData[filterdPaths[j]] = rowData["month"];
      }
    }
    xAxesData.push(xData);
    monthsData.push(monthData);
  }

  const xAxisDataType = "date";
  return { xAxesData, uniqueYears, monthsData, xAxisDataType };
}

export async function filterChartData2(
  forecastResultsId: string,
  chartData: IFilterChartData["chartData"],
  selectedVariable: IFilterChartData["selectedVariable"],
  paths: IFilterChartData["paths"]
) {
  let lstWells = [];

  const moduleVariablesMap = generateModuleVariablesMap(chartData, paths);
  for (const path of paths) {
    var wellData = {
      resultWells: moduleVariablesMap[path],
    };
    //
    lstWells.push(wellData);
  }

  const filterdPaths = paths;
  let i = 0;
  let nWells = filterdPaths.length;

  var inputOjbect = {
    wells: lstWells,
    isByYear: true,
    isForChart: true,
  };
  let result_Output = await new Promise((resolve, reject) => {
    volumeforecastModule.GetYearlyForcastResultModulesAsync(
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

  let results_Output: any[] = result_Output as [];
  let well = results_Output[0] as any;
  let table = well.resultWells as string;
  let resultWells: any[] = getForecastResult(table) as [];

  const nYears = resultWells.length;

  const xAxesData: any[] = [];
  const uniqueYears: any[] = [];
  const monthsData: any[] = [];

  let j = 0;
  for (i = 0; i < nYears; i++) {
    let xData: any = {};
    let monthData: any = {};
    let resultWells: any[] = [];
    for (j = 0; j < nWells; j++) {
      well = results_Output[j] as any;
      table = well.resultWells as string;
      resultWells = getForecastResult(table) as [];
      const rowData = resultWells[i] as any;
      if (rowData != undefined) {
        if (uniqueYears.indexOf(rowData["year"]) === -1) {
          uniqueYears.push(rowData["year"]);
        }
        xData[filterdPaths[j]] = rowData[selectedVariable];
        monthData[filterdPaths[j]] = rowData["month"];
      }
    }
    xAxesData.push(xData);
    monthsData.push(monthData);
  }

  const xAxisDataType = "date";
  return { xAxesData, uniqueYears, monthsData, xAxisDataType };
}
