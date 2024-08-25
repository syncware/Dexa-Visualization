import mongoose from 'mongoose';
import { ISelectOption } from '../types';

interface ForecastInputModel {
  forecastInputDeckOption: ISelectOption;
  forecastInputOption: ISelectOption;
  shutinOpenupScheduleOption: ISelectOption;
  reroutingStrategyOption: ISelectOption;
  rampupScheduleOption: ISelectOption;
}

interface ForecastInputProperties {
  userId: string;
  projectId: string;
  title: string;
  description: string;
  forecastInputModel: ForecastInputModel;
}

interface ForecastInputDoc
  extends mongoose.Document,
    ForecastInputProperties {
  isDeleted: boolean;
  createdAt: Date;
}

interface ForecastInputModel
  extends mongoose.Model<ForecastInputDoc> {
  build(props: ForecastInputProperties): ForecastInputDoc;
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
  forecastInputModel: {
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

modelSchema.statics.build = (props: ForecastInputProperties) => {
  return new ForecastInput(props);
};

const ForecastInput = mongoose.model<
  ForecastInputDoc,
  ForecastInputModel
>('Forecast_ForecastInput', modelSchema);

export {
  ForecastInput,
  ForecastInputDoc,
  ForecastInputProperties,
  ISelectOption,
  ForecastInputModel,
};
