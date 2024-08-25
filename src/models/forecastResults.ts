import mongoose from "mongoose";

// required properties to create a Forecast
interface ForecastResultsProperties {
  id: string;
  userId: string; 
  projectId: string;
  facilitiesInputId: string;
  forecastInputId: string;
  forecastParametersId: string;
  facilitiesInputTitle: string;
  forecastInputTitle: string;
  forecastingParametersTitle: string;
  title: string;
  description: string;
  treeResult: object;
  runTimeStatistics: object
}

// properties that a Forecast document has
interface ForecastResultsDoc extends mongoose.Document, ForecastResultsProperties {
  id: string;
  isDeleted: boolean;
  createdAt: Date;
}

// properties that Forecast model has
interface ForecastModel extends mongoose.Model<ForecastResultsDoc> {
  build(props: ForecastResultsProperties): ForecastResultsDoc;
}

const modelSchema = new mongoose.Schema({
  userId: {
    type: String,
    required: true,
  },
  projectId: {
    type: String,
    required: true,
  },
  facilitiesInputId: {
    type: String,
    required: true,
  },
  facilitiesInputTitle: {
    type: String,
  },
  forecastInputId: {
    type: String,
    required: true,
  },
  forecastInputTitle: {
    type: String,
  },
  forecastParametersId: {
    type: String,
    required: true,
  },
  forecastingParametersTitle: {
    type: String,
  },
  title: {
    type: String,
    required: true,
  },
  description: {
    type: String,
  },
  treeResult: {
    type: Object,
  },
  runTimeStatistics: {
    type: Object,
  },
  isDeleted: {
    type: Boolean,
    default: false,
  },
  createdAt: {
    type: Date,
    default: Date.now(),
  },
});

modelSchema.methods.toJSON = function () {
  const model = this.toObject();
  model.id = model._id;

  delete model._id;
  delete model.__v;

  return model;
};

modelSchema.statics.build = (props: ForecastResultsProperties) => {
  return new ForecastResults(props);
};

const ForecastResults = mongoose.model<ForecastResultsDoc, ForecastModel>(
  "Forecast_ForecastResults",
  modelSchema
);

export { ForecastResults, ForecastResultsDoc, ForecastResultsProperties };

