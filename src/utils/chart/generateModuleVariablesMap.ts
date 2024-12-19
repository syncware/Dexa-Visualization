import { IFilterChartData } from './filterChartData';

const get = require('lodash/get');
const objectScan = require('object-scan');

export const generateModuleVariablesMap = (
  chartData: IFilterChartData['chartData'],
  paths: IFilterChartData['paths']
) => {
  let delimeter = '@#$%';
  const modulePathVariablesMap = {} as Record<string, any[]>;

  for (const path of paths) {
    const parts = path.split(delimeter);
    const scenario = parts[0];
    const station = parts[1];
    const moduleName = parts[2];

    const selectedModulePaths = objectScan(
      [`${scenario}.${station}[*].*[*].module`],
      {
        joined: true,
        filterFn: ({ value }: any) => moduleName === value,
      }
    )(chartData);

    const moduleVariableArr = [];
    for (const modulePath of selectedModulePaths.reverse()) {
      const lastIndex = modulePath.lastIndexOf('.');
      const moduleVariablesPath = modulePath.substring(0, lastIndex);

      const moduleVariables = get(chartData, moduleVariablesPath);
      moduleVariableArr.push(moduleVariables);
    }

    modulePathVariablesMap[path] = moduleVariableArr;
  }

  return modulePathVariablesMap;
};
