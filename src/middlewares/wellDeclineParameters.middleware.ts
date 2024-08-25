import { NextFunction, Request, Response } from "express";

const Save_WellDeclineParameter_Validation = (
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
    if (!req.body.declineParameters) {
      errors.push("Missing decline parameters field");
    }
    if (!req.body.forecastInputDeckId) {
      errors.push("Missing forecast Input deck field");
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

const Generate_DeclineParameters_Default = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (!req.params.forecastInputDeckId) {
      errors.push("Missing forecastInputDeckId field");
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

export { Save_WellDeclineParameter_Validation, Generate_DeclineParameters_Default };
