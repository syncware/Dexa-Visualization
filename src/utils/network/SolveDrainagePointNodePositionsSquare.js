import flatten from "lodash/flatten";

const SolveDrainagePointNodePositionsSquare = (
  manifoldPosition,
  numberOfWells,
  drainagePointGroupOffset
) => {
  const maximumWellsSingleRow = 6;
  const interwellDistance = 20;
  const wellsRowDistance = 25;
  const noOfLoops = Math.ceil(numberOfWells / maximumWellsSingleRow);

  let diffs = [];
  diffs.push({ a: 0, b: 0 });
  for (let i = 1; i <= maximumWellsSingleRow; i++) {
    diffs.push({ a: i * interwellDistance, b: 0 });
    diffs.push({ a: -i * interwellDistance, b: 0 });
  }

  let realdiffs = [];
  if (noOfLoops === 1) {
    realdiffs = diffs.slice(0, numberOfWells);
  } else {
    diffs = diffs.slice(0, maximumWellsSingleRow);
    for (let i = 0; i <= noOfLoops; i++) {
      realdiffs.push(
        diffs.map((v) => ({ a: v.a, b: v.b + wellsRowDistance * i }))
      );
    }
    realdiffs = flatten(realdiffs).slice(0, numberOfWells);
  }

  const drainagePointPositions = realdiffs.map((diff) => {
    return {
      x: diff.a + manifoldPosition.x,
      y: diff.b + manifoldPosition.y + drainagePointGroupOffset,
    };
  });

  return drainagePointPositions;
};
export default SolveDrainagePointNodePositionsSquare;
