import { NextFunction, Request, Response } from "express";

const Save_WellPrioritization_Validation = (
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
    if (!req.body.productionPrioritizationModel) {
      errors.push("Missing well productionPrioritizationModel entities field");
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

export { Save_WellPrioritization_Validation };
