import { GetStructuredForecastResultsByForecastId } from './forecastExtension';

const oil_rate_column_index = 13;
const cum_days_column_index = 37;
const optimal_solution_column_index = 38;
const all_wells_liquid_capacity_column_index = 39;
const all_wells_gas_capacity_column_index = 40;
const gas_rate_column_index = 14;
const water_rate_column_index = 15;
const liquid_rate_column_index = 16;
const cum_oil_prod_column_index = 17;
const cum_gas_prod_column_index = 18;
const cum_water_prod_column_index = 19;
const cubacks_1_cum_column_index = 24;
const cubacks_2_cum_column_index = 34;
const ur_oil_column_index = 28;
const ur_gas_column_index = 29;
const bsw_column_index = 21;
const gor_column_index = 20;

const field_column_index = 2;
const drainage_point_column_index = 9;
const reservoir_column_index = 3;
const well_column_index = 5;
const project_column_index = 36;
const project_code_column_index = 35;
const facility_column_index = 8;
const hydrocarbon_stream_column_index = 25;

const flare_gas_rate_column_index = 32;
const own_use_gas_rate_column_index = 30;
const sales_gas_rate_column_index = 31;
const condensate_rate_column_index = 42;

const constant_well_parameters_col_titles = [
  'FIELD',
  'UNIQUE_ID',
  'RESERVOIR',
  'WELL',
  'PROJECT',
  'PROJECT_CODE',
  'FACILITY',
  'HC_STREAM',
] as string[];

const constant_well_parameters_col_idxs = [
  field_column_index,
  drainage_point_column_index,
  reservoir_column_index,
  well_column_index,
  project_column_index,
  project_code_column_index,
  facility_column_index,
  hydrocarbon_stream_column_index,
] as number[];

const y_axis_labels = [
  'Oil (b/d)',
  'Condensate (b/d)',
  'Gross (b/d)',
  'Prod/Inj Gas (Mscf/d)',
  'Flare Gas (Mscf/d)',
  'OwnUse Gas (Mscf/d)',
  'Sales Gas (Mscf/d)',
] as string[];

const Y_column_indicies = [
  oil_rate_column_index,
  condensate_rate_column_index,
  liquid_rate_column_index,
  gas_rate_column_index,
  flare_gas_rate_column_index,
  own_use_gas_rate_column_index,
  sales_gas_rate_column_index,
] as number[];
const y_variables_Multipliers = [
  1.0,
  1.0,
  1.0,
  1.0 / 1000.0,
  1.0 / 1000.0,
  1.0 / 1000.0,
  1.0 / 1000.0,
] as number[];

const matTranspose = (matrix: any[][]) => {
  const matrixT = [] as any[];
  const nrow = matrix.length;
  const ncol = matrix[0].length;

  for (let j = 0; j < ncol; j++) {
    const yCol = [] as any[];
    for (let i = 0; i < nrow; i++) {
      yCol.push(matrix[i][j]);
    }
    matrixT.push(yCol);
  }

  return matrixT;
};

const fetchUniqueItems = (objects: any[], attribute: string) => {
  const seen = new Set();
  return objects.filter((obj: any) => {
    const attrValue = obj[attribute];
    if (seen.has(attrValue)) {
      return false;
    } else {
      seen.add(attrValue);
      return true;
    }
  });
};

