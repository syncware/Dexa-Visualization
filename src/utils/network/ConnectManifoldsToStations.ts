import generateEdgeService from "./GenerateEdgeService";

const ConnectManifoldsToStations = (
  manifoldNodes: any,
  flowstationNodes: any,
  gasFacilityNodes: any
) => {
  const allEdges = [];
  const manifoldAndflowstationNodes = [
    ...flowstationNodes,
    ...gasFacilityNodes,
  ];

  for (const manifoldNode of manifoldNodes) {
    for (const stationNode of manifoldAndflowstationNodes) {
      const stationTitleFromManifold = manifoldNode.data.title.replace(
        " Manifold",
        ""
      );
      const stationTitle = stationNode.data.stationData.title;

      if (stationTitleFromManifold === stationTitle) {
        const edge = generateEdgeService();

        const edgeUpdated = {
          ...edge,
          source: manifoldNode.id,
          target: stationNode.id,
        };

        allEdges.push(edgeUpdated);

        break;
      }
    }
  }

  return allEdges;
};

export default ConnectManifoldsToStations;
