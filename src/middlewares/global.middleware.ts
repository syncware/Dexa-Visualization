import { NextFunction, Request, Response } from "express";

const Update_GlobalVariableUnit_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (req.params.id === undefined) {
      errors.push("Missing Id field");
    }
    if (req.body.displayUnitId === undefined) {
      errors.push("Missing Display Unit field");
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
const Save_GlobalVariableUnit_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (req.body.data === undefined) {
      errors.push("Missing list of variable and unit data=[] field");
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
  Update_GlobalVariableUnit_Validation,
  Save_GlobalVariableUnit_Validation,
};
