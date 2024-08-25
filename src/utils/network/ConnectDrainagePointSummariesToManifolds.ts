import generateEdgeService from "./GenerateEdgeService";

const ConnectDrainagePointSummariesToManifolds = (
  drainagePointSummaryNodes: any,
  manifoldNodes: any
) => {
  const allEdges = [];

  let i = 0;
  for (const manifoldNode of manifoldNodes) {
    const drainagePointSummaryNode = drainagePointSummaryNodes[i];

    const edge = generateEdgeService();

    const edgeUpdated = {
      ...edge,
      source: drainagePointSummaryNode.id,
      target: manifoldNode.id,
    };

    allEdges.push(edgeUpdated);

    i = i + 1;
  }
  return allEdges;
};

export default ConnectDrainagePointSummariesToManifolds;
