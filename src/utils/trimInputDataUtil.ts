import { isNumber } from 'lodash';
import { EquipmentCapacitiesProperties } from '../models/equipmentCapacities';
import { EquipmentCrudeLossesProperties } from '../models/equipmentCrudeLosses';
import { EquipmentDefermentsProperties } from '../models/equipmentDeferments';
import { ForecastIInputDeckEntity } from '../models/forecastInputDeck';
import { ForecastProfileEntity } from '../models/forecastProfiles';
import { RampUpProperties } from '../models/rampUp';
import { ReroutingProperties } from '../models/reRouting';
import { SalesPointProperties } from '../models/salesPoint';
import { ShutinOpenupProperties } from '../models/shutinOpenup';

export function trimLineForecastIInputDeckData(
  payloadinputDeck: ForecastIInputDeckEntity[],
  variableUnitTitles: any
) {
  for (let index = 0; index < payloadinputDeck.length; index++) {
    let x = payloadinputDeck[index];

    x.onStreamDate1P1C = x.onStreamDate2P2C;
    x.onStreamDate3P3C = x.onStreamDate2P2C;
    x.abandBSWWGR1P1C = x.abandBSWWGR2P2C;
    x.abandBSWWGR3P3C = x.abandBSWWGR2P2C;
    x.abandGORCGR1P1C = x.abandGORCGR2P2C;
    x.abandGORCGR3P3C = x.abandGORCGR2P2C;
    x.initOilGasRate1P1C = x.initOilGasRate2P2C;
    x.initOilGasRate3P3C = x.initOilGasRate2P2C;
    x.abandOilGasRate1P1C = x.abandOilGasRate2P2C;
    x.abandOilGasRate3P3C = x.abandOilGasRate2P2C;

    if (x.declineMethod === null || x.declineMethod === undefined) {
      payloadinputDeck[index].declineMethod = 'exponential';
    }

    if (x.forecastVersion === null || x.forecastVersion === undefined) {
      payloadinputDeck[index].forecastVersion = '';
    }
    if (x.asset === null || x.asset === undefined) {
      payloadinputDeck[index].asset = '';
    }
    if (x.field === null || x.field === undefined) {
      payloadinputDeck[index].field = '';
    }
    if (x.reservoir === null || x.reservoir === undefined) {
      payloadinputDeck[index].reservoir = '';
    }
    if (x.drainagePoint === null || x.drainagePoint === undefined) {
      payloadinputDeck[index].drainagePoint = '';
    }
    if (x.string === null || x.string === undefined) {
      payloadinputDeck[index].string = '';
    }
    if (x.module === null || x.module === undefined) {
      payloadinputDeck[index].module = '';
    }
    if (x.projectCode === null || x.projectCode === undefined) {
      payloadinputDeck[index].projectCode = '';
    }
    if (x.projectName === null || x.projectName === undefined) {
      payloadinputDeck[index].projectName = '';
    }
    if (x.facilities === null || x.facilities === undefined) {
      payloadinputDeck[index].facilities = '';
    }
    if (x.hydrocarbonStream === null || x.hydrocarbonStream === undefined) {
      payloadinputDeck[index].hydrocarbonStream = '';
    }
    if (x.hydrocarbonType === null || x.hydrocarbonType === undefined) {
      payloadinputDeck[index].hydrocarbonType = '';
    }
    if (x.terminal === null || x.terminal === undefined) {
      payloadinputDeck[index].terminal = '';
    }
    if (x.resourceClass === null || x.resourceClass === undefined) {
      payloadinputDeck[index].resourceClass = '';
    }
    if (x.onStreamDate2P2C === null || x.onStreamDate2P2C === undefined) {
      payloadinputDeck[index].onStreamDate2P2C = '1/1/2024';
    }
    if (x.onStreamDate1P1C === null || x.onStreamDate1P1C === undefined) {
      payloadinputDeck[index].onStreamDate1P1C =
        payloadinputDeck[index].onStreamDate2P2C;
    }
    if (x.onStreamDate3P3C === null || x.onStreamDate3P3C === undefined) {
      payloadinputDeck[index].onStreamDate3P3C =
        payloadinputDeck[index].onStreamDate2P2C;
    }
    if (x.remarks === null || x.remarks === undefined) {
      payloadinputDeck[index].remarks = '';
    }
    if (x.developmentTranche === null || x.developmentTranche === undefined) {
      payloadinputDeck[index].developmentTranche = '';
    }
    if (x.description === null || x.description === undefined) {
      payloadinputDeck[index].description = '';
    }
    if (!isNumber(x.oilUR1P1C)) {
      payloadinputDeck[index].oilUR1P1C = 0;
      variableUnitTitles.oilUR1P1C = variableUnitTitles.oilUR2P2C;
    }
    if (!isNumber(x.oilUR2P2C)) {
      payloadinputDeck[index].oilUR2P2C = 0;
    }
    if (!isNumber(x.oilUR3P3C)) {
      payloadinputDeck[index].oilUR3P3C = 0;
      variableUnitTitles.oilUR3P3C = variableUnitTitles.oilUR2P2C;
    }
    if (!isNumber(x.Np)) {
      payloadinputDeck[index].Np = 0;
    }
    if (!isNumber(x.Gp)) {
      payloadinputDeck[index].Gp = 0;
    }
    if (!isNumber(x.initOilGasRate1P1C)) {
      payloadinputDeck[index].initOilGasRate1P1C = 0;
      variableUnitTitles.initOilGasRate1P1C = variableUnitTitles.initOilGasRate2P2C;
    }
    if (!isNumber(x.initOilGasRate2P2C)) {
      payloadinputDeck[index].initOilGasRate2P2C = 0;
    }
    if (!isNumber(x.initOilGasRate3P3C)) {
      payloadinputDeck[index].initOilGasRate3P3C = 0;
      variableUnitTitles.initOilGasRate3P3C = variableUnitTitles.initOilGasRate2P2C;
    }
    if (!isNumber(x.abandBSWWGR1P1C)) {
      payloadinputDeck[index].abandBSWWGR1P1C = 0;
      variableUnitTitles.abandBSWWGR1P1C = variableUnitTitles.abandBSWWGR2P2C;
    }
    if (!isNumber(x.abandBSWWGR2P2C)) {
      payloadinputDeck[index].abandBSWWGR2P2C = 0;
    }
    if (!isNumber(x.abandBSWWGR3P3C)) {
      payloadinputDeck[index].abandBSWWGR3P3C = 0;
      variableUnitTitles.abandBSWWGR3P3C = variableUnitTitles.abandBSWWGR2P2C;
    }
    if (!isNumber(x.abandGORCGR1P1C)) {
      payloadinputDeck[index].abandGORCGR1P1C = 0;
      variableUnitTitles.abandGORCGR1P1C = variableUnitTitles.abandGORCGR2P2C;
    }
    if (!isNumber(x.abandGORCGR2P2C)) {
      payloadinputDeck[index].abandGORCGR2P2C = 0;
    }
    if (!isNumber(x.abandGORCGR3P3C)) {
      payloadinputDeck[index].abandGORCGR3P3C = 0;
      variableUnitTitles.abandGORCGR3P3C = variableUnitTitles.abandGORCGR2P2C;
    }
    if (!isNumber(x.abandOilGasRate1P1C)) {
      payloadinputDeck[index].abandOilGasRate1P1C = 0;
      variableUnitTitles.abandOilGasRate1P1C = variableUnitTitles.abandOilGasRate2P2C;
    }
    if (!isNumber(x.abandOilGasRate2P2C)) {
      payloadinputDeck[index].abandOilGasRate2P2C = 0;
    }
    if (!isNumber(x.abandOilGasRate3P3C)) {
      payloadinputDeck[index].abandOilGasRate3P3C = 0;
      variableUnitTitles.abandOilGasRate3P3C = variableUnitTitles.abandOilGasRate2P2C;
    }
    if (!isNumber(x.plateauPeriod)) {
      payloadinputDeck[index].plateauPeriod = 0;
    }
    if (!isNumber(x.initBSWWGR)) {
      payloadinputDeck[index].initBSWWGR = 0;
    }
    if (!isNumber(x.gasUR1P1C)) {
      payloadinputDeck[index].gasUR1P1C = 0;
      variableUnitTitles.gasUR1P1C = variableUnitTitles.gasUR2P2C;
    }
    if (!isNumber(x.gasUR2P2C)) {
      payloadinputDeck[index].gasUR2P2C = 0;
    }
    if (!isNumber(x.gasUR3P3C)) {
      payloadinputDeck[index].gasUR3P3C = 0;
      variableUnitTitles.gasUR3P3C = variableUnitTitles.gasUR2P2C;
    }
    if (!isNumber(x.initGORCGR)) {
      payloadinputDeck[index].initGORCGR = 0;
    }
  }
}

