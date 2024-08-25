import mongoose from "mongoose";

// required properties to create a ForecastResultsByModule
interface ForecastResultsByModuleProperties {
  forecastResultsId: string;
  ModuleName: string;
  FacilityName: string;
  ScenarioName: string;
  ModuleKey: string;
  SolutionSpace: string;
  forecastResults: string;
  forecastInputId: string; 
} 

// properties that a ForecastResultsByModule document has
interface ForecastResultsByModuleDoc
  extends mongoose.Document,
    ForecastResultsByModuleProperties {
  isDeleted: boolean;
  createdAt: Date;
}

// properties that ForecastResultsByModule model has
interface ForecastResultsByModuleModel extends mongoose.Model<ForecastResultsByModuleDoc> {
  build(props: ForecastResultsByModuleProperties): ForecastResultsByModuleDoc;
}

const modelSchema = new mongoose.Schema({
  forecastResultsId: {
    type: String,
    required: true,
  },
  ModuleName: {
    type: String,
    required: true,
  },
  FacilityName: {
    type: String,
    required: true,
  },
  ScenarioName: {
    type: String,
    required: true,
  },
  ModuleKey: {
    type: String,
    required: true,
  },
  SolutionSpace: {
    type: String,
    required: true,
  },
  forecastResults: {
    type: String,
  },
  forecastInputId:{
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
});

modelSchema.methods.toJSON = function () {
  const model = this.toObject();
  model.id = model._id;

  delete model._id;
  delete model.__v;

  return model;
};

modelSchema.statics.build = (props: ForecastResultsByModuleProperties) => {
  return new ForecastResultsByModule(props);
};

const ForecastResultsByModule = mongoose.model<
  ForecastResultsByModuleDoc,
  ForecastResultsByModuleModel
>("Forecast_ForecastResultsByModule", modelSchema);

export { ForecastResultsByModule, ForecastResultsByModuleDoc, ForecastResultsByModuleProperties };

