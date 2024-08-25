export const getForecastResult = (table: string) => {
  const columnDelimeter = '@#$%';
  const rowDelimeter = '@#*$%';
  const rows = table.split(rowDelimeter);
  const actualTable = rows.map((row, i) => {
    const result = {} as any;
    let columns: string[] = [];
    let colIndx = 0;
    try {
      columns = row.split(columnDelimeter);

      result.uniqueId = columns[colIndx] as string;
      colIndx++;
      result.forecastVersion = columns[colIndx] as string;
      colIndx++;
      result.field = columns[colIndx] as string;
      colIndx++;
      result.reservoir = columns[colIndx] as string;
      colIndx++;
      result.drainagePoint = columns[colIndx] as string;
      colIndx++;
      result.string = columns[colIndx] as string;
      colIndx++;
      result.developmentTranche = columns[colIndx] as string;
      colIndx++;
      result.asset = columns[colIndx] as string;
      colIndx++;
      result.facilities = columns[colIndx] as string;
      colIndx++;
      result.module = columns[colIndx] as string;
      colIndx++;
      result.day = Number(columns[colIndx]);
      colIndx++;
      result.month = Number(columns[colIndx]);
      colIndx++;
      result.year = Number(columns[colIndx]);
      colIndx++;
      result.oilRate = Number(columns[colIndx]);
      colIndx++;
      result.gasRate = Number(columns[colIndx]);
      colIndx++;
      result.waterRate = Number(columns[colIndx]);
      colIndx++;
      result.liquidRate = result.oilRate + result.waterRate;
      colIndx++;
      result.cumOilProd = Number(columns[colIndx]);
      colIndx++;
      result.cumGasProd = Number(columns[colIndx]);
      colIndx++;
      result.cumWaterProd = Number(columns[colIndx]);
      colIndx++;
      result.gOR = Number(columns[colIndx]);
      colIndx++;
      result.bSW = Number(columns[colIndx]);
      colIndx++;
      result.cGR = Number(columns[colIndx]);
      colIndx++;
      result.wGR = Number(columns[colIndx]);
      colIndx++;
      result.cutBack = Number(columns[colIndx]);
      colIndx++;
      result.hydrocarbonStream = columns[colIndx] as string;
      colIndx++;
      result.hydrocarbonType = columns[colIndx] as string;
      colIndx++;
      result.terminal = columns[colIndx] as string;
      colIndx++;
      result.uRo = Number(columns[colIndx]);
      colIndx++;
      result.uRg = Number(columns[colIndx]);
      colIndx++;
      result.ownUseGas = Number(columns[colIndx]);
      colIndx++;
      result.gasDemand = Number(columns[colIndx]);
      colIndx++;
      result.flareGas = Number(columns[colIndx]);
      colIndx++;
      result.crudeOilLossess = Number(columns[colIndx]);
      colIndx++;
      result.cutBackRatio = Number(columns[colIndx]);
      colIndx++;
      result.projectCode = columns[colIndx] as string;
      colIndx++;
      result.projectName = columns[colIndx] as string;
      colIndx++;
      result.days = Number(columns[colIndx]);
      colIndx++;
      result.optimalSolution = Number(columns[colIndx]);
      colIndx++;
      result.allWellsLiquidCapacity = Number(columns[colIndx]);
      colIndx++;
      result.allWellsGasCapacity = Number(columns[colIndx]);
      colIndx++;
      result.resourceClass = columns[colIndx] as string;
      colIndx++;
      result.condensateRate = Number(columns[colIndx]);
      colIndx++;
      result.reasonForTermination = columns[colIndx];
      colIndx++;
      result.declineRate = Number(columns[colIndx]);
      colIndx++;
    } catch (er: any) {}

    return result;
  });

  actualTable.pop();
  return actualTable;
};