export const ConvertTextToNumber = (x: any) => {
  let y = 0;
  if (x === null || x === undefined || x == '') y = 0;
  else y = Number(x);
  return y;
};

export function TrimLineForecastProfilesData(inputDeckData: any[]) {
  const results = [] as ForecastProfileEntity[];
  for (let index = 0; index < inputDeckData.length; index++) {
    const x = {} as ForecastProfileEntity;

    if (
      inputDeckData[index].customDate != null &&
      inputDeckData[index].customDate != undefined &&
      inputDeckData[index].customDate != '\\r' &&
      inputDeckData[index].customDate != '' &&
      inputDeckData[index].moduleName != null &&
      inputDeckData[index].moduleName != undefined &&
      inputDeckData[index].moduleName != '\\r' &&
      inputDeckData[index].moduleName != ''
    ) {
      x.customDate = inputDeckData[index].customDate;
      x.moduleName = inputDeckData[index].moduleName;

      if (
        inputDeckData[index].hydrocarbonStream === null ||
        inputDeckData[index].hydrocarbonStream === undefined
      ) {
        x.hydrocarbonStream = 'oil';
      }

      x.CGR = ConvertTextToNumber(inputDeckData[index].CGR);
      x.BSW = ConvertTextToNumber(inputDeckData[index].BSW);
      x.GOR = ConvertTextToNumber(inputDeckData[index].GOR);
      x.WGR = ConvertTextToNumber(inputDeckData[index].WGR);
      x.cumOilProd = ConvertTextToNumber(inputDeckData[index].cumOilProd);
      x.cumGasProd = ConvertTextToNumber(inputDeckData[index].cumGasProd);
      x.oilRate = ConvertTextToNumber(inputDeckData[index].oilRate);
      x.gasRate = ConvertTextToNumber(inputDeckData[index].gasRate);

      results.push(x);
    }
  }

  return results;
}

