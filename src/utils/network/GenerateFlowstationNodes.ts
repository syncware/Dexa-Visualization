import { uniq } from "lodash";
import generateNodeService from "./GenerateNodeService";
import { IPosition } from "../../types";

const GenerateFlowstationNodes = (
  flowStationsData: any,
  facilitiesData: any,
  initialFlowstationNode: IPosition,
  nodeToNodeGap: number
) => {
  const flowStationsUnique = Object.keys(flowStationsData);

  const flowstationPositions = flowStationsUnique.map((_, i) => ({
    x: initialFlowstationNode.x - i * nodeToNodeGap,
    y: initialFlowstationNode.y,
  }));

  const flowstationNodes = flowStationsUnique.map((key: string, i) => {
    const data = flowStationsData[key];

    if (data && data !== undefined) {
      const title = key;
      const flowstationNode = generateNodeService("flowstation");

      const flowstationNodeUpdated = {
        ...flowstationNode,
        data: {
          ...flowstationNode.data,
          facilitiesData: facilitiesData[key],
          stationData: {
            title,
            type: "Flowstation",
            drainagePoints: uniq(data.map((row: any) => row["drainagePoint"])),
            stationInfo: data,
          },
        },
        position: flowstationPositions[i],
      };

      return flowstationNodeUpdated;
    }
  });

  return flowstationNodes;
};

export default GenerateFlowstationNodes;
