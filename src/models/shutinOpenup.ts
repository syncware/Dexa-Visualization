import mongoose, { models } from "mongoose";
import { ISelectOption } from "./equipmentCapacities";

interface ShutinOpenupScheduleEntity {
    module: string;
    shutInDate: string;
    event: string;
    dcaStrategy: string;
    startupRate: number;
    startupRatePlateau: number;
    declineType: string;
    declineExponent: number;
    hyperbolicExponent: number;
}


interface ShutinOpenupModelEntity {
    forecastInputDeckOption: string;
    schedule: ShutinOpenupScheduleEntity[];
}

interface ShutinOpenupProperties {
  projectId: string;
  title: string;
  description: string;
  shutinOpenupModel: ShutinOpenupModelEntity;
}

interface ShutinOpenupDoc
  extends mongoose.Document,
  ShutinOpenupProperties {
  isDeleted: boolean;
  createdAt: Date;
}

interface RampUpDeckModel extends mongoose.Model<ShutinOpenupDoc> {
  build(props: ShutinOpenupProperties): ShutinOpenupDoc;
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
    shutinOpenupModel: {
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
            shutInDate: {
                type: String,
                default: false,
            },
            event: {
                type: String,
                default: false,
            },
            dcaStrategy: {
                type: String,
                default: false,
            },
            startupRate: {
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

modelSchema.statics.build = (props: ShutinOpenupProperties) => {
  return new ShutinOpenupDeck(props);
};

const ShutinOpenupDeck = mongoose.model<
ShutinOpenupDoc,
RampUpDeckModel
>("Forecast_ShutinOpenupDeck", modelSchema);

export {
    ShutinOpenupDeck,
    ShutinOpenupProperties,
    ShutinOpenupDoc,
    ShutinOpenupModelEntity,
    ShutinOpenupScheduleEntity,
};
