import mongoose from 'mongoose';
import { ISelectOption } from '../types';

interface TOwnUseGasRow {
  id?: string;
  sn?: number;
  ownUseGasDate: string;
  ownUseGasLow: number;
  ownUseGasBase: number;
  ownUseGasHigh: number;
}
export type TOwnUseGasDeck = TOwnUseGasRow[];
export type TOwnUseGasDateRow = {
  id?: string;
  sn?: number;
  ownUseGasStartDate: string;
  ownUseGasEndDate: string;
  ownUseGasRateLow: number;
  ownUseGasRateBase: number;
  ownUseGasRateHigh: number;
};
export type TOwnUseGasDateDeck = TOwnUseGasDateRow[];
export type TOwnUseGasInput = {
  inputTypeOption: ISelectOption;
  datesInput: TOwnUseGasDateDeck;
  inputDeck: TOwnUseGasDeck;
};
interface OwnUseGasModel {
  facilitiesInputDeckOption: ISelectOption;
  productionEquipmentOption: ISelectOption;
  productionEquipmentOptions: ISelectOption[];
  ownUseGasMap: Record<string, TOwnUseGasInput>;
}

interface OwnUseGasProperties {
  userId: string;
  projectId: string;
  title: string;
  description: string;
  ownUseGasModel: OwnUseGasModel;
}

interface OwnUseGasModellingDoc
  extends mongoose.Document,
    OwnUseGasProperties {
  isDeleted: boolean;
  createdAt: Date;
}

interface OwnUseGasModellingModel
  extends mongoose.Model<OwnUseGasModellingDoc> {
  build(
    props: OwnUseGasProperties
  ): OwnUseGasModellingDoc;
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
  ownUseGasModel: {
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

modelSchema.statics.build = (props: OwnUseGasProperties) => {
  return new OwnUseGasModelling(props);
};

const OwnUseGasModelling = mongoose.model<
  OwnUseGasModellingDoc,
  OwnUseGasModellingModel
>('Forecast_OwnUseGasModelling', modelSchema);

export {
  ISelectOption, OwnUseGasModel,
  OwnUseGasModelling,
  OwnUseGasModellingDoc,
  OwnUseGasProperties, TOwnUseGasRow
};

