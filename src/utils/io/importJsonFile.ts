const fs = require('fs').promises;
import * as path from 'path';

export const importJsonFile = async (fileName:string) => {

    // Define the path to your JSON file
    const jsonFilePath = path.join(__dirname, fileName);

    // Read the file asynchronously
    const jsonData = await fs.readFile(jsonFilePath, 'utf-8');

    return JSON.parse(jsonData);
}