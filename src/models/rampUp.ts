import mongoose, { models } from "mongoose";
import { ISelectOption } from "./equipmentCapacities";

interface RampUpScheduleEntity {
    module: string;
    maximumPotential: number;
    startDate: string;
    dcaStrategy: string;
    percentOfMaximumPotential: number;
    startupRatePlateau: number;
    declineType: string;
    declineExponent: number;
    hyperbolicExponent: number;
}

interface RampUpModelEntity {
    forecastInputDeckOption: ISelectOption;
    rampupTypeOption: ISelectOption;
    schedule: RampUpScheduleEntity[];
}

interface RampUpProperties {
  projectId: string;
  title: string;
  description: string;
  rampupModel: RampUpModelEntity;
}

interface RampUpDoc
  extends mongoose.Document,
  RampUpProperties {
  isDeleted: boolean;
  createdAt: Date;
}

interface RampUpDeckModel extends mongoose.Model<RampUpDoc> {
  build(props: RampUpProperties): RampUpDoc;
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
    rampupModel: {
        forecastInputDeckOption: {
            id: {
              type: String,
            },
            value: {
              type: String,
            },
            label: {
              type: String,
            },
        },
        rampupTypeOption: {
            id: {
              type: String,
            },
            value: {
              type: String,
            },
            label: {
              type: String,
            },
        },
        schedule: [{
            module: {
                type: String,
                default: false,
            },
            maximumPotential: {
                type: Number,
                default: false,
            },
            startDate: {
                type: String,
                default: false,
            },
            dcaStrategy: {
                type: String,
                default: false,
            },
            percentOfMaximumPotential: {
                type: Number,
                default: false,
            },
            startupRatePlateau: {
                type: Number,
                default: false,
            },
            declineType: {
                type: String,
                default: false,
            },
            declineExponent: {
                type: Number,
                default: false,
            },
            hyperbolicExponent: {
                type: Number,
                default: false,
            },
        }]
    },
});

modelSchema.methods.toJSON = function () {
  const model = this.toObject();
  model.id = model._id;

  delete model._id;
  delete model.__v;

  return model;
};

modelSchema.statics.build = (props: RampUpProperties) => {
  return new RampUpDeck(props);
};

const RampUpDeck = mongoose.model<
RampUpDoc,
RampUpDeckModel
>("Forecast_RampUpDeck", modelSchema);

export {
    RampUpDeck,
    RampUpProperties,
    RampUpDoc,
    RampUpModelEntity,
    RampUpScheduleEntity,
};
