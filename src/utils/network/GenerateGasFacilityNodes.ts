import { uniq } from "lodash";
import generateNodeService from "./GenerateNodeService";
import { IPosition } from "../../types";

const GenerateGasFacilityNodes = (
  gasFacilitiesData: any,
  facilitiesData: any,
  initialGasFacilityNode: IPosition,
  nodeToNodeGap: number
) => {
  const gasFacilitiesUnique = Object.keys(gasFacilitiesData);

  const gasfacilityPositions = gasFacilitiesUnique.map((_, i) => ({
    x: initialGasFacilityNode.x + i * nodeToNodeGap,
    y: initialGasFacilityNode.y,
  }));

  const gasFacilityNodes = gasFacilitiesUnique.map((key: string, i) => {
    const data = gasFacilitiesData[key];

    if (data && data !== undefined) {
      const title = key;
      const gasFacilityNode = generateNodeService("gasProcessingFacility");

      const gasFacilityNodeUpdated = {
        ...gasFacilityNode,
        data: {
          ...gasFacilityNode.data,
          facilitiesData: facilitiesData[key],
          stationData: {
            title,
            type: "Gas Facility",
            drainagePoints: uniq(data.map((row: any) => row["drainagePoint"])),
            stationInfo: data,
          },
        },
        position: gasfacilityPositions[i],
      };

      return gasFacilityNodeUpdated;
    }
  });

  return gasFacilityNodes;
};

export default GenerateGasFacilityNodes;
