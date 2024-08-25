import { NextFunction, Request, Response } from "express";

const Save_Project_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (!req.body.title) {
      errors.push("Missing title field");
    }
    if (req.body.unitGroup === undefined) {
      errors.push("Missing unitGroup field");
    }
    if (req.body.variableUnits === undefined) {
      errors.push("Missing variable unit field");
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
const Update_Project_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (req.params.projectId === undefined) {
      errors.push("Missing project id field");
    }
    if (!req.body.title) {
      errors.push("Missing title field");
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
const Update_Project_Settings_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (req.params.projectId === undefined) {
      errors.push("Missing project id field");
    }
    if (req.body.unitGroup === undefined) {
      errors.push("Missing unitGroup field");
    }
    if (req.body.variableUnits === undefined) {
      errors.push("Missing variable unit field");
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
  Save_Project_Validation,
  Update_Project_Validation,
  Update_Project_Settings_Validation,
};