export function TrimLineRampUpInputDeckData(RampUpInputDeck: RampUpProperties) {
  for (
    let index = 0;
    index < RampUpInputDeck.rampupModel.schedule.length;
    index++
  ) {
    const x = RampUpInputDeck.rampupModel.schedule[index];

    if (x.module === null || x.module === undefined) {
      RampUpInputDeck.rampupModel.schedule[index].module = '';
    }
    if (!isNumber(x.maximumPotential)) {
      RampUpInputDeck.rampupModel.schedule[index].maximumPotential = 0;
    }
    if (x.startDate === null || x.startDate === undefined) {
      RampUpInputDeck.rampupModel.schedule[index].startDate = '';
    }
    if (x.dcaStrategy === null || x.dcaStrategy === undefined) {
      RampUpInputDeck.rampupModel.schedule[index].dcaStrategy = '';
    }
    if (!isNumber(x.percentOfMaximumPotential)) {
      RampUpInputDeck.rampupModel.schedule[index].percentOfMaximumPotential = 0;
    }
    if (!isNumber(x.startupRatePlateau)) {
      RampUpInputDeck.rampupModel.schedule[index].startupRatePlateau = 0;
    }
    if (x.declineType === null || x.declineType === undefined) {
      RampUpInputDeck.rampupModel.schedule[index].declineType = '';
    }
    if (!isNumber(x.declineExponent)) {
      RampUpInputDeck.rampupModel.schedule[index].declineExponent = 0;
    }
    if (!isNumber(x.hyperbolicExponent)) {
      RampUpInputDeck.rampupModel.schedule[index].hyperbolicExponent = 0;
    }
  }
}

