import mongoose, { models } from "mongoose";
import { ISelectOption } from "./equipmentCapacities";

interface ReroutingScheduleEntity {
    module: string;
    rerouteDate: string;
    rerouteDestination: string;
    dcaStrategy: string;
    startupRate: number;
    startupRatePlateau: number;
    declineType: string;
    declineExponent: number;
    hyperbolicExponent: number;
}


interface ReroutingModelEntity {
    forecastInputDeckOption: ISelectOption;
    schedule: ReroutingScheduleEntity[];
}

interface ReroutingProperties {
  projectId: string;
  title: string;
  description: string;
  reroutingModel: ReroutingModelEntity;
}

interface ReroutingDoc
  extends mongoose.Document,
  ReroutingProperties {
  isDeleted: boolean;
  createdAt: Date;
}

interface ReroutingDeckModel extends mongoose.Model<ReroutingDoc> {
  build(props: ReroutingProperties): ReroutingDoc;
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
    reroutingModel: {
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
        schedule: [{
            module: {
                type: String,
                default: false,
            },
            rerouteDate: {
                type: String,
                default: false,
            },
            rerouteDestination: {
                type: String,
                default: false,
            },
            dcaStrategy: {
                type: String,
                default: false,
            },
            startupRate: {
                type: String,
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

modelSchema.statics.build = (props: ReroutingProperties) => {
  return new ReroutingDeck(props);
};

const ReroutingDeck = mongoose.model<
ReroutingDoc,
ReroutingDeckModel
>("Forecast_ReroutingDeck", modelSchema);

export {
    ReroutingDeck,
    ReroutingProperties,
    ReroutingDoc,
    ReroutingModelEntity,
    ReroutingScheduleEntity,
};
