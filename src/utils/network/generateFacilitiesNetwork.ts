import { keys, omit, omitBy, orderBy, set } from 'lodash';
import { IRawRow, TNodeDimensionsKey } from '../../types';
import generateEdgeService from './GenerateEdgeService';
import generateNodeService from './GenerateNodeService';

// Global all nodes and all edges collections
// Global nodes map {1: [node1, node2], 2: [node3, node4]}
let allNodes = [] as any[];
let allEdges = [] as any[];
let deepestY = 0;
let currentNodePosition = { x: 0, y: 0 }; // First node position
let uniqueNodeNames = [] as string[];
let globalFacilitiesNodesMap = {} as Record<string, any>;

export function generateFacilitiesNetwork(props: any) {
  const productionEquipments = props?.facilitiesInputDeck?.productionEquipments;
  const facilitiesInputDeck = props?.facilitiesInputDeck?.inputDeckData;
  const forecastInputDeck = props?.forecastInputDeck?.inputDeckData;
  const facilitiesData = props?.facilitiesData;
  const shouldAddFacilitiesDataOrMnfldAndDPSNodes =
    forecastInputDeck && facilitiesData;

  // Get all unique gas demands
  const gasDemands = productionEquipments.filter(
    (row: any) => row.productionEquipmentType === 'gasDemand'
  );

  // Get all unique terminals
  const terminals = productionEquipments.filter(
    (row: any) => row.productionEquipmentType === 'terminal'
  );

  // Start with gasDemands and generate row by row
  // skipping nodes already generated
  for (const gasDemandRow of gasDemands) {
    // Get all node rows in facilities deck that is associated with current gasdemand
    const gasDemandName = gasDemandRow?.productionEquipment;
    const facilitiesRelatedToGasDemand = getFacilitiesForTerminalOrGasDemand(
      gasDemandName,
      facilitiesInputDeck
    );
    const { nodes } = generateNodesForTerminalOrGasDemand(
      gasDemandName,
      productionEquipments,
      facilitiesRelatedToGasDemand,
      shouldAddFacilitiesDataOrMnfldAndDPSNodes,
      facilitiesData
    );

    // Update global nodes and edges per gas demand
    allNodes.push(...nodes);
  }

  // Continue with terminals and generate row by row
  // skipping nodes already generated
  for (const terminalRow of terminals) {
    // Get all node rows in facilities deck that is associated with current terminal
    const terminalName = terminalRow?.productionEquipment;
    const facilitiesRelatedToTerminal = getFacilitiesForTerminalOrGasDemand(
      terminalName,
      facilitiesInputDeck
    );
    const { nodes } = generateNodesForTerminalOrGasDemand(
      terminalName,
      productionEquipments,
      facilitiesRelatedToTerminal,
      shouldAddFacilitiesDataOrMnfldAndDPSNodes,
      facilitiesData
    );

    // Update global nodes and edges per terminal
    allNodes.push(...nodes);
  }

  // If a forecastInputDeck is present, then we will generate
  // the entire network, add manifolds and drainagepoint summary nodes
  if (shouldAddFacilitiesDataOrMnfldAndDPSNodes) {
    addManifoldsAndDrainagePtSummaries();
  }

  // Generate all edges
  generateAllEdges(facilitiesInputDeck.slice(2));

  // Return nodes and edges to route
  return { nodes: allNodes, edges: allEdges };
}