export function TrimLineReRoutingInputDeckData(
  ReroutingUpInputDeck: ReroutingProperties
) {
  for (
    let index = 0;
    index < ReroutingUpInputDeck.reroutingModel.schedule.length;
    index++
  ) {
    const x = ReroutingUpInputDeck.reroutingModel.schedule[index];

    if (x.module === null || x.module === undefined) {
      ReroutingUpInputDeck.reroutingModel.schedule[index].module = '';
    }
    if (x.rerouteDate === null || x.rerouteDate === undefined) {
      ReroutingUpInputDeck.reroutingModel.schedule[index].rerouteDate = '';
    }
    if (x.rerouteDestination === null || x.rerouteDestination === undefined) {
      ReroutingUpInputDeck.reroutingModel.schedule[index].rerouteDestination =
        '';
    }
    if (!isNumber(x.startupRate)) {
      ReroutingUpInputDeck.reroutingModel.schedule[index].startupRate = 0;
    }
    if (!isNumber(x.startupRatePlateau)) {
      ReroutingUpInputDeck.reroutingModel.schedule[
        index
      ].startupRatePlateau = 0;
    }
    if (x.declineType === null || x.declineType === undefined) {
      ReroutingUpInputDeck.reroutingModel.schedule[index].declineType = '';
    }
    if (!isNumber(x.declineExponent)) {
      ReroutingUpInputDeck.reroutingModel.schedule[index].declineExponent = 0;
    }
    if (!isNumber(x.hyperbolicExponent)) {
      ReroutingUpInputDeck.reroutingModel.schedule[
        index
      ].hyperbolicExponent = 0;
    }
  }
}

export function TrimLineShutInOpenUpInputDeckData(
  ShutInOpenUpInputDeck: ShutinOpenupProperties
) {
  for (
    let index = 0;
    index < ShutInOpenUpInputDeck.shutinOpenupModel.schedule.length;
    index++
  ) {
    const x = ShutInOpenUpInputDeck.shutinOpenupModel.schedule[index];

    if (x.module === null || x.module === undefined) {
      ShutInOpenUpInputDeck.shutinOpenupModel.schedule[index].module = '';
    }
    if (x.shutInDate === null || x.shutInDate === undefined) {
      ShutInOpenUpInputDeck.shutinOpenupModel.schedule[index].shutInDate = '';
    }
    if (x.event === null || x.event === undefined) {
      ShutInOpenUpInputDeck.shutinOpenupModel.schedule[index].event = '';
    }
    if (x.dcaStrategy === null || x.dcaStrategy === undefined) {
      ShutInOpenUpInputDeck.shutinOpenupModel.schedule[index].dcaStrategy = '';
    }
    if (!isNumber(x.startupRate)) {
      ShutInOpenUpInputDeck.shutinOpenupModel.schedule[index].startupRate = 0;
    }
    if (!isNumber(x.startupRatePlateau)) {
      ShutInOpenUpInputDeck.shutinOpenupModel.schedule[
        index
      ].startupRatePlateau = 0;
    }
    if (x.declineType === null || x.declineType === undefined) {
      ShutInOpenUpInputDeck.shutinOpenupModel.schedule[index].declineType = '';
    }
    if (!isNumber(x.declineExponent)) {
      ShutInOpenUpInputDeck.shutinOpenupModel.schedule[
        index
      ].declineExponent = 0;
    }
    if (!isNumber(x.hyperbolicExponent)) {
      ShutInOpenUpInputDeck.shutinOpenupModel.schedule[
        index
      ].hyperbolicExponent = 0;
    }
  }
}

// export function TrimLineEquipmentCapacitiesInputDeckData(
//   equipmentCapacitiesProperties: EquipmentCapacitiesProperties
// ) {
  
//   const equipmentCapacitiesMapKeys = Object.keys(
//     equipmentCapacitiesProperties.equipmentCapacitiesModel
//       .equipmentCapacitiesMap
//   );

//   const length = equipmentCapacitiesMapKeys.length;
//   for (let index = 0; index < length; index++) {
//     const schedules =
//       equipmentCapacitiesProperties.equipmentCapacitiesModel
//         .equipmentCapacitiesMap[equipmentCapacitiesMapKeys[index]];

