//import { FlowElement, XYPosition } from "react-flow-renderer";

import { v4 } from "uuid";
import { XYPosition, FlowElement } from "../../types";
export interface NodeDimensionsType {
  [key: string]: [string, string];
}

const nodeDimensions: NodeDimensionsType = {
  drainagePointSummary: ["50px", "30px"],
  drainagePoint: ["20px", "20px"],
  manifold: ["60px", "40px"],
  flowstation: ["60px", "40px"],
  gasProcessingFacility: ["60px", "40px"],
  gatheringCenter: ["80px", "40px"],
  terminal: ["80px", "40px"],
};

const GenerateNodeByPositionService = (
  nodeType: string,
  nodePosition: XYPosition
) => {
  const CurrentDimensions = nodeDimensions[nodeType];

  const newElement: FlowElement = {
    id: v4(),
    type: `${nodeType}Node`,
    data: {
      label: nodeType,
    },
    style: {
      width: CurrentDimensions[0],
      height: CurrentDimensions[1],
      padding: "0px",
      borderColor: "#31BFCC",
    },
    position: nodePosition,
  };
  return newElement;
};

export default GenerateNodeByPositionService;
