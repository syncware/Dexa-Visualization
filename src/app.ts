import bodyParser from 'body-parser';
import cookiesession from 'cookie-session';
import express from 'express';
import 'express-async-errors';
import { NotFoundError } from './errors/not-found';
import { error } from './middlewares/error.middleware';
import { forecastResultsRouter } from './routes/forecastResults';

const cors = require('cors');
const app = express();

app.use(bodyParser.json({ limit: '5000mb' }));
app.use(bodyParser.urlencoded({ limit: '5000mb', extended: true }));
app.use(
  cookiesession({
    signed: false,
  })
);

//use cors middleware
app.use(cors());

console.log('App routes initialized.');

app.use('/api/forecast/forecast-results', forecastResultsRouter);

app.get('/api/forecast/health-check', (_, res) => {
  res.status(200).send('Forecast service is healthy');
});

app.all('*', () => {
  throw new NotFoundError();
});

app.use(error);

export { app };

