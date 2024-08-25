import { NextFunction, Request, Response } from "express";

const Save_ForecastParameter_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (!req.body.projectId) {
      errors.push("Missing project field");
    }
    if (!req.body.title) {
      errors.push("Missing title field");
    }
    if (!req.body.type) {
      errors.push("Missing type field");
    }
    if (!req.body.declineParametersId) {
      errors.push("Missing decline parameters field");
    }
    if (!req.body.forecastInputDeckId) {
      errors.push("Missing forecast Input deck field");
    }
    if (!req.body.parametersEntity) {
      errors.push("Missing parameter entire field");
    }

    if (errors.length) {
      return res.status(400).send({ errors: errors.join(",") });
    } else {
      return next();
    }
  } else {
    return res.status(400).send({ errors: "Missing valid fields" });
  }
};

const Update_ForecastParameter_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (req.body.forecastParametersId === undefined) {
      errors.push("Missing forecasting Parameters field");
    }
    if (req.body.parametersEntity === undefined) {
      errors.push("Missing parameter field");
    }

    if (errors.length) {
      return res.status(400).send({ errors: errors.join(",") });
    } else {
      return next();
    }
  } else {
    return res.status(400).send({ errors: "Missing valid fields" });
  }
};
export {
  Save_ForecastParameter_Validation,
  Update_ForecastParameter_Validation,
};
