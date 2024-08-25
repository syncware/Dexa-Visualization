import generateEdgeService from "./GenerateEdgeService";

const ConnectDrainagePointsToManifolds = (
  drainagePointNodesObj: any,
  manifoldNodes: any
) => {
  const allEdges = [];

  for (const manifoldNode of manifoldNodes) {
    const manifoldTitle = manifoldNode.data.title;
    const stationTitle = manifoldTitle.replace(" Manifold", "");
    const drainagePointNodes = drainagePointNodesObj[stationTitle];

    for (const drainagePointNode of drainagePointNodes) {
      const edge = generateEdgeService();

      const edgeUpdated = {
        ...edge,
        source: drainagePointNode.id,
        target: manifoldNode.id,
      };

      allEdges.push(edgeUpdated);
    }
  }
  return allEdges;
};

export default ConnectDrainagePointsToManifolds;