const getModuleResultsParameters = (moduleForecastResult: any) => {
  const yMatrix = [] as any[][];
  const times = [] as number[];
  const dates = [] as string[];
  const years = [] as number[];
  const module = [] as string[];

  let constant_well_parameters = [] as string[];
  const nY_column_indices = Y_column_indicies.length;
  const uniquie_id_index = constant_well_parameters_col_idxs[1]; // module name index
  const resultWells = moduleForecastResult.resultWells as any[];
  const nResultWells = resultWells.length;

  for (let i = 0; i < nResultWells; i++) {
    const columns = resultWells[i] as any;
    const columnsKeys = Object.keys(columns);
    dates.push(
      columns[columnsKeys[10]] +
        '/' +
        columns[columnsKeys[11]] +
        '/' +
        columns[columnsKeys[12]]
    );
    //times.push(Number(columns[columnsKeys[37]]))
    years.push(columns[columnsKeys[12]]);
    module.push(columns[columnsKeys[uniquie_id_index]]);

    if ((columns[columnsKeys[uniquie_id_index]] as string).length != 0) {
      constant_well_parameters = [];
      const nn = constant_well_parameters_col_idxs.length;
      for (let j = 0; j < nn; j++) {
        constant_well_parameters.push(
          (
            columns[columnsKeys[constant_well_parameters_col_idxs[j]]] as string
          ).toUpperCase()
        );
      }
    }
    const yRow = [] as any[];
    for (let j = 0; j < nY_column_indices; j++) {
      yRow.push(0);
    }

    for (let j = 0; j < nY_column_indices; j++) {
      const variableName = columnsKeys[Y_column_indicies[j]] as string;
      const value = Number(columns[variableName]) * y_variables_Multipliers[j];
      yRow[j] = value;

      /* if (
        variableName == columnsKeys[oil_rate_column_index] &&
        columns[columnsKeys[hydrocarbon_stream_column_index]] == 'oil'
      ) {
        yRow[0] = value;
        yRow[1] = 0;
      } else if (
        variableName == columnsKeys[oil_rate_column_index] &&
        columns[columnsKeys[hydrocarbon_stream_column_index]] == 'gas'
      ) {
        yRow[0] = 0;
        yRow[1] = value;
      } else {
        yRow[j] = value;
      } */
    }
    yMatrix.push(yRow);
  }
  const wellName = '';

  return {
    //times,
    yMatrix,
    wellName,
    dates,
    constant_well_parameters,
    years,
    module,
  };
};

const tabulateWellsSameDirectory = (
  solutionSpacesCase: string[],
  facilitiesNames: string[],
  monthlyReport: any,
  scenarioIndex: number
) => {
  const wells = [] as any[];
  const nsolutionSpaces = solutionSpacesCase.length;
  const nFacilities = facilitiesNames.length;

  for (let facilityIndex = 0; facilityIndex < nFacilities; facilityIndex++) {
    const moduleNames = getmoduleNames(monthlyReport, facilityIndex);
    const nModules = moduleNames.length;
    for (let moduleIndex = 0; moduleIndex < nModules; moduleIndex++) {
      for (
        let solutionSpaceIndex = 0;
        solutionSpaceIndex < nsolutionSpaces;
        solutionSpaceIndex++
      ) {
        const moduleResults = getModuleResults(
          monthlyReport,
          facilityIndex,
          moduleIndex,
          scenarioIndex,
          solutionSpaceIndex
        );
        const well = getModuleResultsParameters(moduleResults) as any;
        let didWellFlow = false;
        const moduleNameCount = well.module.length;
        for (let nm = 0; nm < moduleNameCount; nm++) {
          if (well.module[nm].length != 0) {
            didWellFlow = true;
            break;
          }
        }
        if (didWellFlow == true) {
          wells.push(well);
        }
      }
    }
  }

  return wells;
};

const createColumns = (
  concatenatedTableColumns: string,
  line: string,
  tab: string
) => {
  const columns = {} as any;
  const columnNames = concatenatedTableColumns.split(tab);
  const values = line.split(tab);
  for (let i = 0; i < columnNames.length; i++) {
    columns[columnNames[i]] = values[i];
  }

  return columns;
};

