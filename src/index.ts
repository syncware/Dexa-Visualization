import * as dotenv from "dotenv";
import "express-async-errors";
import mongoose from "mongoose";
import { app } from "./app";

dotenv.config();

const port = process.env.PORT || 3000;
const connectionstring = String(process.env.MONGO_URL); 

const start = async () => {
  try {
    await mongoose.connect(connectionstring, {
      // useNewUrlParser: true,
      // useUnifiedTopology: true,
      // useCreateIndex: true,
      // useFindAndModify: false,
    });
    console.log("Connected to mongodb");

    app.listen(port, () =>
      console.log(`Forecast Service is up and running at ${port}`) 
    );
  } catch (err) {
    console.log(err);
    console.log("Server not up and running");
  }
};

start();
