import express, { Request, Response } from 'express';
import { BadRequestError } from '../errors/bad-request-error';
import { volumeforecastModule } from '../productionforecast/optimizer';
import { SuccessResponse } from '../success/successResponse';

const forecastResultsRouter = express.Router();

forecastResultsRouter.post(
  '/run-forecast',
  async (req: Request, res: Response) => {
    const inputData = req.body;
    


    try {

        // Run Forecast
        const _runForecastResults = await new Promise((resolve, reject) => {
          volumeforecastModule.runForecastAsync(
            inputData,
            runForecastAsyncWorkerCompletion
          );
          async function runForecastAsyncWorkerCompletion(
            err1: any,
            runForecastResult: any
          ) {
            if (err1) {
              return reject(err1);
            } else {
              resolve(runForecastResult);
            }
          }
        });
    
        const result = _runForecastResults as any;

      res.send(SuccessResponse.Success(result));
    } catch {
      throw new BadRequestError('Please check your data.');
    }
  }
);

export { forecastResultsRouter };