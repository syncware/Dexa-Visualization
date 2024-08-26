const fs = require('fs').promises;
import fss from 'fs';
import * as path from 'path';

export const importJsonFile = async (fileName:string) => {

    // Define the path to your JSON file

    const projectRoot = process.cwd();
    const jsonFilePath = path.join(projectRoot, fileName);

    // Read the file asynchronously
    const jsonData = await fs.readFile(jsonFilePath, 'utf-8');

    return JSON.parse(jsonData);
}

export const importJsonFile2 = (fileName:string) => {

    // Define the path to your JSON file

    const projectRoot = process.cwd();
    const jsonFilePath = path.join(projectRoot, fileName);

    // Read the file asynchronously
    const jsonData = fss.readFileSync(jsonFilePath, 'utf-8');

    return JSON.parse(jsonData);
}