export const getForecastReport = (forecastReport: any) => {
  let timeReport: any = {};

  const scenarios = Object.keys(forecastReport);
  let k = 0;
  const scenarioCount = scenarios.length;
  for (k = 0; k < scenarioCount; k++) {
    const facilities = Object.keys(forecastReport[scenarios[k]]);
    let j = 0;
    const facilityCount = facilities.length;
    let facilitiesMonthly: any = {};
    for (j = 0; j < facilityCount; j++) {
      const modulesMonthly = Object.keys(
        forecastReport[scenarios[k]][facilities[j]]
      );
      let i = 0;
      const moduleCount = modulesMonthly.length;
      let wellsMonthly: any = {};
      for (i = 0; i < moduleCount; i++) {
        const wellMonthly = forecastReport[scenarios[k]][facilities[j]][
          modulesMonthly[i]
        ] as any;
        const resultWellsMonthly = wellMonthly.resultWells as string;
        let moduleResultMonthly = {
          resultWells: getForecastResult(resultWellsMonthly),
        };
        wellsMonthly[modulesMonthly[i]] = moduleResultMonthly;
      }

      facilitiesMonthly[facilities[j]] = wellsMonthly;
    }

    timeReport[scenarios[k]] = facilitiesMonthly;
  }
  return timeReport;
};

export const getAllForecastReport = (allForecastReport: any[]) => {
  let monthlyReport: any = {};
  let yearlyReport: any = {};

  const length = allForecastReport.length;

  let kk = 0;
  for (kk = 0; kk < length; kk++) {
    const forecastScenarioReport: any = allForecastReport[kk] as any;
    const monthlyScenarioReport = forecastScenarioReport.monthlyReport as any;
    const yearlScenarioReport = forecastScenarioReport.yearlyReport as any;
    const scenarios = Object.keys(monthlyScenarioReport);
    let k = 0;
    const scenarioCount = scenarios.length;

    for (k = 0; k < scenarioCount; k++) {
      const facilities = Object.keys(monthlyScenarioReport[scenarios[k]]);
      let j = 0;
      const facilityCount = facilities.length;
      let facilitiesMonthly: any = {};
      let facilitiesYearly: any = {};
      for (j = 0; j < facilityCount; j++) {
        const modulesMonthly = Object.keys(
          monthlyScenarioReport[scenarios[k]][facilities[j]]
        );
        const modulesYearly = Object.keys(
          yearlScenarioReport[scenarios[k]][facilities[j]]
        );
        let i = 0;
        const moduleCount = modulesMonthly.length;
        let wellsMonthly: any = {};
        let wellsYearly: any = {};
        for (i = 0; i < moduleCount; i++) {
          //
          const wellMonthly = monthlyScenarioReport[scenarios[k]][
            facilities[j]
          ][modulesMonthly[i]] as any;
          const wellYearly = monthlyScenarioReport[scenarios[k]][facilities[j]][
            modulesYearly[i]
          ] as any;
          const resultWellsMonthly = wellMonthly.resultWells as string;
          const resultWellsYearly = wellYearly.resultWells as string;
          let moduleResultMonthly = {
            resultWells: getForecastResult(resultWellsMonthly) as [],
          };
          wellsMonthly[modulesMonthly[i]] = moduleResultMonthly;

          let moduleResultYearly = {
            resultWells: getForecastResult(resultWellsYearly) as [],
          };

          wellsYearly[modulesYearly[i]] = moduleResultYearly;

          // if(i == 0){
          //
          //
          // }

          //
          //forecastReport[scenarios[k]][facilities[j]][modules[i]] = moduleResult as any
        }

        facilitiesMonthly[facilities[j]] = wellsYearly;
        facilitiesYearly[facilities[j]] = wellsMonthly;
      }

      monthlyReport[scenarios[k]] = facilitiesMonthly;
      yearlyReport[scenarios[k]] = facilitiesYearly;
    }
  }

  //
  //
  return { monthlyReport, yearlyReport };
};
