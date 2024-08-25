const SolveDrainagePointNodePositionsArc = (
  manifoldPosition,
  radius,
  numberOfWells
) => {
  const a = manifoldPosition.x;
  const b = -1 * manifoldPosition.y;

  const floatRange = (last, first, step) => {
    const arr = [];

    let d = last;
    arr.push(d);
    while (d >= first) {
      arr.push(d + step);
      d += step;
    }

    return arr;
  };

  //y range
  const firstY = 0.5 * radius;
  const lastY = radius;
  const rangeY = floatRange(lastY, firstY, -5);
  const noOfLoops = Math.ceil(numberOfWells / rangeY.length);
  let fullRangeY = [];
  const wellsRowDistance = 50;
  if (noOfLoops === 1) {
    fullRangeY = rangeY;
  } else {
    for (let i = 0; i <= noOfLoops; i++) {
      fullRangeY.push(...rangeY.map((v) => v + wellsRowDistance * i));
    }
  }
  const realRangeY = fullRangeY.slice(0, numberOfWells);

  const drainagePointPositions = [];
  let realRadius = realRangeY[0];
  for (let i = 0; i < realRangeY.length; i++) {
    const newY = -1 * realRangeY[i] + b;
    const isRangeYInitial = realRangeY[i] > realRadius;
    if (isRangeYInitial) realRadius = realRangeY[i];

    const insideSqrt = realRadius ** 2 - (newY - b) ** 2;
    const newXPos = a + Math.sqrt(insideSqrt);
    const newXNeg = a - Math.sqrt(insideSqrt);

    if (realRangeY[i] === realRadius) {
      drainagePointPositions.push({ x: newXPos, y: -newY });
    } else {
      drainagePointPositions.push({ x: newXPos, y: -newY });
      drainagePointPositions.push({ x: newXNeg, y: -newY });
    }
  }

  return drainagePointPositions.slice(0, numberOfWells);
};

export default SolveDrainagePointNodePositionsArc;