//     for (let idx = 0; idx < schedules.length; idx++) {
//       const x = schedules[idx];
//       if (
//         x.equipmentCapacityDate === null ||
//         x.equipmentCapacityDate === undefined
//       ) {
//         equipmentCapacitiesProperties.equipmentCapacitiesModel.equipmentCapacitiesMap[
//           equipmentCapacitiesMapKeys[index]
//         ][idx].equipmentCapacityDate = '4/26/2024';
//       }
//       if (!isNumber(x.liquidCapacityLow)) {
//         equipmentCapacitiesProperties.equipmentCapacitiesModel.equipmentCapacitiesMap[
//           equipmentCapacitiesMapKeys[index]
//         ][idx].liquidCapacityLow = 0;
//       }
//       if (!isNumber(x.liquidCapacityBase)) {
//         equipmentCapacitiesProperties.equipmentCapacitiesModel.equipmentCapacitiesMap[
//           equipmentCapacitiesMapKeys[index]
//         ][idx].liquidCapacityBase = 0;
//       }
//       if (!isNumber(x.liquidCapacityHigh)) {
//         equipmentCapacitiesProperties.equipmentCapacitiesModel.equipmentCapacitiesMap[
//           equipmentCapacitiesMapKeys[index]
//         ][idx].liquidCapacityHigh = 0;
//       }
//       if (!isNumber(x.gasCapacityLow)) {
//         equipmentCapacitiesProperties.equipmentCapacitiesModel.equipmentCapacitiesMap[
//           equipmentCapacitiesMapKeys[index]
//         ][idx].gasCapacityLow = 0;
//       }
//       if (!isNumber(x.gasCapacityBase)) {
//         equipmentCapacitiesProperties.equipmentCapacitiesModel.equipmentCapacitiesMap[
//           equipmentCapacitiesMapKeys[index]
//         ][idx].gasCapacityBase = 0;
//       }
//       if (!isNumber(x.gasCapacityHigh)) {
//         equipmentCapacitiesProperties.equipmentCapacitiesModel.equipmentCapacitiesMap[
//           equipmentCapacitiesMapKeys[index]
//         ][idx].gasCapacityHigh = 0;
//       }
//     }
//   }
// }

// export function TrimLineCrudeLossesInputDeckData(
//   crudeLossesProperties: EquipmentCrudeLossesProperties
// ) {
//   const equipmentCrudeLossesMapKeys = Object.keys(
//     crudeLossesProperties.equipmentCrudeLossesModel.equipmentCrudeLossesMap
//   );
//   const length = equipmentCrudeLossesMapKeys.length;
//   for (let index = 0; index < length; index++) {
//     const schedules =
//       crudeLossesProperties.equipmentCrudeLossesModel.equipmentCrudeLossesMap[
//         equipmentCrudeLossesMapKeys[index]
//       ];
//     for (let idx = 0; idx < schedules.length; idx++) {
//       const x = schedules[idx];
//       if (
//         x.equipmentCrudeLossesDate === null ||
//         x.equipmentCrudeLossesDate === undefined
//       ) {
//         crudeLossesProperties.equipmentCrudeLossesModel.equipmentCrudeLossesMap[
//           equipmentCrudeLossesMapKeys[index]
//         ][idx].equipmentCrudeLossesDate = '4/26/2024';
//       }
//       if (!isNumber(x.equipmentCrudeLossesLow)) {
//         crudeLossesProperties.equipmentCrudeLossesModel.equipmentCrudeLossesMap[
//           equipmentCrudeLossesMapKeys[index]
//         ][idx].equipmentCrudeLossesLow = 0;
//       }
//       if (!isNumber(x.equipmentCrudeLossesBase)) {
//         crudeLossesProperties.equipmentCrudeLossesModel.equipmentCrudeLossesMap[
//           equipmentCrudeLossesMapKeys[index]
//         ][idx].equipmentCrudeLossesBase = 0;
//       }
//       if (!isNumber(x.equipmentCrudeLossesHigh)) {
//         crudeLossesProperties.equipmentCrudeLossesModel.equipmentCrudeLossesMap[
//           equipmentCrudeLossesMapKeys[index]
//         ][idx].equipmentCrudeLossesHigh = 0;
//       }
//     }
//   }
// }

