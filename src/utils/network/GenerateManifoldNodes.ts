import generateNodeService from "./GenerateNodeService";

const GenerateManifoldNodes = (
  flowstationNodes: any,
  gasFacilityNodes: any,
  stationManifoldGap: number
) => {
  const flowstationGasFacilityNodes = [
    ...flowstationNodes,
    ...gasFacilityNodes,
  ];
  const manifoldPositions = flowstationGasFacilityNodes.map((node) => {
    const position = {
      x: node.position.x,
      y: node.position.y + stationManifoldGap,
    };

    return position;
  });

  const manifoldNodes = flowstationGasFacilityNodes.map((stationNode, i) => {
    if (stationNode && stationNode !== undefined) {
      const manifoldNode = generateNodeService("manifold");

      const stationTitle = stationNode.data.stationData.title;
      const title = `${stationTitle} Manifold`;
      const drainagePoints = stationNode.data.stationData.drainagePoints;

      const manifoldNodeUpdated = {
        ...manifoldNode,
        data: {
          ...manifoldNode.data,
          title,
          type: "Manifold",
          drainagePoints,
        },
        position: manifoldPositions[i],
      };

      return manifoldNodeUpdated;
    }
  });

  return manifoldNodes;
};

export default GenerateManifoldNodes;
