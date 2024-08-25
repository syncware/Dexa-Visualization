import mongoose from 'mongoose';
import { ISelectOption } from '../types';

interface TFlareGasRow {
  id?: string;
  sn?: number;
  flareGasDate: string;
  flareGasLow: number;
  flareGasBase: number;
  flareGasHigh: number;
}
export type TFlareGasDeck = TFlareGasRow[];
export type TFlareGasDateRow = {
  id?: string;
  sn?: number;
  flareGasStartDate: string;
  flareGasEndDate: string;
  flareGasRateLow: number;
  flareGasRateBase: number;
  flareGasRateHigh: number;
};
export type TFlareGasDateDeck = TFlareGasDateRow[];
export type TFlareGasInput = {
  inputTypeOption: ISelectOption;
  datesInput: TFlareGasDateDeck;
  inputDeck: TFlareGasDeck;
};
interface FlareGasModel {
  facilitiesInputDeckOption: ISelectOption;
  productionEquipmentOption: ISelectOption;
  productionEquipmentOptions: ISelectOption[];
  flareGasMap: Record<string, TFlareGasInput>;
}

interface FlareGasProperties {
  userId: string; 
  projectId: string;
  title: string;
  description: string;
  flareGasModel: FlareGasModel;
}

interface FlareGasModellingDoc
  extends mongoose.Document,
    FlareGasProperties {
  isDeleted: boolean;
  createdAt: Date;
}

interface FlareGasModellingModel
  extends mongoose.Model<FlareGasModellingDoc> {
  build(
    props: FlareGasProperties
  ): FlareGasModellingDoc;
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
  flareGasModel: {
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

modelSchema.statics.build = (props: FlareGasProperties) => {
  return new FlareGasModelling(props);
};

const FlareGasModelling = mongoose.model<
  FlareGasModellingDoc,
  FlareGasModellingModel
>('Forecast_FlareGasModelling', modelSchema);

export {
  FlareGasModel,
  FlareGasModelling,
  FlareGasModellingDoc,
  FlareGasProperties,
  ISelectOption,
  TFlareGasRow,
};
