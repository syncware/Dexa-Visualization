import mongoose, { models } from "mongoose";

// required properties to create a MatchObject
interface MatchObjectProperties {
  id: string;
  data: object;
}

// properties that a MatchObject document has
interface MatchObjectDoc extends mongoose.Document, MatchObjectProperties {
  id: string;
}

// properties that MatchObject model has
interface MatchObjectModel extends mongoose.Model<MatchObjectDoc> {
  build(props: MatchObjectProperties): MatchObjectDoc;
}

const modelSchema = new mongoose.Schema({
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

modelSchema.statics.build = (props: MatchObjectProperties) => {
  return new MatchObject(props);
};

const MatchObject = mongoose.model<MatchObjectDoc, MatchObjectModel>(
  "Forecast_MatchObject",
  modelSchema
);

export { MatchObject, MatchObjectProperties, MatchObjectDoc };
