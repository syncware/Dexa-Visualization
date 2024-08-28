const fs = require('fs').promises;
import { createWriteStream } from 'fs';
import { Transform } from 'stream';
//import JSONStreamStringify  from 'json-stream-stringify';
const JSONStreamStringify = require('json-stream-stringify');

export const exportToJsonFile = async (data:any, fileName:string) => {

    // 2. Convert the object to a JSON string
    const jsonData = JSON.stringify(data, null, 2); // The second argument (null) is for replacer, and the third argument (2) is for indentation

    // 3. Write the JSON string to a file
    const filePath = fileName; // Path to save the JSON file

    await fs.writeFile(filePath, jsonData, 'utf8'); // Use fs.writeFile for async, fs.writeFileSync for sync

    console.log(`Data has been written to ${filePath}`);
}

export const streamToJsonFile = async (data: any, fileName: string) => {

    const fileStream = createWriteStream(fileName, { encoding: 'utf8' });

    const jsonStream = new Transform({
        writableObjectMode: true,
        transform(chunk, encoding, callback) {
            // Convert chunk to JSON string
            const jsonChunk = JSON.stringify(chunk, null, 2) + ',\n';
            callback(null, jsonChunk);
        }
    });

    // Handle the start and end of the JSON array
    fileStream.write('[');
    jsonStream.pipe(fileStream, { end: false });

    // Send each item in data to the jsonStream
    for (const item of data) {
        jsonStream.write(item);
    }

    // Close the JSON array and the file stream
    jsonStream.end();
    fileStream.end(']');
};


export const streamToJsonFile2 = async (data: any, fileName: string) => {
    const fileStream = createWriteStream(fileName, { encoding: 'utf8' });

    // Stream the JSON data
    const jsonStream = new JSONStreamStringify(data);

    jsonStream.pipe(fileStream);

    jsonStream.on('end', () => {
        console.log(`Data has been written to ${fileName}`);
    });

    jsonStream.on('error', (err:any) => {
        console.error(`Error writing data to ${fileName}:`, err);
    });
};
