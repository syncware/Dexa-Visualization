import { IPosition } from "../../types";
import SolveDrainagePointNodePositionsSquare from "./SolveDrainagePointNodePositionsSquare";
import uniq from "lodash/uniq";

const generateRepeatingSequence = (noOfNodes: number) => {
  const arr = [];
  for (let i = 0; i < noOfNodes; i++) {
    arr.push(i + 1);
    arr.push(i + 1);
  }
  return arr.slice(0, noOfNodes);
};

const generateAltSequence = (
  shift: number,
  noOfNodes: number,
  multNumbers: number[]
) => {
  const altSequence = [];
  for (let i = 0; i < noOfNodes; i++) {
    const seqEle = Math.pow(-1, i + 1);
    const multNo = multNumbers[i];
    altSequence.push(seqEle * multNo * shift);
  }

  return altSequence;
};

const generatePositions = (
  noOfNodes: number,
  terminalData: any,
  altSequence: number[],
  originalPosition: IPosition
) => {
  let positions = [];
  if (noOfNodes === 1) {
    positions.push(originalPosition);
  } else {
    positions = terminalData.map((_: any, i: number) => ({
      x: originalPosition.x - altSequence[i],
      y: originalPosition.y,
    }));
  }

  if (noOfNodes % 2 !== 0) {
    positions.unshift(originalPosition);
    positions.pop();
  }

  return positions;
};

export const GenerateFlowstationNodePositions = (
  flowStationsUnique: string[],
  initialFlowstationNode: IPosition,
  nodeToNodeGap: number
) => {
  const noOfNodes = flowStationsUnique.length;
  const shift = 120;
  const multNumbers = generateRepeatingSequence(noOfNodes);
  const altSequence = generateAltSequence(shift, noOfNodes, multNumbers);
  const positions = generatePositions(
    noOfNodes,
    flowStationsUnique,
    altSequence,
    initialFlowstationNode
  );

  return positions;
};

export const GenerateGasfacilityNodePositions = (
  gasFacilitiesUnique: string[]
) => {
  const originalPosition = { x: 900, y: 100 };
  const noOfNodes = gasFacilitiesUnique.length;
  const shift = 120;
  const multNumbers = generateRepeatingSequence(noOfNodes);
  const altSequence = generateAltSequence(shift, noOfNodes, multNumbers);
  const positions = generatePositions(
    noOfNodes,
    gasFacilitiesUnique,
    altSequence,
    originalPosition
  );

  return positions;
};

export const GenerateManifoldNodePositions = (
  flowstationNodes: any,
  gasFacilityNodes: any
) => {
  const flowstationGasFacilityNodes = [
    ...flowstationNodes,
    ...gasFacilityNodes,
  ];

  const positions = flowstationGasFacilityNodes.map((node) => {
    const position = { x: node.position.x, y: 250 };

    return position;
  });

  return positions;
};

export const GenerateDrainagePointNodePositions = (
  manifoldPosition: any,
  drainagePointTitles: string[],
  drainagePointGroupOffset: number
) => {
  const uniqueDrainagePointTitles = uniq(drainagePointTitles);

  const positions = SolveDrainagePointNodePositionsSquare(
    manifoldPosition,
    uniqueDrainagePointTitles.length,
    drainagePointGroupOffset
  );

  return positions;
};

export const GenerateDrainagePointSummaryNodePositions = (
  manifoldNodes: any
) => {
  const drainagePointSummaryNodePositions = manifoldNodes.map((node: any) => {
    return {
      x: node.position.x,
      y: node.position.y + 100,
    };
  });

  return drainagePointSummaryNodePositions;
};
