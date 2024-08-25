import { ForecastIInputDeckEntity } from '../models/forecastInputDeck';
import { ForecastProfileEntity } from '../models/forecastProfiles';

export function ValidateForecastProfiles(
  forecastProfiles2: ForecastProfileEntity[],
  forecastDeck: ForecastIInputDeckEntity[]
): boolean {
  function onlyUnique(value: any, index: any, self: string | any[]) {
    return self.indexOf(value) === index;
  }

  const forecastProfiles = [] as ForecastProfileEntity[];
  let _forecastDeckNames = forecastDeck.map((x) => x.module).filter(onlyUnique);
  for (const _forecastDeckName of _forecastDeckNames) {
    for (const forecastProfile2 of forecastProfiles2) {
      if (_forecastDeckName == forecastProfile2.moduleName) {
        forecastProfiles.push(forecastProfile2);
      }
    }
  }

  let _forecastProfilesModuleNames = forecastProfiles
    .map((x) => x.moduleName)
    .filter(onlyUnique);

  const uniqueForecastProfiles = [] as ForecastProfileEntity[];
  for (const _forecastProfilesModuleName of _forecastProfilesModuleNames) {
    for (const forecastProfile of forecastProfiles) {
      if (_forecastProfilesModuleName == forecastProfile.moduleName) {
        uniqueForecastProfiles.push(forecastProfile);
        break;
      }
    }
  }

  let count = 0;
  for (const _forecastProfilesModuleName of _forecastProfilesModuleNames) {
    for (const _forecastDeckName of _forecastDeckNames) {
      if (_forecastProfilesModuleName == _forecastDeckName) {
        count++;
        break;
      }
    }
  }

  let count2 = 0;
  for (const uniqueForecastProfile of uniqueForecastProfiles) {
    for (const _forecastDeck of forecastDeck) {
      if (
        uniqueForecastProfile.hydrocarbonStream ==
        _forecastDeck.hydrocarbonStream
      ) {
        count2++;
        break;
      }
    }
  }

  const checkModuleNames = count === _forecastProfilesModuleNames.length;
  const checkHydrocarbonStreams = count2 === uniqueForecastProfiles.length;

  return {
    checkModuleNames,
    checkHydrocarbonStreams,
    forecastProfiles,
  } as any;
}