// export function TrimLineDefermentsInputDeckData(
//   defermentsProperties: EquipmentDefermentsProperties
// ) {
//   const equipmentDefermentsMapKeys = Object.keys(
//     defermentsProperties.equipmentDefermentsModel.equipmentDefermentsMap
//   );
//   const length = equipmentDefermentsMapKeys.length;
//   for (let index = 0; index < length; index++) {
//     const schedules =
//       defermentsProperties.equipmentDefermentsModel.equipmentDefermentsMap[
//         equipmentDefermentsMapKeys[index]
//       ];
//     for (let idx = 0; idx < schedules.length; idx++) {
//       const x = schedules[idx];
//       if (
//         x.equipmentDefermentDate === null ||
//         x.equipmentDefermentDate === undefined
//       ) {
//         defermentsProperties.equipmentDefermentsModel.equipmentDefermentsMap[
//           equipmentDefermentsMapKeys[index]
//         ][idx].equipmentDefermentDate = '4/26/2024';
//       }
//       if (!isNumber(x.scheduledDefermentBase)) {
//         defermentsProperties.equipmentDefermentsModel.equipmentDefermentsMap[
//           equipmentDefermentsMapKeys[index]
//         ][idx].scheduledDefermentBase = 0;
//       }
//       if (!isNumber(x.scheduledDefermentLow)) {
//         defermentsProperties.equipmentDefermentsModel.equipmentDefermentsMap[
//           equipmentDefermentsMapKeys[index]
//         ][idx].scheduledDefermentLow = 0;
//       }
//       if (!isNumber(x.scheduledDefermentHigh)) {
//         defermentsProperties.equipmentDefermentsModel.equipmentDefermentsMap[
//           equipmentDefermentsMapKeys[index]
//         ][idx].scheduledDefermentHigh = 0;
//       }
//       if (!isNumber(x.unScheduledDefermentBase)) {
//         defermentsProperties.equipmentDefermentsModel.equipmentDefermentsMap[
//           equipmentDefermentsMapKeys[index]
//         ][idx].unScheduledDefermentBase = 0;
//       }
//       if (!isNumber(x.unScheduledDefermentLow)) {
//         defermentsProperties.equipmentDefermentsModel.equipmentDefermentsMap[
//           equipmentDefermentsMapKeys[index]
//         ][idx].unScheduledDefermentLow = 0;
//       }
//       if (!isNumber(x.unScheduledDefermentHigh)) {
//         defermentsProperties.equipmentDefermentsModel.equipmentDefermentsMap[
//           equipmentDefermentsMapKeys[index]
//         ][idx].unScheduledDefermentHigh = 0;
//       }
//       if (!isNumber(x.thirdPartyDefermentBase)) {
//         defermentsProperties.equipmentDefermentsModel.equipmentDefermentsMap[
//           equipmentDefermentsMapKeys[index]
//         ][idx].unScheduledDefermentBase = 0;
//       }
//       if (!isNumber(x.unScheduledDefermentLow)) {
//         defermentsProperties.equipmentDefermentsModel.equipmentDefermentsMap[
//           equipmentDefermentsMapKeys[index]
//         ][idx].unScheduledDefermentLow = 0;
//       }
//       if (!isNumber(x.unScheduledDefermentHigh)) {
//         defermentsProperties.equipmentDefermentsModel.equipmentDefermentsMap[
//           equipmentDefermentsMapKeys[index]
//         ][idx].unScheduledDefermentHigh = 0;
//       }
//     }
//   }
// }

export function TrimLineSalesPointInputDeckData(
  salesPointProperties: SalesPointProperties
) {
  for (
    let index = 0;
    index < salesPointProperties.salesPointModel.salesStrategy.schedule.length;
    index++
  ) {
    const x =
      salesPointProperties.salesPointModel.salesStrategy.schedule[index];

    if (x.equipmentName === null || x.equipmentName === undefined) {
      salesPointProperties.salesPointModel.salesStrategy.schedule[
        index
      ].equipmentName = '';
    }
    if (x.scheduleDate === null || x.scheduleDate === undefined) {
      salesPointProperties.salesPointModel.salesStrategy.schedule[
        index
      ].scheduleDate = '4/26/2024';
    }
    if (!isNumber(x.rateOrVolume)) {
      salesPointProperties.salesPointModel.salesStrategy.schedule[
        index
      ].rateOrVolume = 0;
    }
  }
}
