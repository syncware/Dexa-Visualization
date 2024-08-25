import mongoose from 'mongoose';

interface RateVsCumulativeEntity {
  _id: string;
  sn: string;
  module: string;
  oilRate: number;
  cumOilProd: string;
}

interface WellDeclineParametersEntity {
  _id: string;
  forecastVersion: string;
  asset: string;
  field: string;
  reservoir: string;
  drainagePoint: string;
  string: string;
  module: string;
  hydrocarbonStream: string;
  hydrocarbonType: string;

  declineMethod: string;
  declineStrategy: string;
  rateVsCumulative: string;

  initOilGasRate1P1C: number;
  initOilGasRate2P2C: number;
  initOilGasRate3P3C: number;
  rateofChangeRate1P1C: number;
  rateofChangeRate2P2C: number;
  rateofChangeRate3P3C: number;
  declineExponent1P1C: number;
  declineExponent2P2C: number;
  declineExponent3P3C: number;

  rateOfChangeGORCGR1P1C: number;
  rateOfChangeGORCGR2P2C: number;
  rateOfChangeGORCGR3P3C: number;
  rateOfChangeBSWWGR1P1C: number;
  rateOfChangeBSWWGR2P2C: number;
  rateOfChangeBSWWGR3P3C: number;
}

interface WellDeclineParameterProperties {
  forecastInputDeckId: string;
  projectId: string;
  userId: string;
  title: string;
  description: string;
  forecastInputdeckTitle: string;
  rateVsCumulativeDeck: Array<RateVsCumulativeEntity>;
  declineParameters: Array<WellDeclineParametersEntity>;
}

// properties that a WellDeclineParameters document has
interface WellDeclineParametersDoc
  extends mongoose.Document,
    WellDeclineParameterProperties {
  isDeleted: boolean;
  createdAt: Date;
}

// properties that WellDeclineParameters model has
interface WellDeclineParametersModel
  extends mongoose.Model<WellDeclineParametersDoc> {
  build(props: WellDeclineParameterProperties): WellDeclineParametersDoc;
}

const modelSchema = new mongoose.Schema({
  forecastInputDeckId: {
    type: String,
    required: true,
  },
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
  },
  description: {
    type: String,
  },
  forecastInputdeckTitle: {
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
  rateVsCumulativeDeck: Object,
  declineParameters: Object,
});

modelSchema.methods.toJSON = function () {
  const model = this.toObject();
  model.id = model._id;

  delete model._id;
  delete model.__v;

  return model;
};

modelSchema.statics.build = (props: WellDeclineParameterProperties) => {
  return new WellDeclineParameters(props);
};

const WellDeclineParameters = mongoose.model<
  WellDeclineParametersDoc,
  WellDeclineParametersModel
>('Forecast_WellDeclineParameters', modelSchema);

export {
  WellDeclineParameterProperties,
  WellDeclineParameters,
  WellDeclineParametersDoc,
  RateVsCumulativeEntity,
  WellDeclineParametersEntity,
};
