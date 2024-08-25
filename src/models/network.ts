import mongoose from "mongoose";

interface NetworkNode {
  id: string;
  position: object;
  type?: string;
  __rf?: any;
  data?: any;
  style?: object;
  className?: string;
  targetPosition?: string;
  sourcePosition?: string;
  isHidden?: boolean;
  draggable?: boolean;
  selectable?: boolean;
  connectable?: boolean;
}

interface NetworkEdge {
  id: string;
  type?: string;
  source: string;
  target: string;
  sourceHandle?: string | null;
  targetHandle?: string | null;
  label?: string;
  labelStyle?: string;
  labelShowBg?: boolean;
  labelBgStyle?: string;
  labelBgPadding?: [number, number];
  labelBgBorderRadius?: number;
  style?: string;
  animated?: boolean;
  arrowHeadType?: string;
  isHidden?: boolean;
  data?: any;
  className?: string;
}

// required properties to create a Network
interface NetworkProperties {
  projectId: string;
  userId: string;
  title: string;
  description: string;
  facilitiesInputId: string;
  forecastInputId: string;

  facilitiesInputTitle: string;
  forecastInputTitle: string;
  nodes: Array<NetworkNode>;
  edges: Array<NetworkEdge>;
}

// properties that a Network document has
interface NetworkDoc extends mongoose.Document, NetworkProperties {
  isDeleted: boolean;
  createdAt: Date;
}

// properties that Network model has
interface NetworkModel extends mongoose.Model<NetworkDoc> {
  build(props: NetworkProperties): NetworkDoc;
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
  facilitiesInputId: {
    type: String,
    required: true,
  },
  facilitiesInputTitle: {
    type: String,
  },
  forecastInputId: {
    type: String,
  },
  forecastInputTitle: {
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
  nodes: [
    {
      id: {
        type: String,
      },
      position: {
        x: { type: Number },
        y: { type: Number },
      },
      type: {
        type: String,
      },
      __rf: {
        type: mongoose.SchemaTypes.Mixed,
      },
      data: {
        type: mongoose.SchemaTypes.Mixed,
      },
      style: {
        type: Object,
      },
      className: {
        type: String,
      },
      targetPosition: {
        type: String,
      },
      sourcePosition: {
        type: String,
      },
      isHidden: {
        type: Boolean,
      },
      draggable: {
        type: Boolean,
      },
      selectable: {
        type: Boolean,
      },
      connectable: {
        type: Boolean,
      },
    },
  ],
  edges: [
    {
      id: {
        type: String,
      },
      type: {
        type: String,
      },
      source: {
        type: String,
      },
      target: {
        type: String,
      },
      sourceHandle: {
        type: String,
      },
      targetHandle: {
        type: String,
      },
      label: {
        type: String,
      },
      labelStyle: {
        type: String,
      },
      labelShowBg: {
        type: Boolean,
      },
      labelBgStyle: {
        type: String,
      },
      labelBgPadding: {
        type: Array<Number>(),
      },
      labelBgBorderRadius: {
        type: Number,
      },
      style: {
        type: String,
      },
      animated: {
        type: Boolean,
      },
      arrowHeadType: {
        type: String,
      },
      isHidden: {
        type: Boolean,
      },
      data: {
        type: mongoose.SchemaTypes.Mixed,
      },
      className: {
        type: String,
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

modelSchema.statics.build = (props: NetworkProperties) => {
  return new Network(props);
};
const Network = mongoose.model<NetworkDoc, NetworkModel>(
  "Forecast_Network",
  modelSchema
);

export { Network, NetworkProperties, NetworkNode, NetworkEdge };
