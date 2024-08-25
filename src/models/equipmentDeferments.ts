import mongoose from 'mongoose';
import { ISelectOption } from '../types';

interface TEquipmentDefermentsRow {
  id?: string;
  sn?: number;
  equipmentDefermentDate: string;
  scheduledDefermentLow: number;
  unScheduledDefermentLow: number;
  thirdPartyDefermentLow: number;
  scheduledDefermentBase: number;
  unScheduledDefermentBase: number;
  thirdPartyDefermentBase: number;
  scheduledDefermentHigh: number;
  unScheduledDefermentHigh: number;
  thirdPartyDefermentHigh: number;
}
export type TEquipmentDefermentsDeck = TEquipmentDefermentsRow[];
export type TEquipmentDefermentsDateRow = {
  id?: string;
  sn?: number;
  equipmentDefermentStartDate: string;
  equipmentDefermentEndDate: string;
  scheduledDefermentLow: number;
  unScheduledDefermentLow: number;
  thirdPartyDefermentLow: number;
  scheduledDefermentBase: number;
  unScheduledDefermentBase: number;
  thirdPartyDefermentBase: number;
  scheduledDefermentHigh: number;
  unScheduledDefermentHigh: number;
  thirdPartyDefermentHigh: number;
};
export type TEquipmentDefermentsDateDeck = TEquipmentDefermentsDateRow[];
export type TEquipmentDefermentsInput = {
  inputTypeOption: ISelectOption;
  datesInput: TEquipmentDefermentsDateDeck;
  inputDeck: TEquipmentDefermentsDeck;
};

interface EquipmentDefermentsModel {
  facilitiesInputDeckOption: ISelectOption;
  productionEquipmentOption: ISelectOption;
  productionEquipmentOptions: ISelectOption[];
  equipmentDefermentsMap: Record<string, TEquipmentDefermentsInput>;
}

interface EquipmentDefermentsProperties {
  userId: string;
  projectId: string;
  title: string;
  description: string;
  equipmentDefermentsModel: EquipmentDefermentsModel;
}

interface EquipmentDefermentsModellingDoc
  extends mongoose.Document,
    EquipmentDefermentsProperties {
  isDeleted: boolean;
  createdAt: Date;
}

interface EquipmentDefermentsModellingModel
  extends mongoose.Model<EquipmentDefermentsModellingDoc> {
  build(props: EquipmentDefermentsProperties): EquipmentDefermentsModellingDoc;
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
  equipmentDefermentsModel: {
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

modelSchema.statics.build = (props: EquipmentDefermentsProperties) => {
  return new EquipmentDefermentsModelling(props);
};

const EquipmentDefermentsModelling = mongoose.model<
  EquipmentDefermentsModellingDoc,
  EquipmentDefermentsModellingModel
>('Forecast_EquipmentDefermentsModelling', modelSchema);

export {
    EquipmentDefermentsModel, EquipmentDefermentsModelling,
    EquipmentDefermentsModellingDoc,
    EquipmentDefermentsProperties,
    ISelectOption,
    TEquipmentDefermentsRow
};

