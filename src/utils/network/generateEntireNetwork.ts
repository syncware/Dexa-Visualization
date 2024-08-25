import { groupBy } from 'lodash';
import { INetwork } from '../../types';
import calculateNetworkDiagramWidth from './CalculateNetworkDiagramWidth';
import ConnectDrainagePointSummariesToManifolds from './ConnectDrainagePointSummariesToManifolds';
import ConnectDrainagePointsToManifolds from './ConnectDrainagePointsToManifolds';
import ConnectFlowstationsToTerminal from './ConnectFlowstationsToTerminal';
import ConnectManifoldsToStations from './ConnectManifoldsToStations';
import GenerateDrainagePointNodes from './GenerateDrainagePointNodes';
import GenerateDrainagePointSummaryNodes from './GenerateDrainagePointSummaryNodes';
import GenerateFlowstationNodes from './GenerateFlowstationNodes';
import GenerateGasFacilityNodes from './GenerateGasFacilityNodes';
import GenerateManifoldNodes from './GenerateManifoldNodes';
import GenerateTerminalNode from './GenerateTerminalNode';
import SplitFlowstationsGasFacilities from './SplitFlowstationsGasFacilities';


export function generateEntireNetwork(
  forecastInputDeck: any,
  facilitiesInputDeck: any,
  showDrainagePointSummaryNodes: boolean,
  showDrainagePointSummaryEdges: boolean
): object {
  let network = { nodes: [], edges: [] } as INetwork;

  let terminalXPosition = 0;
  let totalEasternmostX = 0;
  const nodeWidth = 40;
  const nodeToNodeGapFactor = 2;
  const nodeToNodeGap = nodeToNodeGapFactor * nodeWidth;
  const flowstationGasFacilityGap = 100;
  const terminalStationGap = 120;
  const stationManifoldGap = 120;
  const manifoldDrainagePointSummaryGap = 120;

  //Group facilities by station
  const facilitiesData = groupBy(
    facilitiesInputDeck,
    (row: any) => row['primary']
  );

  //Group forecast by terminal
  const forecastDataByTerminal = groupBy(
    forecastInputDeck,
    (row: any) => row['terminal']
  );

  let i = 0;
  for (const terminal of Object.keys(forecastDataByTerminal)) {
    let allNodes = [];
    let allEdges = [];

    const forecastDeck = forecastDataByTerminal[terminal];

    //Group forecast data by station
    const forecastDataByStation = groupBy(
      forecastDeck,
      (row: any) => row['flowStation']
    );

    const { flowStationsData, gasFacilitiesData } =
      SplitFlowstationsGasFacilities(forecastDataByStation);

    //Network width
    const networkWidth = calculateNetworkDiagramWidth({
      flowStationsData,
      gasFacilitiesData,
      nodeToNodeGap,
      nodeWidth,
      flowstationGasFacilityGap,
    });

    const terminalYPosition = 30;
    totalEasternmostX += networkWidth;
    if (i === 0) {
      terminalXPosition = networkWidth / 2;
    } else {
      terminalXPosition = totalEasternmostX - networkWidth / 2;
    }
    const terminalPosition = {
      x: Math.floor(terminalXPosition),
      y: terminalYPosition,
    };

    //Nodes
    const terminalNode = GenerateTerminalNode(terminal, terminalPosition);

    const initialFlowstationNode = {
      x: terminalPosition.x - nodeWidth,
      y: terminalYPosition + terminalStationGap,
    };
    const flowstationNodes = GenerateFlowstationNodes(
      flowStationsData,
      facilitiesData,
      initialFlowstationNode,
      nodeToNodeGap
    );

    const initialGasFacilityNode = {
      x: terminalPosition.x + nodeWidth,
      y: terminalYPosition + terminalStationGap,
    };
    const gasFacilityNodes = GenerateGasFacilityNodes(
      gasFacilitiesData,
      facilitiesData,
      initialGasFacilityNode,
      nodeToNodeGap
    );

    const manifoldNodes = GenerateManifoldNodes(
      flowstationNodes,
      gasFacilityNodes,
      stationManifoldGap
    );

    const drainagePointNodes = GenerateDrainagePointNodes(manifoldNodes);

    const drainagePointNodesMerged = [];
    for (const node of Object.values(drainagePointNodes)) {
      drainagePointNodesMerged.push(node);
    }

    const drainagePointSummaryNodes = GenerateDrainagePointSummaryNodes(
      manifoldNodes,
      manifoldDrainagePointSummaryGap
    );
    const drainagePointOrSummaryNodes = showDrainagePointSummaryNodes
      ? drainagePointSummaryNodes
      : drainagePointNodesMerged;

    allNodes = [
      terminalNode,
      ...flowstationNodes,
      ...gasFacilityNodes,
      ...manifoldNodes,
      ...drainagePointOrSummaryNodes,
    ];

    //Edges
    const flowstationTerminalEdges = ConnectFlowstationsToTerminal(
      terminalNode,
      flowstationNodes,
      gasFacilityNodes
    );
    const manifoldFlowstationEdges = ConnectManifoldsToStations(
      manifoldNodes,
      flowstationNodes,
      gasFacilityNodes
    );
    const drainagePointManifoldEdges = ConnectDrainagePointsToManifolds(
      drainagePointNodes,
      manifoldNodes
    );

    const drainagePointSummaryManifoldEdges =
      ConnectDrainagePointSummariesToManifolds(
        drainagePointSummaryNodes,
        manifoldNodes
      );
    const drainagePointOrSummaryEdges = showDrainagePointSummaryEdges
      ? drainagePointSummaryManifoldEdges
      : drainagePointManifoldEdges;

    allEdges = [
      ...flowstationTerminalEdges,
      ...manifoldFlowstationEdges,
      ...drainagePointOrSummaryEdges,
    ];

    i += 1;

    network = {
      nodes: [...network.nodes, ...allNodes],
      edges: [...network.edges, ...allEdges],
    };
  }

  return network;
}
