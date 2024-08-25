export interface ICalculateNetworkDiagramWidth {
  flowStationsData: Record<string, any>;
  gasFacilitiesData: Record<string, any>;
  nodeToNodeGap: number;
  nodeWidth: number;
  flowstationGasFacilityGap: number;
}

const calculateNetworkDiagramWidth = ({
  flowStationsData,
  gasFacilitiesData,
  nodeToNodeGap,
  nodeWidth,
  flowstationGasFacilityGap,
}: ICalculateNetworkDiagramWidth) => {
  const noOfFlowstationNodes = Object.keys(flowStationsData).length;
  const noOfGasFacilityNodes = Object.keys(gasFacilitiesData).length;

  const flowstationsBoxWidth =
    noOfFlowstationNodes * nodeWidth +
    nodeToNodeGap * (noOfFlowstationNodes - 1) +
    nodeWidth;

  const gasFacilitiesBoxWidth =
    noOfGasFacilityNodes * nodeWidth +
    nodeToNodeGap * (noOfGasFacilityNodes - 1) +
    nodeWidth;

  const networkBoxWidth =
    flowstationsBoxWidth + gasFacilitiesBoxWidth + flowstationGasFacilityGap;

  return networkBoxWidth;
};

export default calculateNetworkDiagramWidth;
