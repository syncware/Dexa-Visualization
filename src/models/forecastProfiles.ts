import mongoose, { models } from "mongoose";

interface ForecastProfileEntity {
  GOR: number;
  CGR: number;
  BSW: number;
  WGR: number;
  cumOilProd: number;
  cumGasProd: number;
  customDate: string;
  moduleName: string;
  oilRate: number;
  gasRate: number;
  hydrocarbonStream: string;
}

// required properties to create a forecastProfiles
interface ForecastProfilesProperties {
  projectId: string;
  userId: string;
  inputDeckData: ForecastProfileEntity[];
  title: string;
  description: string;
  source: string; // external/apex
  variableUnits: object;
  variableUnitTitles: object;
}

// properties that a forecastProfiles document has
interface ForecastProfilesDoc
  extends mongoose.Document,
    ForecastProfilesProperties {
  isDeleted: boolean;
  createdAt: Date;
}

// properties that forecastProfiles model has
interface ForecastProfilesModel extends mongoose.Model<ForecastProfilesDoc> {
  build(props: ForecastProfilesProperties): ForecastProfilesDoc;
}

const modelSchema = new mongoose.Schema({
  projectId: {
    type: String,
    required: true,
  },
  userId: {
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
  source: {
    type: String,
    default: "apex",
  },
  variableUnits: {
    type: Object,
  },
  variableUnitTitles: {
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
  inputDeckData: [
    {
      GOR: {
        type: Number,
        required: false,
      },
      CGR: {
        type: Number,
        required: false,
      },
      BSW: {
        type: Number,
        required: false,
      },
      WGR: {
        type: Number,
        required: false,
      },
      cumOilProd: {
        type: Number,
        required: false,
      },
      cumGasProd: {
        type: Number,
        required: false,
      },
      customDate: {
        type: String,
        required: true,
      },
      moduleName: {
        type: String,
        required: true,
      },
      oilRate: {
        type: Number,
        required: false,
      },
      gasRate: {
        type: Number,
        required: false,
      },
      hydrocarbonStream: {
        type: String,
        required: false,
      },
    },
  ],
});

modelSchema.methods.toJSON = function () {
  const model = this.toObject();
  model.id = model._id;

  delete model._id;
  delete model.__v;

  return model;
};

modelSchema.statics.build = (props: ForecastProfilesProperties) => {
  return new ForecastProfiles(props);
};

const ForecastProfiles = mongoose.model<
  ForecastProfilesDoc,
  ForecastProfilesModel
>("Forecast_ForecastProfiles", modelSchema);

export {
  ForecastProfiles,
  ForecastProfilesProperties,
  ForecastProfilesDoc,
  ForecastProfileEntity,
};