const createAllForecastResultsTable = (
  wells: any[],
  solutionSpacesType: string[],
  scenarioName: string,
  isMonthly: boolean
) => {
  const tab = '@#$%';
  const nWells = wells.length;
  const nsolutionSpacesType = solutionSpacesType.length - 1;

  const table = {} as any;
  const table2 = [] as any[];
  let concatenatedTableColumns = '';
  const forecastCaseModified = scenarioName + ' Forecast';
  let uu = -1;
  let rowKeyIndex = 0;
  for (let i = 0; i < nWells; i++) {
    uu = uu + 1;
    if (uu > nsolutionSpacesType) {
      uu = 0;
    }

    const solution_space = solutionSpacesType[uu];
    //const times = wells[i].times as number[];
    const matrix = matTranspose(wells[i].yMatrix as any[][]);
    const dates = wells[i].dates as string[];
    const constant_well_parameters = wells[i].constant_well_parameters as any[];
    const years = wells[i].years as number[];

    const nTimes = dates.length;

    if (i == 0) {
      //====================Create Title of the Report============================
      let iik = 0;
      let miik = constant_well_parameters_col_titles.length;
      let line_0 = forecastCaseModified;
      for (iik = 0; iik < miik; iik++) {
        line_0 = line_0 + '' + tab;
      }
      line_0 = line_0 + ' ' + tab;
      line_0 = line_0 + ' ' + tab;
      for (let j = 0; j < nTimes; j++) {
        if (j < nTimes - 1) {
          line_0 = line_0 + ' ' + tab;
        } else {
          line_0 = line_0 + ' ';
        }
      }
      rowKeyIndex = rowKeyIndex + 1;
      let rowKey = rowKeyIndex.toString();

      //==========================================================================
      iik = 0;
      miik = constant_well_parameters_col_titles.length;
      let line = '';
      for (iik = 0; iik < miik; iik++) {
        line = line + constant_well_parameters_col_titles[iik] + tab;
      }
      line = line + 'TYPE' + tab;
      line = line + 'PROFILETYPE' + tab;
      for (let j = 0; j < nTimes; j++) {
        if (j < nTimes - 1) {
          if (isMonthly == true) {
            line = line + dates[j] + tab;
          } else {
            line = line + 'Y' + years[j] + tab;
          }
        } else {
          if (isMonthly == true) {
            line = line + dates[j];
          } else {
            line = line + 'Y' + years[j];
          }
        }
      }
      concatenatedTableColumns = line;

      //table[rowKey] = createColumns(concatenatedTableColumns, line_0, tab);
      table2.push(createColumns(concatenatedTableColumns, line_0, tab));

      rowKeyIndex = rowKeyIndex + 1;
      rowKey = rowKeyIndex.toString();
      //table[rowKey] = createColumns(concatenatedTableColumns, line, tab);
      table2.push(createColumns(concatenatedTableColumns, line, tab));

      const n_y_axis_labels = y_axis_labels.length;
      for (let j = 0; j < n_y_axis_labels; j++) {
        const ik = 0;
        const nik = constant_well_parameters.length;
        line = '';
        for (let ik = 0; ik < nik; ik++) {
          line = line + constant_well_parameters[ik] + tab;
        }
        line = line + solution_space.toUpperCase() + tab;
        line = line + y_axis_labels[j] + tab;
        for (let jj = 0; jj < nTimes; jj++) {
          if (jj < nTimes - 1) {
            line = line + matrix[j][jj].toString() + tab;
          } else {
            line = line + matrix[j][jj].toString();
          }
        }
        rowKeyIndex = rowKeyIndex + 1;
        const rowKey = rowKeyIndex.toString();
        //table[rowKey] = createColumns(concatenatedTableColumns, line, tab);
        table2.push(createColumns(concatenatedTableColumns, line, tab));
      }
    } else {
      const n_y_axis_labels = y_axis_labels.length;
      for (let j = 0; j < n_y_axis_labels; j++) {
        const ik = 0;
        const nik = constant_well_parameters.length;
        let line = '';
        for (let ik = 0; ik < nik; ik++) {
          line = line + constant_well_parameters[ik] + tab;
        }
        line = line + solution_space + tab;
        line = line + y_axis_labels[j] + tab;
        for (let jj = 0; jj < nTimes; jj++) {
          if (jj < nTimes - 1) {
            line = line + matrix[j][jj].toString() + tab;
          } else {
            line = line + matrix[j][jj].toString();
          }
        }
        rowKeyIndex = rowKeyIndex + 1;
        const rowKey = rowKeyIndex.toString();
        //table[rowKey] = createColumns(concatenatedTableColumns, line, tab);
        table2.push(createColumns(concatenatedTableColumns, line, tab));
      }
    }
  }

  return table2;
};

