import {
  EquipmentCapacitiesModelling,
  EquipmentCapacitiesProperties,
} from '../../models/equipmentCapacities';
import {
  EquipmentCrudeLossesModelling,
  EquipmentCrudeLossesProperties,
} from '../../models/equipmentCrudeLosses';
import {
  EquipmentDefermentsModelling,
  EquipmentDefermentsProperties,
} from '../../models/equipmentDeferments';
import { FlareGasModelling, FlareGasProperties } from '../../models/flareGas';
import {
  OwnUseGasModelling,
  OwnUseGasProperties,
} from '../../models/ownUseGas';

const getFacilitiesData = async ({
  equipmentCapacitiesId,
  equipmentDefermentsId,
  equipmentCrudeLossesId,
  flareGasId,
  ownUseGasId,
}: any) => {
  let facilitiesData = {} as Record<string, any>;
  /**
   * Equipment Capacities
   */
  if (equipmentCapacitiesId) {
    const equipmentCapacities = (await EquipmentCapacitiesModelling.findById(
      equipmentCapacitiesId
    )) as EquipmentCapacitiesProperties;
    facilitiesData['equipmentCapacitiesMap'] =
      equipmentCapacities?.equipmentCapacitiesModel?.equipmentCapacitiesMap ||
      {};
  }

  /**
   * Equipment deferments
   */
  if (equipmentDefermentsId) {
    const equipmentDeferments = (await EquipmentDefermentsModelling.findById(
      equipmentDefermentsId
    )) as EquipmentDefermentsProperties;
    facilitiesData['equipmentDefermentsMap'] =
      equipmentDeferments?.equipmentDefermentsModel?.equipmentDefermentsMap ||
      {};
  }

  /**
   * Crudelosses Schedule
   */
  if (equipmentCrudeLossesId) {
    const equipmentCrudeLosses = (await EquipmentCrudeLossesModelling.findById(
      equipmentCrudeLossesId
    )) as EquipmentCrudeLossesProperties;
    facilitiesData['equipmentCrudeLossesMap'] =
      equipmentCrudeLosses?.equipmentCrudeLossesModel
        ?.equipmentCrudeLossesMap || [];
  }

  /**
   * Flared Gas
   */
  if (flareGasId) {
    const equipmentFlareGas = (await FlareGasModelling.findById(
      flareGasId
    )) as FlareGasProperties;
    facilitiesData['equipmentFlareGasMap'] =
      equipmentFlareGas?.flareGasModel?.flareGasMap || {};
  }

  /**
   * Gas Own Use
   */
  if (ownUseGasId) {
    const equipmentOwnUseGas = (await OwnUseGasModelling.findById(
      ownUseGasId
    )) as OwnUseGasProperties;
    facilitiesData['equipmentOwnUseGasMap'] =
      equipmentOwnUseGas?.ownUseGasModel?.ownUseGasMap || {};
  }

  return facilitiesData;
};

export default getFacilitiesData;
