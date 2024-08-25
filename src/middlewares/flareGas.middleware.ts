import { NextFunction, Request, Response } from 'express';

const Save_FlareGas_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (!req.body.projectId) {
      errors.push('Missing projectId');
    }
    if (!req.body.title) {
      errors.push('Missing title');
    }
    if (!req.body.flareGasModel) {
      errors.push('Missing Flare Gas Model');
    }

    if (errors.length) {
      return res.status(400).send({ errors: errors.join(',') });
    } else {
      return next();
    }
  } else {
    return res.status(400).send({ errors: 'Missing valid fields' });
  }
};

export { Save_FlareGas_Validation };
