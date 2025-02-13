import * as fs from 'fs';

// Define a function to recursively find and replace
function findAndReplace(obj: any, findValue: any, replaceValue: any): any {
  if (Array.isArray(obj)) {
    return obj.map((item) => findAndReplace(item, findValue, replaceValue));
  } else if (typeof obj === 'object' && obj !== null) {
    const newObj: { [key: string]: any } = {};
    for (const [key, value] of Object.entries(obj)) {
      newObj[key] = findAndReplace(value, findValue, replaceValue);
    }
    return newObj;
  } else {
    return obj === findValue ? replaceValue : obj;
  }
}

// Load your large JSON file
let rawData = fs.readFileSync(
  '/Users/GSanni/Desktop/myinfo/pet_app/files/apex-FG.forecast_forecastresultsbymodules.json'
).toString();
let data = JSON.parse(rawData);

// Replace 'old_value' with 'new_value'
// "moduleName": "FOO6R81L_FOO6 T30X_P12",
//   "FacilityName": "ABU_FS4",
//   "ScenarioName": "1P_1C",
//   "ModuleKey": "potential/1P_1C/ABU_FS4/FOO6R81L_FOO6 T30X_P12",
//   "SolutionSpace": "potential",
const findValue = 'ModuleName'; // This is the value to find
const replaceValue = 'moduleName'; // This is the value to replace with

// Perform find and replace
const modifiedData = findAndReplace(data, findValue, replaceValue);

// Save the modified JSON
fs.writeFileSync('forecastresultsbymodules.json', JSON.stringify(modifiedData, null, 4));

console.log('Replacement complete. Saved to modified_file.json');
