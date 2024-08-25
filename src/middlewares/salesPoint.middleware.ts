import { NextFunction, Request, Response } from "express";

const Save_SalesPoint_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (req.body.projectId === undefined) {
      errors.push("Missing projectId");
    }
    if (req.body.title === undefined) {
      errors.push("Missing title");
    }
    if (req.body.salesPointModel === undefined) {
      errors.push("Missing salesPointModel");
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

export { Save_SalesPoint_Validation };
