export interface ForecastFacility {
  id: string;
  title: string;
  modules: Array<ForecastResultsByModule>;
}

export interface ForecastResultsByModule {
  id: string;
  title: string;
  forecastResults: Array<ForecastResult>;
}

export interface ForecastResult {
  id: string;
  uniqueId: string;
  day: number;
  month: number;
  year: number;
  oilRate: number;
  gasRate: number;
  waterRate: number;
  liquidRate: number;
  gasFlare: number;
  GOR: number;
  CGR: number;
  BSW: number;
  WGR: number;
  cumOilProd: number;
  cumGasProd: number;
  cumWaterProd: number;
  description?: string;
  decisionVariable: number;
  ownUseGas: number;
  gasDemand: number;
  crudeOilLosses: number;
  moduleName: string; // well name
  customDate: string;
  hydrocarbonStream: string;
  hydrocarbonType: string;
  terminal: string;
  cutBack: number;
  URo: number;
  URg: number;
  isFlowing: boolean;
  cutBackUpperBound: number;
  isPlateau: boolean;
  declineRate: number;

  forecastVersion: string;
  asset: string;
  field: string;
  reservoir: string;
  drainagePoint: string;
  string: string;
  facilities: string;
  developmentTranche: string;
}
export interface ForecastScenarioCase {
  id: string;
  userId: string;
  forecastResultsId: string;
  networkId: string;
  facilities: Array<ForecastFacility>;
}
