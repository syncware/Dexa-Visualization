import mongoose, { models } from "mongoose";
import { ISelectOption } from "./equipmentCapacities";

interface SalesPointScheduleEntity {
    equipmentName: string;
    scheduleDate: string;
    rateOrVolume: number;
}

interface SalesStrategy {
    optionValue: string;
    equityPercentage: number;
    schedule: SalesPointScheduleEntity[];
}


interface SalesPointModelEntity {
    facilitiesNetworkOption: ISelectOption;
    facilitiesInputDeckOption: ISelectOption;
    productionEquipmentOption: ISelectOption;
    salesStrategy: SalesStrategy;
    
}

interface SalesPointProperties {
  projectId: string;
  title: string;
  description: string;
  salesPointModel: SalesPointModelEntity;
}

interface SalesPointDoc
  extends mongoose.Document,
  SalesPointProperties {
  isDeleted: boolean;
  createdAt: Date;
}

interface SalesPointDeckModel extends mongoose.Model<SalesPointDoc> {
  build(props: SalesPointProperties): SalesPointDoc;
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
    salesPointModel: {
        facilitiesNetworkOption: {
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
        facilitiesInputDeckOption: {
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
        productionEquipmentOption: {
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
        salesStrategy: {
            optionValue: {
                type: String,
            },
            equityPercentage: {
                type: String,
            },
            schedule: [{
                equipmentName: {
                    type: String,
                    default: false,
                },
                scheduleDate: {
                    type: String,
                    default: false,
                },
                rateOrVolume: {
                    type: Number,
                    default: false,
                },
            }]
        }
    },
});

modelSchema.methods.toJSON = function () {
  const model = this.toObject();
  model.id = model._id;

  delete model._id;
  delete model.__v;

  return model;
};

modelSchema.statics.build = (props: SalesPointProperties) => {
  return new SalesPointDeck(props);
};

const SalesPointDeck = mongoose.model<
SalesPointDoc,
SalesPointDeckModel
>("SalesPointDeck", modelSchema);

export {
    SalesPointDeck,
    SalesPointProperties,
    SalesPointDoc,
    SalesPointModelEntity,
    SalesPointScheduleEntity,
};
