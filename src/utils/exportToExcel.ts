var json2xls = require("json2xls");
const fs = require("fs");

export function exportJson(jsonData: object[], filename: string) {
  // const filename = 'forecast_Table_Data.xlsx';

  let filePath =
    "C:/Users/INTEGRITY/Documents/Projects/database-script/" + filename;

  var xls = json2xls(jsonData);
  fs.writeFileSync(filePath, xls, "binary", (err: any) => {
    if (err) {
      
    }
    
  });
}
