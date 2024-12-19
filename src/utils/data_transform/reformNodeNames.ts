import {
  EquipmentCapacitiesModel,
  IEquipmentCapacitiesRow,
  TEquipmentCapacitiesDateRow,
  TEquipmentCapacitiesInput,
} from '../../models/equipmentCapacities';

import {
  EquipmentCrudeLossesModel,
  TEquipmentCrudeLossesDateRow,
  TEquipmentCrudeLossesInput,
  TEquipmentCrudeLossesRow,
} from '../../models/equipmentCrudeLosses';

import {
  EquipmentDefermentsModel,
  TEquipmentDefermentsDateRow,
  TEquipmentDefermentsInput,
  TEquipmentDefermentsRow,
} from '../../models/equipmentDeferments';

import {
  FlareGasModel,
  TFlareGasDateRow,
  TFlareGasInput,
  TFlareGasRow,
} from '../../models/flareGas';

import {
  OwnUseGasModel,
  TOwnUseGasDateRow,
  TOwnUseGasInput,
  TOwnUseGasRow,
} from '../../models/ownUseGas';

import { ISelectOption } from '../../types';

const formatDate = (date: string) => {
  const dt = new Date(date);
  const ans = dt.getDate() + '/' + (dt.getMonth() + 1) + '/' + dt.getFullYear();
  return ans;
};

const getNodeInternalName = (
  productionEquipmentType: string,
  productionEquipment: string
) => {
  if (productionEquipmentType.includes('flowstation')) {
    return 'Flow Station';
  }

  if (productionEquipmentType.includes('dehydrationunit')) {
    return 'Gas Asset';
  }

  if (productionEquipmentType.includes('oilpipeline')) {
    return 'Oil Asset';
  }

  if (productionEquipmentType.includes('gaspipeline')) {
    return 'Gas Asset';
  }

  if (
    productionEquipmentType.includes('centralprocessingfacility') &&
    productionEquipment.includes('agg')
  ) {
    return 'AG Asset';
  }

  if (
    productionEquipmentType.includes('centralprocessingfacility') &&
    productionEquipment.includes('nag')
  ) {
    return 'NAG Asset';
  }

  if (productionEquipmentType.includes('centralprocessingfacility')) {
    return 'centralProcessingFacility';
  }

  if (productionEquipmentType.includes('gasprocessingfacility')) {
    return 'Gas Plant';
  }

  if (productionEquipmentType.includes('terminal')) {
    return 'Oil Asset';
  }

  if (productionEquipmentType.includes('gasdemand')) {
    return 'Gas Asset';
  }

  return null;
};

export const GetInternalExternalEquipmentNames = (
  productionEquipments: any[]
) => {
  let internalExternalFacilitiesNames = productionEquipments.map((row: any) => {
    const productionEquipmentType = (
      row.productionEquipmentType as string
    ).toLowerCase();
    const productionEquipment = (
      row.productionEquipment as string
    ).toLowerCase();
    const equipmentType = getNodeInternalName(
      productionEquipmentType,
      productionEquipment
    );
    return {
      originalExternalEquipmentName: row.productionEquipment,
      externalEquipmentName: row.productionEquipment,
      internalEquipmentName: equipmentType,
      equipmentType: equipmentType,
      productionEquipmentType: row.productionEquipmentType,
    };
  });

  let internalExternalFacilitiesNamesModified = [];
  for (const internalExternalFacilitiesName of internalExternalFacilitiesNames) {
    if (
      internalExternalFacilitiesName.equipmentType ==
      'centralProcessingFacility'
    ) {
      const productionEquipment = (
        internalExternalFacilitiesName.externalEquipmentName as string
      ).toLowerCase();
      if (
        !productionEquipment.includes('nag') &&
        !productionEquipment.includes('agg')
      ) {
        const centralProcessingFacilityLiquid = {
          ...internalExternalFacilitiesName,
          externalEquipmentName: `${internalExternalFacilitiesName.externalEquipmentName}_Liquid`,
          equipmentType: 'Oil Asset',
        };
        internalExternalFacilitiesNamesModified.push({
          ...centralProcessingFacilityLiquid,
        });
        const centralProcessingFacility_Gas = {
          ...internalExternalFacilitiesName,
          externalEquipmentName: `${internalExternalFacilitiesName.externalEquipmentName}_Gas`,
          equipmentType: 'Gas Asset',
        };
        internalExternalFacilitiesNamesModified.push({
          ...centralProcessingFacility_Gas,
        });
      }
    } else {
      internalExternalFacilitiesNamesModified.push({
        ...internalExternalFacilitiesName,
      });
    }
  }

  return internalExternalFacilitiesNamesModified.slice(1);
};

