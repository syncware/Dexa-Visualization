import "express-async-errors";
import { app } from "./app";

const port = 3000;

const start = async () => {
  try {

    app.listen(port, () =>
      console.log(`Forecast Service is up and running at ${port}`) 
    );
  } catch (err) {
    console.log(err);
    console.log("Server not up and running");
  }
};

start();
