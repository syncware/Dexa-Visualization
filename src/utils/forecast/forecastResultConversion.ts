import {
  Convert_to_Database_Unit_No_Variableunit,
  Convert_to_Display_Unit_No_Variableunit,
} from "../unit/unitService";

export async function Convert_Result_to_Display_Unit(
  forecastResult: any
): Promise<any> {
  if (forecastResult === undefined) {
    return forecastResult;
  }

  let scenarioKeys = Object.keys(forecastResult);
  for (let scenarioName of scenarioKeys) {
    let forecastResultScenario = forecastResult[scenarioName];

    let facilityKeys = Object.keys(forecastResultScenario);
    for (let facilityName of facilityKeys) {
      let forecastResultFacility = forecastResultScenario[facilityName];
      let moduleKeys = Object.keys(forecastResultFacility);
      // const forecastWells = moduleKeys.map(i => forecastResultFacility[i]);
      for (let moduleName of moduleKeys) {
        let well = forecastResultFacility[moduleName];
        let resultWells = well.resultWells;
        let output = await Convert_to_Display_Unit_No_Variableunit(
          resultWells,
          "Error in convert forecastResult."
        );
        if (output) {
          well.resultWells = output as [];
        }
      }
    }
  }
  return forecastResult;
}