const getModuleResults = (
  monthlyReport: any,
  facilityIndex: number,
  moduleIndex: number,
  scenarioIndex: number,
  solutionSpaceIndex: number
) => {
  const forecastSolutionSpacesNames = Object.keys(monthlyReport);
  const firstsolutionSpace =
    monthlyReport[forecastSolutionSpacesNames[solutionSpaceIndex]];
  const scenarioNames = Object.keys(firstsolutionSpace);
  const facilities = firstsolutionSpace[scenarioNames[scenarioIndex]];
  const facilitiesNames = Object.keys(facilities);
  const wellNames = Object.keys(facilities[facilitiesNames[facilityIndex]]);
  const facility = facilities[facilitiesNames[facilityIndex]] as any;
  const moduleResults = facility[wellNames[moduleIndex]];
  return moduleResults;
};

const getmoduleNames = (monthlyReport: any, facilityIndex: number) => {
  const forecastSolutionSpacesNames = Object.keys(monthlyReport);
  const firstsolutionSpace = monthlyReport[forecastSolutionSpacesNames[0]];
  const scenarioNames = Object.keys(firstsolutionSpace);
  const facilities = firstsolutionSpace[scenarioNames[0]];
  const facilitiesNames = Object.keys(facilities);
  const wellNames = Object.keys(facilities[facilitiesNames[facilityIndex]]);
  return wellNames;
};

const getFacilitiesNames = (modules: any[], scenarioAttribute: string) => {
  const uniqueObjects = fetchUniqueItems(modules, scenarioAttribute);
  return uniqueObjects.map((row: any) => {
    return row.facilityName;
  });
};

const getscenarioNames = (modules: any[], scenarioAttribute: string) => {
  const uniqueObjects = fetchUniqueItems(modules, scenarioAttribute);
  return uniqueObjects.map((row: any) => {
    return row.scenarioName;
  });
};

const getsolutionSpaces = (modules: any[], scenarioAttribute: string) => {
  const uniqueObjects = fetchUniqueItems(modules, scenarioAttribute);
  return uniqueObjects.map((row: any) => {
    return row.solutionSpace;
  });
};

//chartDataByModulesOrAggregate
export const getTransposedForecastReport = async (
  forecastResultsByForecastId: any[],
  isMonthly: boolean
) => {
  const forecastSolutionSpacesNames = getsolutionSpaces(
    forecastResultsByForecastId,
    'solutionSpace'
  );
  const scenarioNames = getscenarioNames(
    forecastResultsByForecastId,
    'scenarioName'
  );
  const facilitiesNames = getFacilitiesNames(
    forecastResultsByForecastId,
    'facilityName'
  );
  const monthlyReport = await GetStructuredForecastResultsByForecastId(
    forecastResultsByForecastId,
    scenarioNames,
    forecastSolutionSpacesNames,
    facilitiesNames,
    isMonthly
  );
  const scenarios = {} as any;
  for (let i = 0; i < scenarioNames.length; i++) {
    const wells = tabulateWellsSameDirectory(
      forecastSolutionSpacesNames,
      facilitiesNames,
      monthlyReport,
      i
    );
    const table = createAllForecastResultsTable(
      wells,
      forecastSolutionSpacesNames,
      scenarioNames[i],
      isMonthly
    );

    scenarios[scenarioNames[i]] = table;
  }
  return scenarios;
};
