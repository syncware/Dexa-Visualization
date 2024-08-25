import fs from 'fs';
const fsp = fs.promises;
import path from 'path';

function createDirectories(pathname: string) {
  const __dirname = path.resolve();

  // Remove leading directory markers, and remove ending /file-name.extension
  pathname = pathname.replace(/^\.*\/|\/?[^\/]+\.[a-z]+|\/$/g, '');
  fs.mkdir(path.resolve(__dirname, pathname), { recursive: true }, (e) => {
    if (e) {
      console.error(e);
    } else {
    }
  });
}

function getFilesInDirectory2(directoryPath: string, callback: any) {
  fs.readdir(directoryPath, (err, files) => {
    if (err) {
      callback(err);
      return;
    }
    callback(null, files);
  });
}

async function getFilesInDirectory(directoryPath: string) {
  //const data = {};
  const files = await fsp.readdir(directoryPath);
  /* for (const filename of files) {
      const full = path.join(directoryPath, filename);
      const content = await fsp.readFile(full, {encoding: 'utf8'});
      data[filename] = content;
  } */
  return files;
}

let fileNames = [] as string[];
const getFileNames = (err: any, files: string[]) => {
  if (err) {
    console.error('Error:', err);
    return;
  }
  fileNames = files;
};

async function createWriteTextFile(pathname: string, content: string) {
  try {
    const __dirname = path.resolve();
    pathname = pathname.replace(/^\.*\/|\/?[^\/]+\.[a-z]+|\/$/g, '');
    const filePath = path.resolve(__dirname, pathname);
    await fs.writeFile(`${filePath}.txt`, content, (e: any) => {
      if (e) {
        console.error(e);
      } else {
      }
    });
  } catch (err) {
    console.log(err);
  }
}

export async function exportForecastResults(monthlyReport_LightWeight: any) {
  const folderName = 'ForecastResults';
  const forecastCaseKeys = Object.keys(monthlyReport_LightWeight);
  createDirectories(folderName);
  let i = 0,
    j = 0,
    k = 0,
    ii = 0;
  for (i = 0; i < forecastCaseKeys.length; i++) {
    const forecastCase = monthlyReport_LightWeight[forecastCaseKeys[i]];
    createDirectories(`${folderName}/${forecastCaseKeys[i]}`);
    const scenariosKeys = Object.keys(forecastCase);

    j = 0;
    for (j = 0; j < scenariosKeys.length; j++) {
      const scenario = forecastCase[scenariosKeys[j]];
      createDirectories(
        `${folderName}/${forecastCaseKeys[i]}/${scenariosKeys[j]}`
      );
      const facilitiesKeys = Object.keys(scenario);
      k = 0;
      for (k = 0; k < facilitiesKeys.length; k++) {
        const facility = scenario[facilitiesKeys[k]];
        createDirectories(
          `${folderName}/${forecastCaseKeys[i]}/${scenariosKeys[j]}/${facilitiesKeys[k]}`
        );
        const wellKeys = Object.keys(facility);
        ii = 0;
        for (ii = 0; ii < wellKeys.length; ii++) {
          const well = facility[wellKeys[ii]];
          const table = well['resultWells'];
          await createWriteTextFile(
            `${folderName}/${forecastCaseKeys[i]}/${scenariosKeys[j]}/${facilitiesKeys[k]}/${wellKeys[ii]}`,
            table
          );
        }
      }
    }
  }
}

const getSubDirectoriesSync = (directoryPath: string) => {
  return fs
    .readdirSync(directoryPath)
    .filter((file) =>
      fs.statSync(path.join(directoryPath, file)).isDirectory()
    );
};

async function readTextFile(filePath: string) {
  try {
    const content = await fsp.readFile(filePath, 'utf8');
    return content;
  } catch (err) {
    throw err;
  }
}
export async function importForecastResults() {
  const rootParentDirectory = 'ForecastResults';
  const __dirname = path.resolve();
  const pathname = rootParentDirectory.replace(
    /^\.*\/|\/?[^\/]+\.[a-z]+|\/$/g,
    ''
  );
  const parentDirectoryPath = path.resolve(__dirname, pathname);

  const forecastSolutionSpaces = [
    'potential',
    'deliverability',
    'availability',
    'offtake',
  ];
  const scenariosKeys = ['1P_1C', '2P_2C', '3P_3C'];

  let i = 0,
    j = 0,
    k = 0,
    ii = 0;
  let inputObjectAll = {} as any;
  let inputObjectFSS = {} as any;
  for (i = 0; i < forecastSolutionSpaces.length; i++) {
    let forecastCase = forecastSolutionSpaces[i];
    j = 0;
    let inputObject = {} as any;
    for (j = 0; j < scenariosKeys.length; j++) {
      let scenarioDirectoryPath = `${parentDirectoryPath}/${forecastCase}/${scenariosKeys[j]}`;
      const facilitiesNames = getSubDirectoriesSync(scenarioDirectoryPath); // Read facilities folder names
      k = 0;
      let FaclitiesObject = {} as any;
      for (k = 0; k < facilitiesNames.length; k++) {
        let facilityDirectoryPath = `${parentDirectoryPath}/${forecastCase}/${scenariosKeys[j]}/${facilitiesNames[k]}`;
        if (k == 0 && j == 0 && i == 0) {
          console.log(facilityDirectoryPath);
        }
        let wellNames = await getFilesInDirectory(facilityDirectoryPath); // Read facilities file names
        ii = 0;
        let decksPerFacility = {} as any;
        for (ii = 0; ii < wellNames.length; ii++) {
          let wellResultsFilePath = `${parentDirectoryPath}/${forecastCase}/${scenariosKeys[j]}/${facilitiesNames[k]}/${wellNames[ii]}`;

          let table = await readTextFile(wellResultsFilePath);
          const deckObject = {
            resultWells: table,
          } as any;
          decksPerFacility[wellNames[ii]] = deckObject;
        }
        FaclitiesObject[facilitiesNames[k]] = decksPerFacility;
      }
      let scenarioName = scenariosKeys[j];
      inputObject[scenarioName] = FaclitiesObject;
    }
    inputObjectFSS[forecastSolutionSpaces[i]] = inputObject;
  }

  inputObjectAll['monthlyReport'] = inputObjectFSS;

  return inputObjectAll;
}
