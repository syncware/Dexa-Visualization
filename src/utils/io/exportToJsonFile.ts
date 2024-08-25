import * as fs from 'fs';

export const exportToJsonFile = (data:any, fileName:string) => {

    // 2. Convert the object to a JSON string
    const jsonData = JSON.stringify(data, null, 2); // The second argument (null) is for replacer, and the third argument (2) is for indentation

    // 3. Write the JSON string to a file
    const filePath = fileName; // Path to save the JSON file

    fs.writeFileSync(filePath, jsonData, 'utf8'); // Use fs.writeFile for async, fs.writeFileSync for sync

    console.log(`Data has been written to ${filePath}`);
}
