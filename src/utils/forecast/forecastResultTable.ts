import { evaluate } from "mathjs";
import { ForecastIInputDeckEntity } from "../../models/forecastInputDeck";
import { volumeforecastModule } from "../../productionforecast/optimizer";
import {
  Convert_to_Display_Unit_No_Variableunit,
  Get_GlobalVariableUnits,
  Get_Units,
} from "../unit/unitService";
import * as reformForecastResult from "./reformForecastResult";

function GetActualWells(data: [], moduleNames: string[]): any {
  const result = {} as any;
  let i: number = 0;

  data.forEach((x) => {
    const val = x as any;

    Object.keys(val).forEach((key) => {
      const table = val[key] as string;
      const well = reformForecastResult.getForecastResult(table) as [];
      result[moduleNames[i]] = well;
    });
    i = i + 1;
  });

  return result;
}

function GetVariables(): any {
  const variableNames: object = {
    Oil: {
      hydrocarbonStream: "oil",
      pointerName: "oilRate",
      unitVariable: "oilRate",
    },
    Condensate: {
      hydrocarbonStream: "gas",
      pointerName: "gasRate",
      unitVariable: "gasRate",
    },
    Gross: {
      pointerName: "liquidRate",
      unitVariable: "liquidRate",
    },
    "Prod/Inj Gas": {
      pointerName: "gasRate",
      unitVariable: "gasRate",
    },
    "Sales Gas": {
      pointerName: "gasDemand",
      unitVariable: "gasDemand",
    },
    "Flare Gas": {
      // Flare Gas = Prod Gas - (Sales Gas + Ownuse Gas)
      variables: ["gasRate", "gasDemand", "ownUseGas"],
      pointerName: "gasRate - gasDemand + ownUseGas",
      unitVariable: "gasRate",
    },
    "OwnUse Gas": {
      pointerName: "ownUseGas",
      unitVariable: "ownUseGas",
    },

    // "Reserves": {
    //     composite: {
    //         x: {
    //             hydrocarbonStream: "oil",
    //             pointerName: "uRo"
    //         },
    //         y: {
    //             hydrocarbonStream: "gas",
    //             pointerName: "uRg"
    //         }
    //     },

    // }
  };
  return variableNames;
}

