import { NextFunction, Request, Response } from 'express';

const Run_Forecast_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (!req.body.networkId) {
      errors.push('Missing network field');
    }
    if (!req.body.forecastParametersId) {
      errors.push('Missing forecasting parameter field');
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

const Save_Forecast_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.params) {
    if (!req.params.title) {
      errors.push('title');
    }
    if (!req.params.projectId) {
      errors.push('Missing project field');
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

const ChartData_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (!req.body.forecastResultsIds) {
      errors.push('Missing forecastResultsIds field');
    }
    if (!req.body.forecastsolutionSpaces) {
      errors.push('Missing forecastsolutionSpaces field');
    }
    if (!req.body.selectedVariables) {
      errors.push('Missing selectedVariables field');
    }
    if (!req.body.selectedModulePaths) {
      errors.push('Missing selectedModulePaths field');
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

const Data_Columns_Validation = (
  req: Request,
  res: Response,
  next: NextFunction
) => {
  let errors: String[] = [];
  if (req.body) {
    if (!req.body.forecastInputDeckId) {
      errors.push('Missing forecastInputDeckId field');
    }
    if (!req.body.dataColumns) {
      errors.push('Missing dataColumns field');
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
  ChartData_Validation,
  Data_Columns_Validation,
  Run_Forecast_Validation,
  Save_Forecast_Validation,
};
