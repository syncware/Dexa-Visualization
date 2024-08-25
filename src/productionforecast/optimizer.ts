//let cppLibraryPath = "./Release/volumeforecast.node";
//let cppLibraryPath:string = "./build/Release/volumeforecast.node";
//let cppLibraryPath: string = "../../build/Release/volumeforecast.node";
let cppLibraryPath: string = "../../build/Release/volumeforecast.node";
// let cppLibraryPath: string = "../../build/Debug/volumeforecast.node";

// const os = require('os');
// if(os.type()==='Windows_NT')
// {
//     cppLibraryPath="./release/volumeforecast-window.node";
// }
export const volumeforecastModule = require(cppLibraryPath); 