export async function Get_ForecastResult_Table_Data(
  forecastResult: any,
  forecastInputDecks: ForecastIInputDeckEntity[]
): Promise<object[]> {
  let forecastTables: object[] = [];

  try {
    const errMsg = "Error in applying unit conversion to facilities deck.";
    const _forecastInputDecks = await Convert_to_Display_Unit_No_Variableunit(
      forecastInputDecks,
      errMsg
    );
    if (_forecastInputDecks) {
      forecastInputDecks = _forecastInputDecks;
    }

    const promise_variables = await Get_GlobalVariableUnits();
    const _variables = promise_variables.filter((x) => x.hasUnit == true);
    const _units = await Get_Units();

    const variables_KeyPair = Object.assign(
      {},
      ..._variables.map((x) => ({ [x.name]: x }))
    );
    const units_KeyPair = Object.assign(
      {},
      ..._units.map((x) => ({ [x.id]: x }))
    );

    const variableUnits = {
      oilRate:
        units_KeyPair[variables_KeyPair.oilRate.unitSettings.databaseUnitId]
          .name,
      gasRate:
        units_KeyPair[variables_KeyPair.gasRate.unitSettings.databaseUnitId]
          .name,
      liquidRate:
        units_KeyPair[variables_KeyPair.waterRate.unitSettings.databaseUnitId]
          .name,
      gasFlare:
        units_KeyPair[variables_KeyPair.gasRate.unitSettings.databaseUnitId]
          .name,
      ownUseGas:
        units_KeyPair[variables_KeyPair.ownUseGas.unitSettings.databaseUnitId]
          .name,
      gasDemand:
        units_KeyPair[variables_KeyPair.gasDemand.unitSettings.databaseUnitId]
          .name,
    } as any;

    const variableNames = GetVariables();
    const forecastResultsByModule = Object.assign(
      {},
      ...forecastInputDecks.map((x) => ({ [x.module]: x }))
    );

    const forecastResultKeys = Object.keys(forecastResult);
    for (const scenarioName of forecastResultKeys) {
      const forecastResultScenario = forecastResult[scenarioName];

      const forecastResultScenarioKeys = Object.keys(forecastResultScenario);
      for (const facilityName of forecastResultScenarioKeys) {
        const forecastResultFacility = forecastResultScenario[facilityName];
        const moduleNames = Object.keys(forecastResultFacility);
        const forecastWells = Object.keys(forecastResultFacility).map(
          (i) => forecastResultFacility[i]
        );

        var inputOjbect = {
          wells: forecastWells,
          isByYear: true,
          isForChart: false,
          nWells: forecastWells.length
        };

        forecastTables = await new Promise((resolve, reject) => {
          volumeforecastModule.GetYearlyForcastResultModulesAsync(
            inputOjbect,
            AllWellsYearlyResult
          );
          function AllWellsYearlyResult(err: any, aggregatedResult: any) {
            if (err) {
              
              return reject(err);
            } else {
              const _aggregateWell = GetActualWells(
                aggregatedResult,
                moduleNames
              );

              const _aggregateWellKeys = Object.keys(_aggregateWell);
              for (const module of _aggregateWellKeys) {
                const wells = _aggregateWell[module] as any[];

                const variableNamesKeys = Object.keys(variableNames);
                for (const va of variableNamesKeys) {
                  const forecastTable = {} as any;
                  const variable = variableNames[va] as any;
                  forecastTables.push(forecastTable);

                  forecastTable["Scenario"] = scenarioName;
                  forecastTable["Field"] = forecastResultsByModule[module].field;
                  forecastTable["Reservoir"] = forecastResultsByModule[module].reservoir;
                  forecastTable["Drainage Point"] =
                    forecastResultsByModule[module].drainagePoint;
                  forecastTable["Facilities"] = facilityName;
                  forecastTable["Module"] = module;
                  // forecastTable["Profile Type"] = va  // Add unit
                  forecastTable["Profile Type"] = `${va} (${
                    variableUnits[variable.unitVariable]
                  })`;

                  forecastTable["Project Code"] =
                    forecastResultsByModule[module].projectCode;
                  forecastTable["Project Name"] =
                    forecastResultsByModule[module].projectName;
                  forecastTable["Np"] = forecastResultsByModule[module].Np;
                  forecastTable["Gp"] = forecastResultsByModule[module].Gp;

                  wells.forEach((x) => {
                    const yearName = "Y" + x.year;
                    let originalEquation = variable.pointerName;
                    //NAG
                    forecastTable["Hydrocarbon Stream"] = x.hydrocarbonStream;
                    forecastTable["Hydrocarbon Type"] =
                      x.hydrocarbonStream == "oil" ? "Oil/AG" : "NAG";
                    forecastTable[yearName] = 0;
                    if (variable.hydrocarbonStream) {
                      if (x.hydrocarbonStream == variable.hydrocarbonStream) {
                        forecastTable[yearName] = x[variable.pointerName];
                      }
                    } else {
                      if (variable.variables) {
                        variable.variables.forEach((op: any) => {
                          const tx = op.trim();
                          const newValue = x[tx];
                          originalEquation = originalEquation.replace(
                            tx,
                            newValue
                          );
                        });
                        forecastTable[yearName] = evaluate(originalEquation);
                      } else {
                        forecastTable[yearName] = x[variable.pointerName];
                      }
                    }
                  });
                }
              }
              resolve(forecastTables);
            }
          }
        });
      }
    }
  } catch (err) {
    
  }
  // exportJson(forecastTables, 'forecast_Table_Data.xlsx')
  return forecastTables;
}

export async function Get_ForecastResult_Table_Data_By_ScenarioName(
  scenarioName: string,
  forecastResult: any
): Promise<any> {
  try {
    const forecastResultScenario = forecastResult[scenarioName];

    // const facilities = Object.keys(forecastResultScenario).map(i =>
    //     Object.keys(forecastResultScenario[i]).map(j => forecastResultScenario[i][j]));

    const facilities: object[] = [];
    Object.keys(forecastResultScenario).forEach((facilityName) => {
      const forecastResultFacility = forecastResultScenario[facilityName];
      const forecastWells = Object.keys(forecastResultFacility).map(
        (i) => {
          return {
            innerWells: forecastResultFacility[i].wells,
            nInnerWells: forecastResultFacility[i].wells.length
            //forecastResultFacility[i]
          }
        }
      );
      facilities.push(forecastWells);
    });

    const result = await Get_Yearly_ForecastResult_By_Scenario_Level(
      facilities
    );
    return result;
  } catch (err) {
    
  }
}

export async function Get_Yearly_ForecastResult_By_Scenario_Level(
  facilities: any
): Promise<any> {
  let result = null;

  try {
    var inputOjbect = {
      facilities: facilities,
      isByYear: true,
      isForChart: false,
      nFacilities: facilities.length
    };
    result = await new Promise((resolve, reject) => {
      volumeforecastModule.GetYearlyForcastResultScenarioLevelAsync(
        inputOjbect,
        ScenarioYearlyResult
      );
      function ScenarioYearlyResult(err: any, aggregatedResult: any): any {
        if (err) {
          
          return reject(err);
        } else {
          const table = (aggregatedResult as any).resultWells as string;
          const actualResult = reformForecastResult.getForecastResult(table);
          resolve(actualResult);
        }
      }
    });
  } catch (err: any) {
    
  }

  return result;
}
