import { NextFunction, Request, Response } from 'express';

const Save_EquipmentCrudeLosses_Validation = (
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
    if (!req.body.equipmentCrudeLossesModel) {
      errors.push('Missing Equipment CrudeLosses Model');
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

export { Save_EquipmentCrudeLosses_Validation };
