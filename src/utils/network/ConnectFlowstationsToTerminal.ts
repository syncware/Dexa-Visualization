import generateEdgeService from "./GenerateEdgeService";

const ConnectFlowstationsToTerminal = (
  terminalNode: any,
  flowstationNodes: any,
  gasFacilityNodes: any
) => {
  const allEdges = [];
  const flowstationGasFacilityNodes = [
    ...flowstationNodes,
    ...gasFacilityNodes,
  ];

  for (const flowstationGasfacility of flowstationGasFacilityNodes) {
    const edge = generateEdgeService();
    const edgeUpdated = {
      ...edge,
      source: flowstationGasfacility.id,
      target: terminalNode.id,
    };

    allEdges.push(edgeUpdated);
  }

  return allEdges;
};

export default ConnectFlowstationsToTerminal;
