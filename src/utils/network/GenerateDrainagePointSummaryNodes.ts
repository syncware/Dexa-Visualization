import { IPosition } from "../../types";
import generateNodeService from "./GenerateNodeService";

const GenerateDrainagePointSummaryNodes = (
  manifoldNodes: any,
  manifoldDrainagePointSummaryGap: number
) => {
  const drainagePointSummaryNodePositions = manifoldNodes.map(
    (node: any, i: number) => ({
      x: node.position.x,
      y: node.position.y + manifoldDrainagePointSummaryGap,
    })
  );

  const drainagePointSummaryNodes = drainagePointSummaryNodePositions.map(
    (drainagePointSummaryPosition: IPosition, i: number) => {
      if (
        Object.keys(drainagePointSummaryPosition).length > 0 &&
        drainagePointSummaryPosition !== undefined
      ) {
        const drainagePointSummaryNode = generateNodeService(
          "drainagePointSummary"
        );

        const node = manifoldNodes[i];
        const { drainagePoints } = node.data;

        const drainagePointNodeUpdated = {
          ...drainagePointSummaryNode,
          data: {
            ...drainagePointSummaryNode.data,
            type: "Drainage Point Summary",
            drainagePoints,
          },
          position: drainagePointSummaryPosition,
        };

        return drainagePointNodeUpdated;
      }
    }
  );

  return drainagePointSummaryNodes;
};

export default GenerateDrainagePointSummaryNodes;
