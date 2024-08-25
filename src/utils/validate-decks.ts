import { ForecastIInputDeckEntity } from '../models/forecastInputDeck';

export function ValidateDecks(
  facilitiesDeck: any[],
  forecastDeck: ForecastIInputDeckEntity[]
): boolean {
  function onlyUnique(value: any, index: any, self: string | any[]) {
    return self.indexOf(value) === index;
  }

  const _facilitiesDeckNames = facilitiesDeck
    .map((x) => x.primary)
    .filter(onlyUnique);
  const _forecastDeckNames = forecastDeck
    .map((x) => x.facilities)
    .filter(onlyUnique);

  const union = _facilitiesDeckNames.concat(_forecastDeckNames);
  const unionObject = union.filter(onlyUnique);

  return unionObject.length === _facilitiesDeckNames.length;
}
