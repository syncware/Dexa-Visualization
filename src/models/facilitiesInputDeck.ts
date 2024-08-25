import mongoose from 'mongoose';

// required properties to create a facility
interface FacilitiesInputDeckProperties {
  projectId: string;
  userId: string;
  inputDeckData: any[];
  title: string;
  description: string;
  source: string; // external/apex
  variableUnits: object;
  variableUnitTitles: object;
  validationModel: object;
  productionEquipments: object;
}

// properties that a facility document has
interface FacilitiesInputDeckDoc
  extends mongoose.Document,
    FacilitiesInputDeckProperties {
  isDeleted: boolean;
  createdAt: Date;
}

// properties that facility model has
interface FacilitiesInputDeckModel extends mongoose.Model<FacilitiesInputDeckDoc> {
  build(props: FacilitiesInputDeckProperties): FacilitiesInputDeckDoc;
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
    default: 'apex',
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
  inputDeckData: Object,
  validationModel: Object,
  productionEquipments: Object,
});

modelSchema.methods.toJSON = function () {
  const model = this.toObject();
  model.id = model._id;

  delete model._id;
  delete model.__v;

  return model;
};

modelSchema.statics.build = (props: FacilitiesInputDeckProperties) => {
  return new FacilitiesInputDeck(props);
}; 

const FacilitiesInputDeck = mongoose.model<
  FacilitiesInputDeckDoc,
  FacilitiesInputDeckModel
>('Forecast_FacilitiesInputDeck', modelSchema);

export { FacilitiesInputDeck, FacilitiesInputDeckDoc, FacilitiesInputDeckProperties };