export const GetEquipmentsCapacitiesSheetData = (
  equipmentCapacitiesModel: EquipmentCapacitiesModel,
  internalExternalFacilitiesNamesModified: any[]
) => {
  const equipmentCapacitiesMap =
    equipmentCapacitiesModel.equipmentCapacitiesMap;
  const productionEquipmentOptions =
    equipmentCapacitiesModel.productionEquipmentOptions;
  let equipmentsCapacities = [] as any[];
  const equipmentNames = Object.keys(equipmentCapacitiesMap);
  let j = -1;
  for (const equipmentName of equipmentNames) {
    j++;
    const productionEquipmentOption = productionEquipmentOptions[
      j
    ] as ISelectOption;
    const equipmentCapacities = equipmentCapacitiesMap[
      equipmentName
    ] as TEquipmentCapacitiesInput;
    const inputTypeOption =
      equipmentCapacities.inputTypeOption as ISelectOption;
    const datesInput =
      equipmentCapacities.datesInput as TEquipmentCapacitiesDateRow[];
    const inputDeck =
      equipmentCapacities.inputDeck as IEquipmentCapacitiesRow[];
    let equipmentObject = internalExternalFacilitiesNamesModified.find(
      (e) => e.originalExternalEquipmentName == equipmentName
    );
    const productionEquipmentTypeLowerCase =
      equipmentObject.productionEquipmentType.toLowerCase();
    const equipmentType = equipmentObject.equipmentType.toLowerCase();
    switch (inputTypeOption.value) {
      case 'datesInput':
        for (let i = 1; i < datesInput.length; i++) {
          /* if (
            !datesInput[i].liquidCapacityBase ||
            (datesInput[i].liquidCapacityBase == 0 &&
              !datesInput[i].gasCapacityBase) ||
            datesInput[i].gasCapacityBase == 0
          ) {
            if (
              equipmentType == 'flow station' ||
              equipmentType == 'gas plant'
            ) {
              datesInput[i].liquidCapacityBase = 60;
              datesInput[i].gasCapacityBase = 600;
            }
          } */
          const equipmentCapacitiesRowStartDate = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(datesInput[i].equipmentCapacityStartDate),
            FDate2P: formatDate(datesInput[i].equipmentCapacityStartDate),
            FDate3P: formatDate(datesInput[i].equipmentCapacityStartDate),
            Liquid_Capacity1P: datesInput[i].liquidCapacityBase,
            Liquid_Capacity2P: datesInput[i].liquidCapacityBase,
            Liquid_Capacity3P: datesInput[i].liquidCapacityBase,
            Gas_Capacity1P: datesInput[i].gasCapacityBase,
            Gas_Capacity2P: datesInput[i].gasCapacityBase,
            Gas_Capacity3P: datesInput[i].gasCapacityBase,
            AG_Capacity1P: datesInput[i].gasCapacityBase,
            AG_Capacity2P: datesInput[i].gasCapacityBase,
            AG_Capacity3P: datesInput[i].gasCapacityBase,
            NAG_Capacity1P: datesInput[i].gasCapacityBase,
            NAG_Capacity2P: datesInput[i].gasCapacityBase,
            NAG_Capacity3P: datesInput[i].gasCapacityBase,
            ProductionShareLow: 100,
            ProductionShareBase: 100,
            ProductionShareHigh: 100,
          } as any;

          /* const equipmentCapacitiesRowEndDate = {
                        Primary_Facility: equipmentName,
                        FDate1P: formatDate(datesInput[i].equipmentCapacityEndDate),
                        FDate2P: formatDate(datesInput[i].equipmentCapacityEndDate),
                        FDate3P: formatDate(datesInput[i].equipmentCapacityEndDate),
                        Liquid_Capacity1P: datesInput[i].liquidCapacityBase,
                        Liquid_Capacity2P: datesInput[i].liquidCapacityBase,
                        Liquid_Capacity3P: datesInput[i].liquidCapacityBase,
                        Gas_Capacity1P: datesInput[i].gasCapacityBase,
                        Gas_Capacity2P: datesInput[i].gasCapacityBase,
                        Gas_Capacity3P: datesInput[i].gasCapacityBase,
                        AG_Capacity1P: datesInput[i].gasCapacityBase,
                        AG_Capacity2P: datesInput[i].gasCapacityBase,
                        AG_Capacity3P: datesInput[i].gasCapacityBase,
                        NAG_Capacity1P: datesInput[i].gasCapacityBase,
                        NAG_Capacity2P: datesInput[i].gasCapacityBase,
                        NAG_Capacity3P: datesInput[i].gasCapacityBase,
                        ProductionShareLow: 100,
                        ProductionShareBase: 100,
                        ProductionShareHigh: 100,
                    } as any; */

          if (equipmentType.includes('nag')) {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRowStartDate,
              Gas_Capacity1P: 0,
              Gas_Capacity2P: 0,
              Gas_Capacity3P: 0,
              AG_Capacity1P: 0,
              AG_Capacity2P: 0,
              AG_Capacity3P: 0,
              NAG_Capacity1P: datesInput[i].gasCapacityBase,
              NAG_Capacity2P: datesInput[i].gasCapacityBase,
              NAG_Capacity3P: datesInput[i].gasCapacityBase,
            });

            /* equipmentsCapacities.push({
                            ...equipmentCapacitiesRowEndDate,
                            Gas_Capacity1P: 0,
                            Gas_Capacity2P: 0,
                            Gas_Capacity3P: 0,
                            AG_Capacity1P: 0,
                            AG_Capacity2P: 0,
                            AG_Capacity3P: 0,
                            NAG_Capacity1P: datesInput[i].gasCapacityBase,
                            NAG_Capacity2P: datesInput[i].gasCapacityBase,
                            NAG_Capacity3P: datesInput[i].gasCapacityBase,
                        }) */
          } else if (
            equipmentType.includes('agg') ||
            equipmentType.includes('ag')
          ) {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRowStartDate,
              Gas_Capacity1P: 0,
              Gas_Capacity2P: 0,
              Gas_Capacity3P: 0,
              AG_Capacity1P: datesInput[i].gasCapacityBase,
              AG_Capacity2P: datesInput[i].gasCapacityBase,
              AG_Capacity3P: datesInput[i].gasCapacityBase,
              NAG_Capacity1P: 0,
              NAG_Capacity2P: 0,
              NAG_Capacity3P: 0,
            });

            /* equipmentsCapacities.push({
                            ...equipmentCapacitiesRowEndDate,
                            Gas_Capacity1P: 0,
                            Gas_Capacity2P: 0,
                            Gas_Capacity3P: 0,
                            AG_Capacity1P: datesInput[i].gasCapacityBase,
                            AG_Capacity2P: datesInput[i].gasCapacityBase,
                            AG_Capacity3P: datesInput[i].gasCapacityBase,
                            NAG_Capacity1P: 0,
                            NAG_Capacity2P: 0,
                            NAG_Capacity3P: 0,
                        }) */
          } else if (
            productionEquipmentTypeLowerCase.includes(
              'centralprocessingfacility'
            )
          ) {
            if (
              !equipmentType.includes('nag') &&
              !equipmentType.includes('agg') &&
              !equipmentType.includes('ag')
            ) {
              const centralProcessingFacilityLiquidStartDate = {
                ...equipmentCapacitiesRowStartDate,
                Primary_Facility: `${equipmentObject.originalExternalEquipmentName}_Liquid`,
                Liquid_Capacity1P: datesInput[i].liquidCapacityBase,
                Liquid_Capacity2P: datesInput[i].liquidCapacityBase,
                Liquid_Capacity3P: datesInput[i].liquidCapacityBase,
                Gas_Capacity1P: 0,
                Gas_Capacity2P: 0,
                Gas_Capacity3P: 0,
                AG_Capacity1P: 0,
                AG_Capacity2P: 0,
                AG_Capacity3P: 0,
                NAG_Capacity1P: 0,
                NAG_Capacity2P: 0,
                NAG_Capacity3P: 0,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacilityLiquidStartDate,
              });
              /* const centralProcessingFacilityLiquidEndDate = {
                                ...equipmentCapacitiesRowEndDate,
                                Primary_Facility: `${equipmentObject.originalExternalEquipmentName}_Liquid`,
                                Liquid_Capacity1P: datesInput[i].liquidCapacityBase,
                                Liquid_Capacity2P: datesInput[i].liquidCapacityBase,
                                Liquid_Capacity3P: datesInput[i].liquidCapacityBase,
                                Gas_Capacity1P: 0,
                                Gas_Capacity2P: 0,
                                Gas_Capacity3P: 0,
                                AG_Capacity1P: 0,
                                AG_Capacity2P: 0,
                                AG_Capacity3P: 0,
                                NAG_Capacity1P: 0,
                                NAG_Capacity2P: 0,
                                NAG_Capacity3P: 0,
                            };
                            equipmentsCapacities.push({...centralProcessingFacilityLiquidEndDate}); */
              const centralProcessingFacility_GasStartDate = {
                ...equipmentCapacitiesRowStartDate,
                Primary_Facility: `${equipmentName}_Gas`,
                Liquid_Capacity1P: 0,
                Liquid_Capacity2P: 0,
                Liquid_Capacity3P: 0,
                Gas_Capacity1P: datesInput[i].gasCapacityBase,
                Gas_Capacity2P: datesInput[i].gasCapacityBase,
                Gas_Capacity3P: datesInput[i].gasCapacityBase,
                AG_Capacity1P: 0,
                AG_Capacity2P: 0,
                AG_Capacity3P: 0,
                NAG_Capacity1P: 0,
                NAG_Capacity2P: 0,
                NAG_Capacity3P: 0,
              };

              equipmentsCapacities.push({
                ...centralProcessingFacility_GasStartDate,
              });
              /* const centralProcessingFacility_GasEndDate = {
                                ...equipmentCapacitiesRowEndDate,
                                Primary_Facility: `${equipmentName}_Gas`,
                                Liquid_Capacity1P: 0,
                                Liquid_Capacity2P: 0,
                                Liquid_Capacity3P: 0,
                                Gas_Capacity1P: datesInput[i].gasCapacityBase,
                                Gas_Capacity2P: datesInput[i].gasCapacityBase,
                                Gas_Capacity3P: datesInput[i].gasCapacityBase,
                                AG_Capacity1P: 0,
                                AG_Capacity2P: 0,
                                AG_Capacity3P: 0,
                                NAG_Capacity1P: 0,
                                NAG_Capacity2P: 0,
                                NAG_Capacity3P: 0,
                            };
                            equipmentsCapacities.push({...centralProcessingFacility_GasEndDate}); */
            }
          } else {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRowStartDate,
            });

            /* equipmentsCapacities.push({
                            ...equipmentCapacitiesRowEndDate
                        }) */
          }
        }

        break;
      case 'inputDeck':
        for (let i = 1; i < inputDeck.length; i++) {
          /*  if (
            equipmentType == 'Flow Station' ||
            (equipmentType == 'Gas Plant' &&
              !inputDeck[i].liquidCapacityBase &&
              !inputDeck[i].gasCapacityBase)
          ) {
            inputDeck[i].liquidCapacityBase = 10000;
            inputDeck[i].gasCapacityBase = 50000;
          } */
          const equipmentCapacitiesRow = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(inputDeck[i].equipmentCapacityDate),
            FDate2P: formatDate(inputDeck[i].equipmentCapacityDate),
            FDate3P: formatDate(inputDeck[i].equipmentCapacityDate),
            Liquid_Capacity1P: inputDeck[i].liquidCapacityBase,
            Liquid_Capacity2P: inputDeck[i].liquidCapacityBase,
            Liquid_Capacity3P: inputDeck[i].liquidCapacityBase,
            Gas_Capacity1P: inputDeck[i].gasCapacityBase,
            Gas_Capacity2P: inputDeck[i].gasCapacityBase,
            Gas_Capacity3P: inputDeck[i].gasCapacityBase,
            AG_Capacity1P: inputDeck[i].gasCapacityBase,
            AG_Capacity2P: inputDeck[i].gasCapacityBase,
            AG_Capacity3P: inputDeck[i].gasCapacityBase,
            NAG_Capacity1P: inputDeck[i].gasCapacityBase,
            NAG_Capacity2P: inputDeck[i].gasCapacityBase,
            NAG_Capacity3P: inputDeck[i].gasCapacityBase,
            ProductionShareLow: 100,
            ProductionShareBase: 100,
            ProductionShareHigh: 100,
          } as any;

          if (equipmentType.includes('nag')) {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRow,
              Gas_Capacity1P: 0,
              Gas_Capacity2P: 0,
              Gas_Capacity3P: 0,
              AG_Capacity1P: 0,
              AG_Capacity2P: 0,
              AG_Capacity3P: 0,
              NAG_Capacity1P: inputDeck[i].gasCapacityBase,
              NAG_Capacity2P: inputDeck[i].gasCapacityBase,
              NAG_Capacity3P: inputDeck[i].gasCapacityBase,
            });
          } else if (
            equipmentType.includes('agg') ||
            equipmentType.includes('ag')
          ) {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRow,
              Gas_Capacity1P: 0,
              Gas_Capacity2P: 0,
              Gas_Capacity3P: 0,
              AG_Capacity1P: inputDeck[i].gasCapacityBase,
              AG_Capacity2P: inputDeck[i].gasCapacityBase,
              AG_Capacity3P: inputDeck[i].gasCapacityBase,
              NAG_Capacity1P: 0,
              NAG_Capacity2P: 0,
              NAG_Capacity3P: 0,
            });
          } else if (
            productionEquipmentTypeLowerCase.includes(
              'centralprocessingfacility'
            )
          ) {
            if (
              !equipmentType.includes('nag') &&
              !equipmentType.includes('agg') &&
              !equipmentType.includes('ag')
            ) {
              const centralProcessingFacilityLiquid = {
                ...equipmentCapacitiesRow,
                Primary_Facility: `${equipmentObject.originalExternalEquipmentName}_Liquid`,
                Liquid_Capacity1P: inputDeck[i].liquidCapacityBase,
                Liquid_Capacity2P: inputDeck[i].liquidCapacityBase,
                Liquid_Capacity3P: inputDeck[i].liquidCapacityBase,
                Gas_Capacity1P: 0,
                Gas_Capacity2P: 0,
                Gas_Capacity3P: 0,
                AG_Capacity1P: 0,
                AG_Capacity2P: 0,
                AG_Capacity3P: 0,
                NAG_Capacity1P: 0,
                NAG_Capacity2P: 0,
                NAG_Capacity3P: 0,
              };
              equipmentsCapacities.push({ ...centralProcessingFacilityLiquid });
              const centralProcessingFacility_Gas = {
                ...equipmentCapacitiesRow,
                Primary_Facility: `${equipmentObject.originalExternalEquipmentName}_Gas`,
                Liquid_Capacity1P: 0,
                Liquid_Capacity2P: 0,
                Liquid_Capacity3P: 0,
                Gas_Capacity1P: inputDeck[i].gasCapacityBase,
                Gas_Capacity2P: inputDeck[i].gasCapacityBase,
                Gas_Capacity3P: inputDeck[i].gasCapacityBase,
                AG_Capacity1P: 0,
                AG_Capacity2P: 0,
                AG_Capacity3P: 0,
                NAG_Capacity1P: 0,
                NAG_Capacity2P: 0,
                NAG_Capacity3P: 0,
              };
              equipmentsCapacities.push({ ...centralProcessingFacility_Gas });
            }
          } else {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRow,
            });
          }
        }
        break;
    }
  }

  for (j = 0; j < equipmentsCapacities.length; j++) {
    /* if (equipmentsCapacities[j].Primary_Facility.includes('Liquid')) {
      if (
        (equipmentsCapacities[j].Primary_Facility.includes('Liquid') &&
          equipmentsCapacities[j].Liquid_Capacity2P == 0) ||
        equipmentsCapacities[j].Liquid_Capacity2P == undefined
      ) {
        equipmentsCapacities[j].Liquid_Capacity1P = 1000;
        equipmentsCapacities[j].Liquid_Capacity2P = 1000;
        equipmentsCapacities[j].Liquid_Capacity3P = 1000;
        equipmentsCapacities[j].Gas_Capacity1P = 0;
        equipmentsCapacities[j].Gas_Capacity2P = 0;
        equipmentsCapacities[j].Gas_Capacity3P = 0;
      }
    } */

    if (equipmentsCapacities[j].Liquid_Capacity2P == undefined) {
      equipmentsCapacities[j].Liquid_Capacity1P = 0;
      equipmentsCapacities[j].Liquid_Capacity2P = 0;
      equipmentsCapacities[j].Liquid_Capacity3P = 0;
    }

    /* if (equipmentsCapacities[j].Primary_Facility.includes('Gas')) {
      if (
        equipmentsCapacities[j].Gas_Capacity2P == 0 ||
        equipmentsCapacities[j].Gas_Capacity2P == undefined
      ) {
        equipmentsCapacities[j].Gas_Capacity1P = 1000;
        equipmentsCapacities[j].Gas_Capacity2P = 1000;
        equipmentsCapacities[j].Gas_Capacity3P = 1000;
        equipmentsCapacities[j].Liquid_Capacity1P = 0;
        equipmentsCapacities[j].Liquid_Capacity2P = 0;
        equipmentsCapacities[j].Liquid_Capacity3P = 0;
      }
    } */

    if (equipmentsCapacities[j].Gas_Capacity2P == undefined) {
      equipmentsCapacities[j].Gas_Capacity1P = 0;
      equipmentsCapacities[j].Gas_Capacity2P = 0;
      equipmentsCapacities[j].Gas_Capacity3P = 0;
    }

    if (equipmentsCapacities[j].AG_Capacity2P == undefined) {
      equipmentsCapacities[j].AG_Capacity1P = 0;
      equipmentsCapacities[j].AG_Capacity2P = 0;
      equipmentsCapacities[j].AG_Capacity3P = 0;
    }

    if (equipmentsCapacities[j].NAG_Capacity2P == undefined) {
      equipmentsCapacities[j].NAG_Capacity1P = 0;
      equipmentsCapacities[j].NAG_Capacity2P = 0;
      equipmentsCapacities[j].NAG_Capacity3P = 0;
    }
  }

  return equipmentsCapacities;
};

