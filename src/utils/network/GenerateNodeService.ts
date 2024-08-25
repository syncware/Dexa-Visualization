import { v4 } from 'uuid';
import { FlowElement, XYPosition, nodeDimensions } from '../../types';

const generateNodeService = (
  nodeType: keyof typeof nodeDimensions,
  newPosition?: XYPosition,
  nodeLabel?: string,
  facilitiesData?: any
) => {
  const currentDimensions = nodeDimensions[nodeType];
  const newElement = {
    id: v4(),
    type: `${nodeType}Node`,
    data: {
      type: nodeType,
      label: nodeLabel,
      facilitiesData
    },
    style: {
      width: currentDimensions[0],
      height: currentDimensions[1],
      padding: '0px',
      borderColor: '#31BFCC',
    },
    position: { x: 0, y: 0, ...newPosition } as XYPosition,
  } as FlowElement;

  return newElement;
};

export default generateNodeService;
