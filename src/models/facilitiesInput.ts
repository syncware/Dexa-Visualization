import mongoose from 'mongoose';
import { ISelectOption } from '../types';

interface FacilitiesInputModel {
  equipmentCapacitiesOption: ISelectOption;
  equipmentCrudeLossesOption: ISelectOption;
  equipmentDefermentOption: ISelectOption;
  flareGasOption: ISelectOption;
  ownUseGasOption: ISelectOption;
  facilitiesInputDeckOption: ISelectOption;
  facilitiesInputOption: ISelectOption;
  nodesAndEdges: Record<string, any>;
  flaredGasInputOption: ISelectOption;
  gasOwnUseInputOption: ISelectOption;
}

interface FacilitiesInputProperties {
  userId: string;
  projectId: string;
  title: string;
  description: string;
  facilitiesInputModel: FacilitiesInputModel;
}

interface FacilitiesInputDoc
  extends mongoose.Document,
    FacilitiesInputProperties {
  isDeleted: boolean;
  createdAt: Date;
}

interface FacilitiesInputModel
  extends mongoose.Model<FacilitiesInputDoc> {
  build(props: FacilitiesInputProperties): FacilitiesInputDoc;
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
  facilitiesInputModel: {
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

modelSchema.statics.build = (props: FacilitiesInputProperties) => {
  return new FacilitiesInput(props);
};

const FacilitiesInput = mongoose.model<
  FacilitiesInputDoc,
  FacilitiesInputModel
>('Forecast_FacilitiesInput', modelSchema);

export {
  FacilitiesInput,
  FacilitiesInputDoc,
  FacilitiesInputProperties,
  ISelectOption,
  FacilitiesInputModel,
};