export const GetEquipmentsDefermentsSheetData = (
  equipmentDefermentsModel: EquipmentDefermentsModel
) => {
  const equipmentCapacitiesMap =
    equipmentDefermentsModel.equipmentDefermentsMap;
  const productionEquipmentOptions =
    equipmentDefermentsModel.productionEquipmentOptions;
  let equipmentsCapacities = [] as any[];
  const equipmentNames = Object.keys(equipmentCapacitiesMap);
  let j = -1;
  for (const equipmentName of equipmentNames) {
    j++;
    const productionEquipmentOption = productionEquipmentOptions[
      j
    ] as ISelectOption;
    const equipmentCapacities = equipmentCapacitiesMap[
      equipmentName
    ] as TEquipmentDefermentsInput;
    const inputTypeOption =
      equipmentCapacities.inputTypeOption as ISelectOption;
    const datesInput =
      equipmentCapacities.datesInput as TEquipmentDefermentsDateRow[];
    const inputDeck =
      equipmentCapacities.inputDeck as TEquipmentDefermentsRow[];

    switch (inputTypeOption.value) {
      case 'datesInput':
        for (let i = 1; i < datesInput.length; i++) {
          let productionEquipmentOptionLabel =
            productionEquipmentOption.label as string;
          const equipmentCapacitiesRowStartDate = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(datesInput[i].equipmentDefermentStartDate),
            FDate2P: formatDate(datesInput[i].equipmentDefermentStartDate),
            FDate3P: formatDate(datesInput[i].equipmentDefermentStartDate),
            Scheduled_Deferment1P: datesInput[i].scheduledDefermentBase,
            Scheduled_Deferment2P: datesInput[i].scheduledDefermentBase,
            Scheduled_Deferment3P: datesInput[i].scheduledDefermentBase,
            Unscheduled_Deferment1P: datesInput[i].unScheduledDefermentBase,
            Unscheduled_Deferment2P: datesInput[i].unScheduledDefermentBase,
            Unscheduled_Deferment3P: datesInput[i].unScheduledDefermentBase,
            Thirdparty_Deferment1P: datesInput[i].thirdPartyDefermentBase,
            Thirdparty_Deferment2P: datesInput[i].thirdPartyDefermentBase,
            Thirdparty_Deferment3P: datesInput[i].thirdPartyDefermentBase,
          } as any;

          const equipmentCapacitiesRowEndDate = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(datesInput[i].equipmentDefermentEndDate),
            FDate2P: formatDate(datesInput[i].equipmentDefermentEndDate),
            FDate3P: formatDate(datesInput[i].equipmentDefermentEndDate),
            Scheduled_Deferment1P: datesInput[i].scheduledDefermentBase,
            Scheduled_Deferment2P: datesInput[i].scheduledDefermentBase,
            Scheduled_Deferment3P: datesInput[i].scheduledDefermentBase,
            Unscheduled_Deferment1P: datesInput[i].unScheduledDefermentBase,
            Unscheduled_Deferment2P: datesInput[i].unScheduledDefermentBase,
            Unscheduled_Deferment3P: datesInput[i].unScheduledDefermentBase,
            Thirdparty_Deferment1P: datesInput[i].thirdPartyDefermentBase,
            Thirdparty_Deferment2P: datesInput[i].thirdPartyDefermentBase,
            Thirdparty_Deferment3P: datesInput[i].thirdPartyDefermentBase,
          } as any;

          const productionEquipmentOptionLabelLowerCase =
            productionEquipmentOptionLabel.toLowerCase();
          if (
            productionEquipmentOptionLabel.includes('centralprocessingfacility')
          ) {
            if (
              !productionEquipmentOptionLabelLowerCase.includes('nag') &&
              !productionEquipmentOptionLabelLowerCase.includes('agg') &&
              !productionEquipmentOptionLabelLowerCase.includes('ag')
            ) {
              const centralProcessingFacilityLiquidStartDate = {
                ...equipmentCapacitiesRowStartDate,
                Primary_Facility: `${equipmentName}_Liquid`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacilityLiquidStartDate,
              });
              const centralProcessingFacility_GasStartDate = {
                ...equipmentCapacitiesRowStartDate,
                Primary_Facility: `${equipmentName}_Gas`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacility_GasStartDate,
              });

              const centralProcessingFacilityLiquidEndDate = {
                ...equipmentCapacitiesRowEndDate,
                Primary_Facility: `${equipmentName}_Liquid`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacilityLiquidEndDate,
              });
              const centralProcessingFacility_GasEndDate = {
                ...equipmentCapacitiesRowEndDate,
                Primary_Facility: `${equipmentName}_Gas`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacility_GasEndDate,
              });
            }
          } else {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRowStartDate,
            });

            equipmentsCapacities.push({
              ...equipmentCapacitiesRowEndDate,
            });
          }
        }

        break;
      case 'inputDeck':
        for (let i = 1; i < inputDeck.length; i++) {
          let productionEquipmentOptionLabel =
            productionEquipmentOption.label as string;
          const equipmentCapacitiesRow = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(inputDeck[i].equipmentDefermentDate),
            FDate2P: formatDate(inputDeck[i].equipmentDefermentDate),
            FDate3P: formatDate(inputDeck[i].equipmentDefermentDate),
            Scheduled_Deferment1P: inputDeck[i].scheduledDefermentBase,
            Scheduled_Deferment2P: inputDeck[i].scheduledDefermentBase,
            Scheduled_Deferment3P: inputDeck[i].scheduledDefermentBase,
            Unscheduled_Deferment1P: inputDeck[i].unScheduledDefermentBase,
            Unscheduled_Deferment2P: inputDeck[i].unScheduledDefermentBase,
            Unscheduled_Deferment3P: inputDeck[i].unScheduledDefermentBase,
            Thirdparty_Deferment1P: inputDeck[i].thirdPartyDefermentBase,
            Thirdparty_Deferment2P: inputDeck[i].thirdPartyDefermentBase,
            Thirdparty_Deferment3P: inputDeck[i].thirdPartyDefermentBase,
          } as any;

          const productionEquipmentOptionLabelLowerCase =
            productionEquipmentOptionLabel.toLowerCase();
          if (
            productionEquipmentOptionLabel.includes('centralprocessingfacility')
          ) {
            if (
              !productionEquipmentOptionLabelLowerCase.includes('nag') &&
              !productionEquipmentOptionLabelLowerCase.includes('agg') &&
              !productionEquipmentOptionLabelLowerCase.includes('ag')
            ) {
              const centralProcessingFacilityLiquid = {
                ...equipmentCapacitiesRow,
                Primary_Facility: `${equipmentName}_Liquid`,
              };
              equipmentsCapacities.push({ ...centralProcessingFacilityLiquid });
              const centralProcessingFacility_Gas = {
                ...equipmentCapacitiesRow,
                Primary_Facility: `${equipmentName}_Gas`,
              };
              equipmentsCapacities.push({ ...centralProcessingFacilityLiquid });
            }
          } else {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRow,
            });
          }
        }
        break;
    }
  }

  return equipmentsCapacities;
};

