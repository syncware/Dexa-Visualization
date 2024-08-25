import { v4 } from "uuid";
import { FlowElement } from "../../types";

const generateEdgeService = () => {
  const newEdge: FlowElement = {
    id: v4(),
    source: "0",
    target: "1",
    type: "smoothstep",
    arrowHeadType: "arrowclosed",
  };

  return newEdge;
};

export default generateEdgeService;