// Generate nodes
const generateNodesForTerminalOrGasDemand = (
  terminalOrGasDemandName: string,
  productionEquipments: IRawRow[],
  facilitiesRowsForTerminalOrGasDemand: IRawRow[],
  shouldAddFacilitiesDataOrMnfldAndDPSNodes: boolean,
  facilitiesData: Record<string, any>
) => {
  // Facilities nodeMap for terminal or gas demand
  let facilitiesNodesMapForTerminalOrGasDemand = {} as Record<string, any>;

  // Keep track of all rows for this terminal
  let rowIdx = 0;
  let yline = 0;
  const interRowGap = 50;
  for (const facilityRow of facilitiesRowsForTerminalOrGasDemand) {
    // Get all node names in current row, do it from terminal and back
    // to flowstation
    const nodeLabels = Object.values(omit(facilityRow, 'sn')).filter(
      (nodeLabel) => !!nodeLabel
    ) as string[];

    // For current nodes row
    let nodeIdx = 0;
    const ylevel = yline + deepestY;
    for (const nodeLabel of nodeLabels) {
      // if node exists in uniqueNodeNames, skip to next node
      if (uniqueNodeNames.includes(nodeLabel)) {
        continue;
      }
      // Start generating nodes and storing in global map
      // 1. get node type
      const nodeType = getNodeTypeRow(
        nodeLabel,
        productionEquipments
      ) as TNodeDimensionsKey;

      // 2. Determine node position using its type
      // If the node is a flowstation or gas processing facility,
      // distribute vertically downwards after the first one is plotted
      // for other nodes, distribute horizontally
      const isRootNode = isRootNodeByType(nodeType);
      if (isRootNode) {
        currentNodePosition = { x: 0, y: ylevel };
      } else {
        currentNodePosition = { x: currentNodePosition.x + 200, y: ylevel };
      }

      // 3. Generate node from type and add info from crudelosses,
      // capacities and deferments deck if available
      let dataForFacility = {
        capacities: [],
        deferments: [],
        crudeLosses: [],
        flareGas: [],
        ownUseGas: [],
      };
      if (shouldAddFacilitiesDataOrMnfldAndDPSNodes) {
        dataForFacility = getFacilitiesDataForNode(nodeLabel, facilitiesData);
      }
      const node = generateNodeService(
        nodeType,
        currentNodePosition,
        nodeLabel,
        dataForFacility
      );

      // 4. Add node name to unique nodes
      uniqueNodeNames.push(nodeLabel);

      // 4. Add node to facility nodes map
      const noOfNodes =
        facilitiesNodesMapForTerminalOrGasDemand?.[rowIdx]?.length || 0;
      const nodePath = `${rowIdx}.${noOfNodes}`;
      set(facilitiesNodesMapForTerminalOrGasDemand, nodePath, node);

      // Increment
      nodeIdx += 1;
    }
    // Increment Y so nodes on next row is plotted on next line
    yline += interRowGap;

    rowIdx += 1;
  }

  // deepestY is bottom edge of previously drawn subnetwork
  // add buffer for next subnetwork
  deepestY = currentNodePosition.y + 100;

  // Reset currentNodePosition to 0,0
  currentNodePosition = { x: 0, y: 0 };

  // Get nodes collection from nodes map
  let nodes = [];
  for (const key in facilitiesNodesMapForTerminalOrGasDemand) {
    const nodesForRow = facilitiesNodesMapForTerminalOrGasDemand[key];
    nodes.push(...nodesForRow);
  }

  // Place nodes map in globalFacilitiesNodesMap
  globalFacilitiesNodesMap[terminalOrGasDemandName] =
    facilitiesNodesMapForTerminalOrGasDemand;

  return { nodes };
};

// Generate edges
const generateAllEdges = (facilitiesInputDeck: IRawRow[]) => {
  // Global edges map[node1, node2]
  let facilityEdges = [] as any[];

  for (const facilityRow of facilitiesInputDeck) {
    // Get all node names in current row, do it from terminal and back
    // to flowstation
    const nodeLabels = Object.values(omit(facilityRow, 'sn')).filter(
      (nodeLabel) => !!nodeLabel
    ) as string[];

    // Get current node and previous node
    for (let idx = 0; idx < nodeLabels.length; idx++) {
      const currentNodename = nodeLabels[idx];
      const nextNodename = nodeLabels[idx + 1];
      const { currentNode, nextNode } = getCurrentAndNextNodes(
        currentNodename,
        nextNodename
      );
      // Create edge node from these nodes
      const defaultEdge = generateEdgeService();
      const edge = {
        ...defaultEdge,
        source: currentNode?.id,
        target: nextNode?.id,
      };

      facilityEdges.push(edge);
    }
  }

  allEdges.push(...facilityEdges);
};

// Get node type using productionEquipments map
const getNodeTypeRow = (name: string, productionEquipments: IRawRow[]) => {
  let equipmentRow = {} as any;
  for (const row of productionEquipments) {
    if (row.productionEquipment === name) {
      equipmentRow = row;
      break;
    }
  }
  return equipmentRow.productionEquipmentType;
};

// Get the current node and previous node along the flow path
const getCurrentAndNextNodes = (
  currentNodename: string,
  nextNodename: string
) => {
  const currentNode = findNode(currentNodename);
  const nextNode = findNode(nextNodename);
  return { currentNode, nextNode };
};

// Find node within global facilities map
const findNode = (nodeLabel: string) => {
  // Search for searchNode
  let searchNode;
  outerloop: for (const terminalOrGasDemand in globalFacilitiesNodesMap) {
    const terminalOrGasDemandMap =
      globalFacilitiesNodesMap[terminalOrGasDemand];
    for (const key in terminalOrGasDemandMap) {
      const nodes = terminalOrGasDemandMap[key];
      searchNode = nodes?.find((node: any) => node.data?.label === nodeLabel);
      if (searchNode) {
        break outerloop;
      }
    }
  }
  return searchNode;
};

// Get all the data rows for specific terminal or gas demand
const getFacilitiesForTerminalOrGasDemand = (
  name: string,
  facilitiesInputDeck: IRawRow[]
) => {
  let facilitiesRows = [];
  for (const row of facilitiesInputDeck) {
    if (Object.values(row).includes(name)) {
      facilitiesRows.push(row);
    }
  }
  const filterredFacilitiesRows = facilitiesRows.map((row) => {
    const newRow = omitBy(row, (vK) => !vK);
    const updatedRow = omit(newRow, ['sn']);
    return updatedRow;
  });
  const sortedFacilitiesRows = orderBy(
    filterredFacilitiesRows,
    [(obj) => keys(obj)?.length],
    ['desc']
  );
  return sortedFacilitiesRows;
};