export const GetEquipmentsCrudeLossesSheetData = (
  equipmentCrudeLossesModel: EquipmentCrudeLossesModel
) => {
  const equipmentCrudeLossesMap =
    equipmentCrudeLossesModel.equipmentCrudeLossesMap;
  const productionEquipmentOptions =
    equipmentCrudeLossesModel.productionEquipmentOptions;
  let equipmentsCapacities = [] as any[];
  const equipmentNames = Object.keys(equipmentCrudeLossesMap);
  let j = -1;
  for (const equipmentName of equipmentNames) {
    j++;
    const productionEquipmentOption = productionEquipmentOptions[
      j
    ] as ISelectOption;
    const equipmentCrudeLossesInput = equipmentCrudeLossesMap[
      equipmentName
    ] as TEquipmentCrudeLossesInput;
    const inputTypeOption =
      equipmentCrudeLossesInput.inputTypeOption as ISelectOption;
    const datesInput =
      equipmentCrudeLossesInput.datesInput as TEquipmentCrudeLossesDateRow[];
    const inputDeck =
      equipmentCrudeLossesInput.inputDeck as TEquipmentCrudeLossesRow[];

    switch (inputTypeOption.value) {
      case 'datesInput':
        for (let i = 1; i < datesInput.length; i++) {
          let productionEquipmentOptionLabel =
            productionEquipmentOption.label as string;
          const equipmentCapacitiesRowStartDate = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(datesInput[i].equipmentCrudeLossesStartDate),
            FDate2P: formatDate(datesInput[i].equipmentCrudeLossesStartDate),
            FDate3P: formatDate(datesInput[i].equipmentCrudeLossesStartDate),
            Crudeoil_Lossess1P: datesInput[i].equipmentCrudeLossesBase,
            Crudeoil_Lossess2P: datesInput[i].equipmentCrudeLossesBase,
            Crudeoil_Lossess3P: datesInput[i].equipmentCrudeLossesBase,
          } as any;

          const equipmentCapacitiesRowEndDate = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(datesInput[i].equipmentCrudeLossesEndDate),
            FDate2P: formatDate(datesInput[i].equipmentCrudeLossesEndDate),
            FDate3P: formatDate(datesInput[i].equipmentCrudeLossesEndDate),
            Crudeoil_Lossess1P: datesInput[i].equipmentCrudeLossesBase,
            Crudeoil_Lossess2P: datesInput[i].equipmentCrudeLossesBase,
            Crudeoil_Lossess3P: datesInput[i].equipmentCrudeLossesBase,
          } as any;

          const productionEquipmentOptionLabelLowerCase =
            productionEquipmentOptionLabel.toLowerCase();
          if (
            productionEquipmentOptionLabel.includes('centralprocessingfacility')
          ) {
            if (
              !productionEquipmentOptionLabelLowerCase.includes('nag') &&
              !productionEquipmentOptionLabelLowerCase.includes('agg') &&
              !productionEquipmentOptionLabelLowerCase.includes('ag')
            ) {
              const centralProcessingFacilityLiquidStartDate = {
                ...equipmentCapacitiesRowStartDate,
                Primary_Facility: `${equipmentName}_Liquid`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacilityLiquidStartDate,
              });
              const centralProcessingFacility_GasStartDate = {
                ...equipmentCapacitiesRowStartDate,
                Primary_Facility: `${equipmentName}_Gas`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacility_GasStartDate,
              });

              const centralProcessingFacilityLiquidEndDate = {
                ...equipmentCapacitiesRowEndDate,
                Primary_Facility: `${equipmentName}_Liquid`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacilityLiquidEndDate,
              });
              const centralProcessingFacility_GasEndDate = {
                ...equipmentCapacitiesRowEndDate,
                Primary_Facility: `${equipmentName}_Gas`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacility_GasEndDate,
              });
            }
          } else {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRowStartDate,
            });

            equipmentsCapacities.push({
              ...equipmentCapacitiesRowEndDate,
            });
          }
        }

        break;
      case 'inputDeck':
        for (let i = 1; i < inputDeck.length; i++) {
          let productionEquipmentOptionLabel =
            productionEquipmentOption.label as string;
          const equipmentCapacitiesRow = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(inputDeck[i].equipmentCrudeLossesDate),
            FDate2P: formatDate(inputDeck[i].equipmentCrudeLossesDate),
            FDate3P: formatDate(inputDeck[i].equipmentCrudeLossesDate),
            Crudeoil_Lossess1P: inputDeck[i].equipmentCrudeLossesBase,
            Crudeoil_Lossess2P: inputDeck[i].equipmentCrudeLossesBase,
            Crudeoil_Lossess3P: inputDeck[i].equipmentCrudeLossesBase,
          } as any;

          const productionEquipmentOptionLabelLowerCase =
            productionEquipmentOptionLabel.toLowerCase();
          if (
            productionEquipmentOptionLabel.includes('centralprocessingfacility')
          ) {
            if (
              !productionEquipmentOptionLabelLowerCase.includes('nag') &&
              !productionEquipmentOptionLabelLowerCase.includes('agg') &&
              !productionEquipmentOptionLabelLowerCase.includes('ag')
            ) {
              const centralProcessingFacilityLiquid = {
                ...equipmentCapacitiesRow,
                Primary_Facility: `${equipmentName}_Liquid`,
              };
              equipmentsCapacities.push({ ...centralProcessingFacilityLiquid });
              const centralProcessingFacility_Gas = {
                ...equipmentCapacitiesRow,
                Primary_Facility: `${equipmentName}_Gas`,
              };
              equipmentsCapacities.push({ ...centralProcessingFacilityLiquid });
            }
          } else {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRow,
            });
          }
        }
        break;
    }
  }

  return equipmentsCapacities;
};

