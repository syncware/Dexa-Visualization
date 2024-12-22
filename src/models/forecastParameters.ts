import mongoose, { Schema } from "mongoose";
interface ForecastParametersEntity {
  stopDay: number;
  stopMonth: number;
  stopYear: number;
  startDay: number;
  startMonth: number;
  startYear: number;
  timeFrequency: string;
  targetFluid: string;
  realtimeResults: string;
  isDeferred: number;
}

// required properties to create a ForecastParameters
interface ForecastParametersProperties {
  projectId: string;
  forecastInputDeckId: string;
  forecastInputdeckTitle: string;
  userId: string;
  type: string; // default
  title: string;
  description: string;
  wellPrioritizationTitle: string;
  wellDeclineParameterTitle: string;
  declineParametersId: string;
  wellPrioritizationId: string;
  parametersEntity: ForecastParametersEntity;
  isForecastProfiles: string;
  forecastProfilesId: string;
}

// properties that a ForecastParameters document has
interface ForecastParametersDoc
  extends mongoose.Document,
    ForecastParametersProperties {
  isDeleted: boolean;
  createdAt: Date;
}

// properties that ForecastParameters model has
interface ForecastParametersModel
  extends mongoose.Model<ForecastParametersDoc> {
  build(props: ForecastParametersProperties): ForecastParametersDoc;
}

const modelSchema = new mongoose.Schema({
  projectId: {
    type: String,
    required: true,
  },
  forecastInputDeckId: {
    type: String,
    required: true,
  },
  forecastInputdeckTitle: {
    type: String,
  },
  userId: {
    type: String,
    required: true,
  },
  type: {
    type: String,
    default: "Default",
  },
  title: {
    type: String,
  },
  description: {
    type: String,
  },
  wellPrioritizationTitle: {
    type: String,
  },
  wellDeclineParameterTitle: {
    type: String,
  },
  wellPrioritizationId: {
    type: String,
  },
  declineParametersId: {
    type: String,
  },
  isForecastProfiles: {
    type: String,
  },
  forecastProfilesId: {
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
  parametersEntity: {
    stopDay: {
      type: Schema.Types.Mixed,
    },
    stopMonth: {
      type: Schema.Types.Mixed,
    },
    stopYear: {
      type: Schema.Types.Mixed,
    },
    startDay: {
      type: Schema.Types.Mixed,
    },
    startMonth: {
      type: Schema.Types.Mixed,
    },
    startYear: {
      type: Schema.Types.Mixed,
    },
    timeFrequency: {
      type: String,
    },
    targetFluid: {
      type: String,
    },
    isDeferred: {
      type: Schema.Types.Mixed,
    },
    realtimeResults: {
      type: String,
    },
  },
});

modelSchema.methods.toJSON = function () {
  const model = this.toObject();
  model.id = model._id;

  delete model._id;
  delete model.__v;

  return model;
};

modelSchema.statics.build = (props: ForecastParametersProperties) => {
  return new ForecastParameters(props);
};

const ForecastParameters = mongoose.model<
  ForecastParametersDoc,
  ForecastParametersModel
>("Forecast_ForecastParameters", modelSchema);

export {
  ForecastParameters,
  ForecastParametersProperties,
  ForecastParametersDoc,
  ForecastParametersEntity,
};
