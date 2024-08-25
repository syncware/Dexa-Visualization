import generateNodeService from "./GenerateNodeService";
import { GenerateDrainagePointNodePositions } from "./GenerateNodePositions";

const injectDrainagePointPositions = (
  drainagePointPositions: any,
  drainagePointTitles: string[],
  stationTitle: string
) => {
  const drainagePointNodes = drainagePointPositions.map(
    (drainagePointPosition: any, i: any) => {
      if (Object.keys(drainagePointPosition).length > 0) {
        const drainagePointNode = generateNodeService("drainagePoint");

        const drainagePointNodeUpdated = {
          ...drainagePointNode,
          data: {
            ...drainagePointNode.data,
            title: drainagePointTitles[i],
            type: "Drainage Point",
            station: stationTitle,
          },
          position: drainagePointPosition,
        };

        return drainagePointNodeUpdated;
      }
    }
  );

  return drainagePointNodes;
};

export const GenerateDrainagePointNodes = (manifoldNodes: any) => {
  const drainagePointNodes: any = {};

  let i = 1;
  for (const node of manifoldNodes) {
    const drainagePointGroupOffset = i % 2 === 0 ? 50 : 100;

    const manifoldPosition = node.position;
    const drainagePointTitles = node.data.drainagePoints;
    const stationTitle = node.data.title.replace(" Manifold", "");

    const drainagePointNodePositions = GenerateDrainagePointNodePositions(
      manifoldPosition,
      drainagePointTitles,
      drainagePointGroupOffset
    );

    const nodes = injectDrainagePointPositions(
      drainagePointNodePositions,
      drainagePointTitles,
      stationTitle
    );

    drainagePointNodes[stationTitle] = nodes;

    i += 1;
  }

  return drainagePointNodes;
};

export default GenerateDrainagePointNodes;