export const GetEquipmentsFlaredGasSheetData = (
  flareGasModel: FlareGasModel
) => {
  const flareGasMap = flareGasModel.flareGasMap;
  const productionEquipmentOptions = flareGasModel.productionEquipmentOptions;
  let equipmentsCapacities = [] as any[];
  const equipmentNames = Object.keys(flareGasMap);
  let j = -1;
  for (const equipmentName of equipmentNames) {
    j++;
    const productionEquipmentOption = productionEquipmentOptions[
      j
    ] as ISelectOption;
    const flareGasInput = flareGasMap[equipmentName] as TFlareGasInput;
    const inputTypeOption = flareGasInput.inputTypeOption as ISelectOption;
    const datesInput = flareGasInput.datesInput as TFlareGasDateRow[];
    const inputDeck = flareGasInput.inputDeck as TFlareGasRow[];

    switch (inputTypeOption.value) {
      case 'datesInput':
        for (let i = 1; i < datesInput.length; i++) {
          let productionEquipmentOptionLabel =
            productionEquipmentOption.label as string;
          const equipmentCapacitiesRowStartDate = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(datesInput[i].flareGasStartDate),
            FDate2P: formatDate(datesInput[i].flareGasStartDate),
            FDate3P: formatDate(datesInput[i].flareGasStartDate),
            GasFlared1P: datesInput[i].flareGasRateBase,
            GasFlared2P: datesInput[i].flareGasRateBase,
            GasFlared3P: datesInput[i].flareGasRateBase,
          } as any;

          const equipmentCapacitiesRowEndDate = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(datesInput[i].flareGasEndDate),
            FDate2P: formatDate(datesInput[i].flareGasEndDate),
            FDate3P: formatDate(datesInput[i].flareGasEndDate),
            GasFlared1P: datesInput[i].flareGasRateBase,
            GasFlared2P: datesInput[i].flareGasRateBase,
            GasFlared3P: datesInput[i].flareGasRateBase,
          } as any;

          const productionEquipmentOptionLabelLowerCase =
            productionEquipmentOptionLabel.toLowerCase();
          if (
            productionEquipmentOptionLabel.includes('centralprocessingfacility')
          ) {
            if (
              !productionEquipmentOptionLabelLowerCase.includes('nag') &&
              !productionEquipmentOptionLabelLowerCase.includes('agg') &&
              !productionEquipmentOptionLabelLowerCase.includes('ag')
            ) {
              const centralProcessingFacilityLiquidStartDate = {
                ...equipmentCapacitiesRowStartDate,
                Primary_Facility: `${equipmentName}_Liquid`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacilityLiquidStartDate,
              });
              const centralProcessingFacility_GasStartDate = {
                ...equipmentCapacitiesRowStartDate,
                Primary_Facility: `${equipmentName}_Gas`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacility_GasStartDate,
              });

              const centralProcessingFacilityLiquidEndDate = {
                ...equipmentCapacitiesRowEndDate,
                Primary_Facility: `${equipmentName}_Liquid`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacilityLiquidEndDate,
              });
              const centralProcessingFacility_GasEndDate = {
                ...equipmentCapacitiesRowEndDate,
                Primary_Facility: `${equipmentName}_Gas`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacility_GasEndDate,
              });
            }
          } else {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRowStartDate,
            });

            equipmentsCapacities.push({
              ...equipmentCapacitiesRowEndDate,
            });
          }
        }

        break;
      case 'inputDeck':
        for (let i = 1; i < inputDeck.length; i++) {
          let productionEquipmentOptionLabel =
            productionEquipmentOption.label as string;
          const equipmentCapacitiesRow = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(inputDeck[i].flareGasDate),
            FDate2P: formatDate(inputDeck[i].flareGasDate),
            FDate3P: formatDate(inputDeck[i].flareGasDate),
            GasFlared1P: inputDeck[i].flareGasBase,
            GasFlared2P: inputDeck[i].flareGasBase,
            GasFlared3P: inputDeck[i].flareGasBase,
          } as any;

          const productionEquipmentOptionLabelLowerCase =
            productionEquipmentOptionLabel.toLowerCase();
          if (
            productionEquipmentOptionLabel.includes('centralprocessingfacility')
          ) {
            if (
              !productionEquipmentOptionLabelLowerCase.includes('nag') &&
              !productionEquipmentOptionLabelLowerCase.includes('agg') &&
              !productionEquipmentOptionLabelLowerCase.includes('ag')
            ) {
              const centralProcessingFacilityLiquid = {
                ...equipmentCapacitiesRow,
                Primary_Facility: `${equipmentName}_Liquid`,
              };
              equipmentsCapacities.push({ ...centralProcessingFacilityLiquid });
              const centralProcessingFacility_Gas = {
                ...equipmentCapacitiesRow,
                Primary_Facility: `${equipmentName}_Gas`,
              };
              equipmentsCapacities.push({ ...centralProcessingFacilityLiquid });
            }
          } else {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRow,
            });
          }
        }
        break;
    }
  }

  return equipmentsCapacities;
};

