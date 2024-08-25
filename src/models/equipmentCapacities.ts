import mongoose from 'mongoose';
import { ISelectOption } from '../types';

interface IEquipmentCapacitiesRow {
  id?: string;
  sn?: number;
  equipmentCapacityDate: string;
  liquidCapacityLow?: number;
  liquidCapacityBase?: number;
  liquidCapacityHigh?: number;
  gasCapacityLow?: number;
  gasCapacityBase?: number;
  gasCapacityHigh?: number;
}
export type TEquipmentCapacitiesDeck = IEquipmentCapacitiesRow[];
export type TEquipmentCapacitiesDateRow = {
  id: string;
  sn: number;
  equipmentCapacityStartDate: string;
  equipmentCapacityEndDate: string;
  liquidCapacityLow?: number;
  liquidCapacityBase?: number;
  liquidCapacityHigh?: number;
  gasCapacityLow?: number;
  gasCapacityBase?: number;
  gasCapacityHigh?: number;
};
export type TEquipmentCapacitiesDateDeck = TEquipmentCapacitiesDateRow[];
export type TEquipmentCapacitiesInput = {
  inputTypeOption: ISelectOption;
  datesInput: TEquipmentCapacitiesDateDeck;
  inputDeck: TEquipmentCapacitiesDeck;
};
interface EquipmentCapacitiesModel {
  facilitiesInputDeckOption: ISelectOption;
  productionEquipmentOption: ISelectOption;
  productionEquipmentOptions: ISelectOption[];
  equipmentCapacitiesMap: Record<string, TEquipmentCapacitiesInput>;
}

interface EquipmentCapacitiesProperties {
  userId: string;
  projectId: string;
  title: string;
  description: string;
  equipmentCapacitiesModel: EquipmentCapacitiesModel;
}

interface EquipmentCapacitiesModellingDoc
  extends mongoose.Document,
    EquipmentCapacitiesProperties {
  isDeleted: boolean;
  createdAt: Date;
}

interface EquipmentCapacitiesModellingModel
  extends mongoose.Model<EquipmentCapacitiesModellingDoc> {
  build(props: EquipmentCapacitiesProperties): EquipmentCapacitiesModellingDoc;
}

const modelSchema = new mongoose.Schema({
  projectId: {
    type: String,
    required: true,
  },
  title: {
    type: String,
    required: true,
  },
  description: {
    type: String,
  },
  isDeleted: {
    type: Boolean,
    default: false,
  },
  createdAt: {
    type: Date,
    default: Date.now(),
  },
  equipmentCapacitiesModel: {
    type: Object,
  },
});

modelSchema.methods.toJSON = function () {
  const model = this.toObject();
  model.id = model._id;

  delete model._id;
  delete model.__v;

  return model;
};

modelSchema.statics.build = (props: EquipmentCapacitiesProperties) => {
  return new EquipmentCapacitiesModelling(props);
};

const EquipmentCapacitiesModelling = mongoose.model<
  EquipmentCapacitiesModellingDoc,
  EquipmentCapacitiesModellingModel
>('Forecast_EquipmentCapacitiesModelling', modelSchema);

export {
    EquipmentCapacitiesModelling,
    EquipmentCapacitiesModellingDoc,
    EquipmentCapacitiesProperties,
    ISelectOption,
    IEquipmentCapacitiesRow,
    EquipmentCapacitiesModel
};

