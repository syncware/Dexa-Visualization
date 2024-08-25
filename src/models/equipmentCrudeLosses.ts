import mongoose from 'mongoose';
import { ISelectOption } from '../types';

interface TEquipmentCrudeLossesRow {
  sn?: number;
  equipmentCrudeLossesDate: string;
  equipmentCrudeLossesLow: number;
  equipmentCrudeLossesBase: number;
  equipmentCrudeLossesHigh: number;
}
export type TEquipmentCrudeLossesDeck = TEquipmentCrudeLossesRow[];
export type TEquipmentCrudeLossesDateRow = {
  id?: string;
  sn?: number;
  equipmentCrudeLossesStartDate: string;
  equipmentCrudeLossesEndDate: string;
  equipmentCrudeLossesLow: number;
  equipmentCrudeLossesBase: number;
  equipmentCrudeLossesHigh: number;
};
export type TEquipmentCrudeLossesDateDeck = TEquipmentCrudeLossesDateRow[];
export type TEquipmentCrudeLossesInput = {
  inputTypeOption: ISelectOption;
  datesInput: TEquipmentCrudeLossesDateDeck;
  inputDeck: TEquipmentCrudeLossesDeck;
};
interface EquipmentCrudeLossesModel {
  facilitiesInputDeckOption: ISelectOption;
  productionEquipmentOption: ISelectOption;
  productionEquipmentOptions: ISelectOption[];
  equipmentCrudeLossesMap: Record<string, TEquipmentCrudeLossesInput>;
}

interface EquipmentCrudeLossesProperties {
  userId: string;
  projectId: string;
  title: string;
  description: string;
  equipmentCrudeLossesModel: EquipmentCrudeLossesModel;
}

interface EquipmentCrudeLossesModellingDoc
  extends mongoose.Document,
    EquipmentCrudeLossesProperties {
  isDeleted: boolean;
  createdAt: Date;
}

interface EquipmentCrudeLossesModellingModel
  extends mongoose.Model<EquipmentCrudeLossesModellingDoc> {
  build(
    props: EquipmentCrudeLossesProperties
  ): EquipmentCrudeLossesModellingDoc;
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
  equipmentCrudeLossesModel: {
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

modelSchema.statics.build = (props: EquipmentCrudeLossesProperties) => {
  return new EquipmentCrudeLossesModelling(props);
};

const EquipmentCrudeLossesModelling = mongoose.model<
  EquipmentCrudeLossesModellingDoc,
  EquipmentCrudeLossesModellingModel
>('Forecast_EquipmentCrudeLossesModelling', modelSchema);

export {
  EquipmentCrudeLossesModel,
  EquipmentCrudeLossesModelling,
  EquipmentCrudeLossesModellingDoc,
  EquipmentCrudeLossesProperties,
  ISelectOption,
  TEquipmentCrudeLossesRow,
};