export const GetEquipmentsGasOwnUseSheetData = (
  ownUseGasModel: OwnUseGasModel
) => {
  const flareGasMap = ownUseGasModel.ownUseGasMap;
  const productionEquipmentOptions = ownUseGasModel.productionEquipmentOptions;
  let equipmentsCapacities = [] as any[];
  const equipmentNames = Object.keys(flareGasMap);
  let j = -1;
  for (const equipmentName of equipmentNames) {
    j++;
    const productionEquipmentOption = productionEquipmentOptions[
      j
    ] as ISelectOption;
    const ownUseGasInput = flareGasMap[equipmentName] as TOwnUseGasInput;
    const inputTypeOption = ownUseGasInput.inputTypeOption as ISelectOption;
    const datesInput = ownUseGasInput.datesInput as TOwnUseGasDateRow[];
    const inputDeck = ownUseGasInput.inputDeck as TOwnUseGasRow[];

    switch (inputTypeOption.value) {
      case 'datesInput':
        for (let i = 1; i < datesInput.length; i++) {
          let productionEquipmentOptionLabel =
            productionEquipmentOption.label as string;
          const equipmentCapacitiesRowStartDate = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(datesInput[i].ownUseGasStartDate),
            FDate2P: formatDate(datesInput[i].ownUseGasStartDate),
            FDate3P: formatDate(datesInput[i].ownUseGasStartDate),
            GasOwnUse1P: datesInput[i].ownUseGasRateBase,
            GasOwnUse2P: datesInput[i].ownUseGasRateBase,
            GasOwnUse3P: datesInput[i].ownUseGasRateBase,
          } as any;

          const equipmentCapacitiesRowEndDate = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(datesInput[i].ownUseGasEndDate),
            FDate2P: formatDate(datesInput[i].ownUseGasEndDate),
            FDate3P: formatDate(datesInput[i].ownUseGasEndDate),
            GasOwnUse1P: datesInput[i].ownUseGasRateBase,
            GasOwnUse2P: datesInput[i].ownUseGasRateBase,
            GasOwnUse3P: datesInput[i].ownUseGasRateBase,
          } as any;

          const productionEquipmentOptionLabelLowerCase =
            productionEquipmentOptionLabel.toLowerCase();
          if (
            productionEquipmentOptionLabel.includes('centralprocessingfacility')
          ) {
            if (
              !productionEquipmentOptionLabelLowerCase.includes('nag') &&
              !productionEquipmentOptionLabelLowerCase.includes('agg') &&
              !productionEquipmentOptionLabelLowerCase.includes('ag')
            ) {
              const centralProcessingFacilityLiquidStartDate = {
                ...equipmentCapacitiesRowStartDate,
                Primary_Facility: `${equipmentName}_Liquid`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacilityLiquidStartDate,
              });
              const centralProcessingFacility_GasStartDate = {
                ...equipmentCapacitiesRowStartDate,
                Primary_Facility: `${equipmentName}_Gas`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacility_GasStartDate,
              });

              const centralProcessingFacilityLiquidEndDate = {
                ...equipmentCapacitiesRowEndDate,
                Primary_Facility: `${equipmentName}_Liquid`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacilityLiquidEndDate,
              });
              const centralProcessingFacility_GasEndDate = {
                ...equipmentCapacitiesRowEndDate,
                Primary_Facility: `${equipmentName}_Gas`,
              };
              equipmentsCapacities.push({
                ...centralProcessingFacility_GasEndDate,
              });
            }
          } else {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRowStartDate,
            });

            equipmentsCapacities.push({
              ...equipmentCapacitiesRowEndDate,
            });
          }
        }

        break;
      case 'inputDeck':
        for (let i = 1; i < inputDeck.length; i++) {
          let productionEquipmentOptionLabel =
            productionEquipmentOption.label as string;
          const equipmentCapacitiesRow = {
            Primary_Facility: equipmentName,
            FDate1P: formatDate(inputDeck[i].ownUseGasDate),
            FDate2P: formatDate(inputDeck[i].ownUseGasDate),
            FDate3P: formatDate(inputDeck[i].ownUseGasDate),
            GasOwnUse1P: inputDeck[i].ownUseGasBase,
            GasOwnUse2P: inputDeck[i].ownUseGasBase,
            GasOwnUse3P: inputDeck[i].ownUseGasBase,
          } as any;

          const productionEquipmentOptionLabelLowerCase =
            productionEquipmentOptionLabel.toLowerCase();
          if (
            productionEquipmentOptionLabel.includes('centralprocessingfacility')
          ) {
            if (
              !productionEquipmentOptionLabelLowerCase.includes('nag') &&
              !productionEquipmentOptionLabelLowerCase.includes('agg') &&
              !productionEquipmentOptionLabelLowerCase.includes('ag')
            ) {
              const centralProcessingFacilityLiquid = {
                ...equipmentCapacitiesRow,
                Primary_Facility: `${equipmentName}_Liquid`,
              };
              equipmentsCapacities.push({ ...centralProcessingFacilityLiquid });
              const centralProcessingFacility_Gas = {
                ...equipmentCapacitiesRow,
                Primary_Facility: `${equipmentName}_Gas`,
              };
              equipmentsCapacities.push({ ...centralProcessingFacilityLiquid });
            }
          } else {
            equipmentsCapacities.push({
              ...equipmentCapacitiesRow,
            });
          }
        }
        break;
    }
  }

  return equipmentsCapacities;
};

