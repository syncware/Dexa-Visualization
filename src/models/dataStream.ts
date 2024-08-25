import mongoose, { models } from "mongoose";

// required properties to create a DataStream
interface DataStreamProperties {
  id: string;
  userId: string;
  type: string;
  data: object;
}

// properties that a DataStream document has
interface DataStreamDoc extends mongoose.Document, DataStreamProperties {
  id: string;
}

// properties that DataStream model has
interface DataStreamModel extends mongoose.Model<DataStreamDoc> {
  build(props: DataStreamProperties): DataStreamDoc;
}

const modelSchema = new mongoose.Schema({
  userId: {
    type: String,
    required: true,
  },
  type: {
    type: String,
  },
  data: {
    type: Object,
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

modelSchema.statics.build = (props: DataStreamProperties) => {
  return new DataStream(props);
};

const DataStream = mongoose.model<DataStreamDoc, DataStreamModel>(
  "Forecast_DataStream",
  modelSchema
);

export { DataStream, DataStreamProperties, DataStreamDoc, DataStreamModel };