// Check if node is flowstation or gas processing facility
const isRootNodeByType = (nodeType: string) => {
  return ['flowstation', 'gasProcessingFacility'].includes(nodeType);
};

// Add manifolds and drainge pt summary nodes
const addManifoldsAndDrainagePtSummaries = () => {
  for (const terminalOrGasDemandName in globalFacilitiesNodesMap) {
    const terminalOrGasDemandMap =
      globalFacilitiesNodesMap[terminalOrGasDemandName];

    for (const key in terminalOrGasDemandMap) {
      const nodes = terminalOrGasDemandMap[key];
      const rootNode = nodes?.[0];
      const nodeType = rootNode?.data?.type;
      const nodeLabel = rootNode?.data?.label;

      if (!isRootNodeByType(nodeType)) {
        continue;
      }

      // Add manifold node
      const manifoldPosition = {
        x: rootNode?.position.x - 120,
        y: rootNode?.position.y,
      };
      const manifoldNode = generateNodeService(
        'manifold',
        manifoldPosition,
        `${nodeLabel}_Manifold`
      );
      const updatedNodesWidthManifold = [manifoldNode, ...nodes];
      globalFacilitiesNodesMap[terminalOrGasDemandName][key] =
        updatedNodesWidthManifold;
      allNodes.push(manifoldNode); // Update all nodes

      // Add drainage point summary node
      const drainagePointSummaryPosition = {
        x: manifoldPosition?.x - 120,
        y: manifoldPosition?.y,
      };
      const drainagePointNode = generateNodeService(
        'drainagePointSummary',
        drainagePointSummaryPosition,
        `${nodeLabel}_DrainagePoints`
      );
      const updatedDrainagePointNodes = [
        drainagePointNode,
        ...updatedNodesWidthManifold,
      ];
      globalFacilitiesNodesMap[terminalOrGasDemandName][key] =
        updatedDrainagePointNodes;
      allNodes.push(drainagePointNode); // Update all nodes

      // Add edge - Manifold and FS/GPF and
      // Create edge node from these nodes
      const defaultManifoldRootNodeEdge = generateEdgeService();
      const manifoldEdge = {
        ...defaultManifoldRootNodeEdge,
        source: manifoldNode?.id,
        target: rootNode?.id,
      };
      allEdges.push(manifoldEdge);

      // Add edge - Drainage point Summary and Manifold
      // Create edge node from these nodes
      const defaultDPSmanifoldEdge = generateEdgeService();
      const drainagePointSummaryEdge = {
        ...defaultDPSmanifoldEdge,
        source: drainagePointNode?.id,
        target: manifoldNode?.id,
      };
      allEdges.push(drainagePointSummaryEdge);
    }
  }
};

const getFacilitiesDataForNode = (
  nodeLabel: string,
  facilitiesData: Record<string, any>
): any => {
  const capacitiesDataMap =
    facilitiesData?.['equipmentCapacitiesMap']?.[nodeLabel];
  const defermentsDataMap =
    facilitiesData?.['equipmentDefermentsMap']?.[nodeLabel];
  const crudeLossesDataMap =
    facilitiesData?.['equipmentCrudeLossesMap']?.[nodeLabel];
  const flareGasDataMap = facilitiesData?.['equipmentFlareGasMap']?.[nodeLabel];
  const ownUseGasDataMap =
    facilitiesData?.['equipmentOwnUseGasMap']?.[nodeLabel];

  return {
    capacities: getInputDeckOrDatesInputSummary(capacitiesDataMap),
    deferments: getInputDeckOrDatesInputSummary(defermentsDataMap),
    crudeLosses: getInputDeckOrDatesInputSummary(crudeLossesDataMap),
    flareGas: getInputDeckOrDatesInputSummary(flareGasDataMap),
    ownUseGas: getInputDeckOrDatesInputSummary(ownUseGasDataMap),
  };
};

const getInputDeckOrDatesInputSummary = (dataMap: Record<string, any>) => {
  const inputTypeOption = dataMap?.inputTypeOption;
  if (inputTypeOption?.value === 'datesInput') {
    // filter data by columns with data only
    const data = dataMap?.datesInput?.slice(1)?.map((row: any) => {
      const updatedRow = omitBy(row, (v) => !v);
      return updatedRow;
    });

    // Also filter units row by the columns with data only
    let updatedUnitsRow = {} as Record<string, number | string>;
    const unitsRow = dataMap?.datesInput?.slice(0)[0];
    const names = Object.keys(data?.[0]);
    for (const name of names) {
      updatedUnitsRow[name] = unitsRow[name];
    }

    return [updatedUnitsRow, ...data];
  }

  // TODO: Please implement when data becomes available
  if (inputTypeOption?.value === 'inputDeck') {
  }

  return [];
};