export const GetEquipmentConnections = (
  equipmentConnectionList: any[],
  internalExternalFacilitiesNamesModified: any[]
) => {
  let equipmentConnections2 = equipmentConnectionList.slice(2);
  let equipmentConnectionListModified = equipmentConnections2.map(
    (row: any) => {
      let i = 0,
        j = 0;
      let newRow = {} as any;
      const keys = Object.keys(row);
      let lastNode = row[keys[0]];
      for (i = 0; i < keys.length; i++) {
        if (row[keys[i]]) {
          lastNode = row[keys[i]];
        }
      }
      for (i = 1; i < keys.length; i++) {
        newRow[keys[i]] = row[keys[i]];
        if ((i > 1 && row[keys[i]] == '') || row[keys[i]] == undefined) {
          for (j = i; j < keys.length; j++) {
            let tempNode = newRow[keys[j - 2]];
            newRow[keys[j - 1]] = tempNode;
            newRow[keys[j]] = tempNode;
          }
          break;
        }
      }
      newRow[keys[keys.length - 1]] = lastNode;
      return {
        ...newRow,
      };
    }
  ) as any[];

  let equipmentConnectionListUpdated = [] as any[];
  let uniqueConnections = [] as string[];
  for (const equipmentConnectionModified of equipmentConnectionListModified) {
    const row = { ...equipmentConnectionModified };
    const rowKeys = Object.keys(row);
    let i = 0;
    //Creat econnection=====================
    let uniqueConnection = '';
    for (i = 0; i < rowKeys.length; i++) {
      uniqueConnection = uniqueConnection + row[rowKeys[i]] + '===';
    }
    //================================
    for (i = 1; i < rowKeys.length; i++) {
      if (i < rowKeys.length - 1) {
        let equipmentObject = internalExternalFacilitiesNamesModified.find(
          (e) => e.originalExternalEquipmentName == row[rowKeys[i]]
        );
        let nextEquipmentObject = internalExternalFacilitiesNamesModified.find(
          (e) => e.originalExternalEquipmentName == row[rowKeys[i + 1]]
        );
        const productionEquipmentOptionLabelLowerCase =
          equipmentObject.equipmentType.toLowerCase();
        if (
          equipmentObject.productionEquipmentType.includes(
            'centralProcessingFacility'
          )
        ) {
          if (
            !productionEquipmentOptionLabelLowerCase.includes('nag') &&
            !productionEquipmentOptionLabelLowerCase.includes('agg') &&
            !productionEquipmentOptionLabelLowerCase.includes('ag')
          ) {
            if (nextEquipmentObject.equipmentType == 'Oil Asset') {
              row[rowKeys[i]] = `${row[rowKeys[i]]}_Liquid`;
            } else {
              row[rowKeys[i]] = `${row[rowKeys[i]]}_Gas`;
            }
            if (!uniqueConnections.includes(uniqueConnection)) {
              uniqueConnections.push(uniqueConnection);
              equipmentConnectionListUpdated.push({ ...row });
            }
          }
        } else {
          if (!uniqueConnections.includes(uniqueConnection)) {
            uniqueConnections.push(uniqueConnection);
            equipmentConnectionListUpdated.push({ ...row });
          }
        }
      } else {
        let equipmentObject = internalExternalFacilitiesNamesModified.find(
          (e) => e.originalExternalEquipmentName == row[rowKeys[i]]
        );
        let previousEquipmentObject =
          internalExternalFacilitiesNamesModified.find(
            (e) => e.originalExternalEquipmentName == row[rowKeys[i - 1]]
          );
        const productionEquipmentOptionLabelLowerCase =
          equipmentObject.equipmentType.toLowerCase();
        if (
          equipmentObject.productionEquipmentType.includes(
            'centralProcessingFacility'
          )
        ) {
          if (
            !productionEquipmentOptionLabelLowerCase.includes('nag') &&
            !productionEquipmentOptionLabelLowerCase.includes('agg') &&
            !productionEquipmentOptionLabelLowerCase.includes('ag')
          ) {
            if (
              previousEquipmentObject.equipmentType.includes('Oil') ||
              previousEquipmentObject.equipmentType.includes('Flow Station')
            ) {
              row[rowKeys[i]] = `${row[rowKeys[i]]}_Liquid`;
            } else {
              row[rowKeys[i]] = `${row[rowKeys[i]]}_Gas`;
            }
            if (!uniqueConnections.includes(uniqueConnection)) {
              uniqueConnections.push(uniqueConnection);
              equipmentConnectionListUpdated.push({ ...row });
            }
          }
        } else {
          if (!uniqueConnections.includes(uniqueConnection)) {
            uniqueConnections.push(uniqueConnection);
            equipmentConnectionListUpdated.push({ ...row });
          }
        }
      }
    }
  }
  let numberOfNodes = 0;
  if (equipmentConnectionListUpdated.length > 0) {
    numberOfNodes = Object.keys(equipmentConnectionListUpdated[0]).length;
  }

  return { numberOfNodes, equipmentConnectionListUpdated };
};
