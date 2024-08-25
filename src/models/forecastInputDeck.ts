import mongoose, { Schema } from "mongoose";

// required properties to create a InputDeck
interface ForecastIInputDeckEntity {
  forecastVersion: string;
  asset: string;
  field: string;
  reservoir: string;
  drainagePoint: string;
  string: string;
  module: string;
  projectCode: string;
  projectName: string;
  facilities: string;
  hydrocarbonStream: string;
  hydrocarbonType: string;
  terminal: string;
  resourceClass: string;
  oilUR1P1C: number;
  oilUR2P2C: number;
  oilUR3P3C: number;
  Np: number;
  gasUR1P1C: number;
  gasUR2P2C: number;
  gasUR3P3C: number;
  Gp: number;
  initOilGasRate1P1C: number;
  initOilGasRate2P2C: number;
  initOilGasRate3P3C: number;
  abandOilGasRate1P1C: number;
  //abandOilGasRateLow: number;
  abandOilGasRate2P2C: number;
  abandOilGasRate3P3C: number;
  initBSWWGR: number;
  abandBSWWGR1P1C: number;
  abandBSWWGR2P2C: number;
  abandBSWWGR3P3C: number;
  initGORCGR: number;
  abandGORCGR1P1C: number;
  abandGORCGR2P2C: number;
  abandGORCGR3P3C: number;
  plateauPeriod: number;
  onStreamDate1P1C: string;
  onStreamDate2P2C: string;
  onStreamDate3P3C: string;
  remarks: string;
  developmentTranche: string;
  description: string;

  //Calculated Variables

  day1P1C: number;
  day2P2C: number;
  day3P3C: number;
  month1P1C: number;
  month2P2C: number;
  month3P3C: number;
  year1P1C: number;
  year2P2C: number;
  year3P3C: number;

  rateofChangeRate1P1C: number;
  rateofChangeRate2P2C: number;
  rateofChangeRate3P3C: number;
  declineExponent1P1C: number;
  declineExponent2P2C: number;
  declineExponent3P3C: number;
  declineMethod: string;

  rateOfChangeGORCGR1P1C: number;
  rateOfChangeGORCGR2P2C: number;
  rateOfChangeGORCGR3P3C: number;
  rateOfChangeBSWWGR1P1C: number;
  rateOfChangeBSWWGR2P2C: number;
  rateOfChangeBSWWGR3P3C: number;

  plateauUR1P1C: number;
  plateauUR2P2C: number;
  plateauUR3P3C: number;
}
interface ForecastInputDeckProperties {
  projectId: string;
  userId: string;
  inputDeckData: Array<ForecastIInputDeckEntity>;
  title: string;
  description: string;
  source: string; // external/apex
  variableUnits: object;
  variableUnitTitles: object;
}

// properties that a InputDeck document has
interface ForecastInputDeckDoc
  extends mongoose.Document,
    ForecastInputDeckProperties {
  isDeleted: boolean;
  createdAt: Date;
}

// properties that InputDeck model has
interface ForecastInputDeckModel extends mongoose.Model<ForecastInputDeckDoc> {
  build(props: ForecastInputDeckProperties): ForecastInputDeckDoc;
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
      forecastVersion: {
        type: String,
        required: false,
      },
      asset: {
        type: String,
        required: false,
      },
      reservoir: {
        type: String,
        required: false,
      },
      field: {
        type: String,
        required: false,
      },
      drainagePoint: {
        type: String,
        required: false,
      },
      string: {
        type: String,
        required: false,
      },
      module: {
        type: String,
        required: true,
      },
      projectCode: {
        type: String,
        required: false,
      },
      projectName: {
        type: String,
        required: false,
      },
      facilities: {
        type: String,
        required: false,
      },
      hydrocarbonStream: {
        type: String,
        required: false,
      },
      hydrocarbonType: {
        type: String,
      },
      terminal: {
        type: String,
      },
      resourceClass: {
        type: String,
        required: false,
      },
      oilUR1P1C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      oilUR2P2C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      oilUR3P3C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      Np: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      gasUR1P1C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      gasUR2P2C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      gasUR3P3C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      Gp: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      initOilGasRate1P1C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      initOilGasRate2P2C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      initOilGasRate3P3C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      abandOilGasRate1P1C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      abandOilGasRate2P2C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      abandOilGasRate3P3C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      initBSWWGR: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      abandBSWWGR1P1C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      abandBSWWGR2P2C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      abandBSWWGR3P3C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      initGORCGR: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      abandGORCGR1P1C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      abandGORCGR2P2C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      abandGORCGR3P3C: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      plateauPeriod: {
        type: Schema.Types.Mixed,
        default: 0,
      },
      onStreamDate1P1C: {
        type: String,
        required: false,
      },
      onStreamDate2P2C: {
        type: String,
        required: false,
      },
      onStreamDate3P3C: {
        type: String,
        required: false,
      },
      remarks: {
        type: String,
        required: false,
      },
      developmentTranche: {
        type: String,
        required: false,
      },
      description: {
        type: String,
        required: false,
      },

      //Calculated Variables

      day1P1C: {
        type: Schema.Types.Mixed,
      },
      day2P2C: {
        type: Schema.Types.Mixed,
      },
      day3P3C: {
        type: Schema.Types.Mixed,
      },
      month1P1C: {
        type: Schema.Types.Mixed,
      },
      month2P2C: {
        type: Schema.Types.Mixed,
      },
      month3P3C: {
        type: Schema.Types.Mixed,
      },
      year1P1C: {
        type: Schema.Types.Mixed,
      },
      year2P2C: {
        type: Schema.Types.Mixed,
      },
      year3P3C: {
        type: Schema.Types.Mixed,
      },
      rateofChangeRate1P1C: {
        type: Schema.Types.Mixed,
      },
      rateofChangeRate2P2C: {
        type: Schema.Types.Mixed,
      },
      rateofChangeRate3P3C: {
        type: Schema.Types.Mixed,
      },
      declineExponent1P1C: {
        type: Schema.Types.Mixed,
      },
      declineExponent2P2C: {
        type: Schema.Types.Mixed,
      },
      declineExponent3P3C: {
        type: Schema.Types.Mixed,
      },
      declineMethod: {
        type: String,
      },
      rateOfChangeGORCGR1P1C: {
        type: Schema.Types.Mixed,
      },
      rateOfChangeGORCGR2P2C: {
        type: Schema.Types.Mixed,
      },
      rateOfChangeGORCGR3P3C: {
        type: Schema.Types.Mixed,
      },
      rateOfChangeBSWWGR1P1C: {
        type: Schema.Types.Mixed,
      },
      rateOfChangeBSWWGR2P2C: {
        type: Schema.Types.Mixed,
      },
      rateOfChangeBSWWGR3P3C: {
        type: Schema.Types.Mixed,
      },
      plateauUR1P1C: {
        type: Schema.Types.Mixed,
      },
      plateauUR2P2C: {
        type: Schema.Types.Mixed,
      },
      plateauUR3P3C: {
        type: Schema.Types.Mixed,
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

modelSchema.statics.build = (props: ForecastInputDeckProperties) => {
  return new ForecastInputDeck(props);
};
const ForecastInputDeck = mongoose.model<
  ForecastInputDeckDoc,
  ForecastInputDeckModel
>("Forecast_ForecastInputDeck", modelSchema);

export {
  ForecastInputDeck,
  ForecastInputDeckProperties,
  ForecastInputDeckDoc,
  ForecastIInputDeckEntity,
};
