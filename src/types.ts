import { Request } from "express";
import { NetworkNode, NetworkEdge } from "./models/network";

export declare type FlowElement<T = any> = NetworkNode | NetworkEdge;
export interface XYPosition {
  x: number;
  y: number;
}
export declare enum ArrowHeadType {
  Arrow = "arrow",
  ArrowClosed = "arrowclosed",
}

export interface ISelectOption {
    value: string | undefined;
    label: string;
    id?: string;
    title?: string;
    description?: string;
  }
  
  export interface ISingleInput {
    id?: string;
    title?: string;
    value: number | null;
    unit: string;
  }

  export type TRequestWithMetadata = Request & { currentUser: any }

  export type IRawRow = Record<string, string | number>;

  export interface INetwork {
    nodes: any[];
    edges: any[];
  }
  export interface IPosition {
    x: number;
    y: number;
  }  

  export interface NodeDimensionsType {
    [key: string]: [string, string];
  }
  
  export const nodeDimensions = {
    drainagePointSummary: ['50px', '30px'],
    drainagePoint: ['20px', '20px'],
    manifold: ['60px', '40px'],
    centralProcessingFacility: ['60px', '40px'],
    gasProcessingFacility: ['60px', '40px'],
    flowstation: ['60px', '40px'],
    oilPipeline: ['60px', '40px'],
    gasPipeline: ['60px', '40px'],
    oilTrunkline: ['60px', '40px'],
    gasTrunkline: ['60px', '40px'],
    terminal: ['80px', '40px'],
    subseaManifold: ['60px', '40px'],
    subseaTemplate: ['60px', '40px'],
    umbilical: ['60px', '40px'],
    productionPlatform: ['60px', '40px'],
    fso: ['60px', '40px'],
    fpso: ['60px', '40px'],
    dehydrationUnit: ['60px', '40px'],
    gasDemand: ['60px', '40px'],
  };

  export type TNodeDimensions = typeof nodeDimensions
  export type TNodeDimensionsKey = keyof TNodeDimensions