import { NextFunction, Request, Response } from 'express';

const Generate_Facility_Network_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (!req.body.facilitiesInputDeckOption) {
      errors.push('please select facilities input deck');
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
const Generate_Entire_Network_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (!req.body.facilitiesInputOption) {
      errors.push('please select facilitiesInputOption');
    }
    if (!req.body.forecastInputOption) {
      errors.push('please select forecastInputOption');
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

const Save_Network_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (!req.body.title) {
      errors.push('Missing title field');
    }
    if (!req.body.facilitiesInputId) {
      errors.push('please select facilities input');
    }
    if (!req.body.forecastInputId) {
      errors.push('please select forecast input');
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

export {
  Generate_Entire_Network_Validation, Generate_Facility_Network_Validation, Save_Network_Validation
};

