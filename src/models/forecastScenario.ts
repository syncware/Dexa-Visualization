import mongoose, { models } from "mongoose";

// required properties to create a ForecastScenario
interface ForecastScenarioProperties {
  forecastResultsId: string;
  scenarioName: string;
  forecastResults: object;
}

// properties that a ForecastScenario document has
interface ForecastScenarioDoc
  extends mongoose.Document,
    ForecastScenarioProperties {
  isDeleted: boolean;
  createdAt: Date;
}

// properties that ForecastScenario model has
interface ForecastScenarioModel extends mongoose.Model<ForecastScenarioDoc> {
  build(props: ForecastScenarioProperties): ForecastScenarioDoc;
}

const modelSchema = new mongoose.Schema({
  forecastResultsId: {
    type: String,
    required: true,
  },
  scenarioName: {
    type: String,
    required: true,
  },
  forecastResults: {
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

modelSchema.statics.build = (props: ForecastScenarioProperties) => {
  return new ForecastScenario(props);
};

const ForecastScenario = mongoose.model<
  ForecastScenarioDoc,
  ForecastScenarioModel
>("Forecast_ForecastScenario", modelSchema);

export { ForecastScenario, ForecastScenarioProperties, ForecastScenarioDoc };
