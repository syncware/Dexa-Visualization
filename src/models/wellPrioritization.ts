import mongoose, { Schema } from 'mongoose';
import { ISelectOption } from './equipmentCapacities';

interface WellPrioritizationEntitty {
  module: string;
  optimizationWeight: string;
}

interface PrioritizationLevelOption {
  value: number;
  title: string;
  unit: string;
}

interface StreamPrioritization {
  streamTypeOption: ISelectOption;
  prioritizationOrchestrationVariableOption: ISelectOption;
  prioritizationOrchestrationMethodOption: ISelectOption;
}
interface WellPrioritization {
  prioritizationLevelOptions: PrioritizationLevelOption[];
  prioritizationTable: WellPrioritizationEntitty[];
}

interface ProjectPrioritizationRow {
  sn: string | number;
  project: string;
  rank: string | number;
}

interface NodalPrioritizationRow {
  sn: string;
  productionEquipment: string;
  priorityFluid: string;
  projectOptions: ISelectOption[];
  rankOptions: ISelectOption[];
}

interface ResourceClassPrioritization {
  resourceClass: string;
  rank: string;
}

interface ProductionPrioritizationModel {
  forecastInputDeckOption: ISelectOption;
  typeOfPrioritization: string;
  streamPrioritization: StreamPrioritization;
  wellPrioritization: WellPrioritization;
  projectPrioritization: ProjectPrioritizationRow[];
  nodalPrioritization: NodalPrioritizationRow[];
  resourceClassPrioritization: ResourceClassPrioritization[];
}

interface WellPrioritizationProperties {
  projectId: string;
  title: string;
  description: string;
  productionPrioritizationModel: ProductionPrioritizationModel;
}

// properties that a WellPrioritization document has
interface WellPrioritizationDoc
  extends mongoose.Document,
    WellPrioritizationProperties {
  isDeleted: boolean;
  createdAt: Date;
}

// properties that WellPrioritization model has
interface WellPrioritizationModel
  extends mongoose.Model<WellPrioritizationDoc> {
  build(props: WellPrioritizationProperties): WellPrioritizationDoc;
}

const modelSchema = new mongoose.Schema({
  projectId: {
    type: String,
    required: true,
  },
  title: {
    type: String,
  },
  description: {
    type: String,
  },
  productionPrioritizationModel: {
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
    typeOfPrioritization: {
      type: String,
    },
    streamPrioritization: {
      type: Object,
    },
    wellPrioritization: {
      prioritizationLevelOptions: [
        {
          value: {
            type: Schema.Types.Mixed,
          },
          title: {
            type: String,
          },
          unit: {
            type: String,
          },
        },
      ],
      prioritizationTable: [
        {
          module: {
            type: String,
          },
          optimizationWeight: {
            type: String,
          },
        },
      ],
    },
    projectPrioritization: {
      type: Object,
    },
    nodalPrioritization: {
      type: Object,
    },
    resourceClassPrioritization: [
      {
        resourceClass: {
          type: String,
        },
        rank: {
          type: String,
        },
      },
    ],
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

modelSchema.statics.build = (props: WellPrioritizationProperties) => {
  return new WellPrioritization(props);
};

const WellPrioritization = mongoose.model<
  WellPrioritizationDoc,
  WellPrioritizationModel
>('Forecast_WellPrioritization', modelSchema);

export {
  WellPrioritization,
  WellPrioritizationEntitty,
  WellPrioritizationProperties,
  PrioritizationLevelOption,
  StreamPrioritization,
  ResourceClassPrioritization,
  ProductionPrioritizationModel,
};
