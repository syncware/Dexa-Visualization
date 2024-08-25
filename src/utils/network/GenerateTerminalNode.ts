import { IPosition } from "../../types";
import generateNodeService from "./GenerateNodeService";

const GenerateTerminalNode = (
  terminal: string,
  terminalPosition: IPosition
) => {
  const terminalNode = generateNodeService("terminal");

  const terminalNodeUpdated = {
    ...terminalNode,
    data: { ...terminalNode.data, title: terminal },
    position: terminalPosition,
  };

  return terminalNodeUpdated;
};

export default GenerateTerminalNode;
