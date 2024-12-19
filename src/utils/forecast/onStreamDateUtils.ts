import { ForecastIInputDeckEntity } from '../../models/forecastInputDeck';

export function GetForecastStartDate(
  forecastInputDecks: ForecastIInputDeckEntity[]
) {
  var i = 0;
  var lent = forecastInputDecks.length;
  var startDate = new Date(
    forecastInputDecks[i].year1P1C,
    forecastInputDecks[i].month1P1C,
    forecastInputDecks[i].day1P1C,
    0,
    0,
    0,
    0
  );

  var date1;
  for (i = 0; i < lent; i++) {
    date1 = new Date(
      forecastInputDecks[i].year1P1C,
      forecastInputDecks[i].month1P1C,
      forecastInputDecks[i].day1P1C,
      0,
      0,
      0,
      0
    );
    if (date1 < startDate) {
      startDate = date1;
    }

    date1 = new Date(
      forecastInputDecks[i].year2P2C,
      forecastInputDecks[i].month2P2C,
      forecastInputDecks[i].day2P2C,
      0,
      0,
      0,
      0
    );
    if (date1 < startDate) {
      startDate = date1;
    }

    date1 = new Date(
      forecastInputDecks[i].year3P3C,
      forecastInputDecks[i].month3P3C,
      forecastInputDecks[i].day3P3C,
      0,
      0,
      0,
      0
    );
    if (date1 < startDate) {
      startDate = date1;
    }
  }

  return startDate;
}

export function GetForecastStopDate(
  forecastInputDecks: ForecastIInputDeckEntity[]
) {
  var i = 0;
  var lent = forecastInputDecks.length;
  var stopDate = new Date(
    forecastInputDecks[i].year1P1C,
    forecastInputDecks[i].month1P1C,
    forecastInputDecks[i].day1P1C,
    0,
    0,
    0,
    0
  );

  var date1;
  for (i = 0; i < lent; i++) {
    date1 = new Date(
      forecastInputDecks[i].year1P1C,
      forecastInputDecks[i].month1P1C,
      forecastInputDecks[i].day1P1C,
      0,
      0,
      0,
      0
    );
    if (date1 > stopDate) {
      stopDate = date1;
    }

    date1 = new Date(
      forecastInputDecks[i].year2P2C,
      forecastInputDecks[i].month2P2C,
      forecastInputDecks[i].day2P2C,
      0,
      0,
      0,
      0
    );
    if (date1 > stopDate) {
      stopDate = date1;
    }

    date1 = new Date(
      forecastInputDecks[i].year3P3C,
      forecastInputDecks[i].month3P3C,
      forecastInputDecks[i].day3P3C,
      0,
      0,
      0,
      0
    );
    if (date1 > stopDate) {
      stopDate = date1;
    }
  }

  var stopDateNew = new Date();
  var year = stopDate.getFullYear();
  var month = stopDate.getMonth();
  var day = stopDate.getDate();
  var stopDateNew = new Date(year + 10, month, day);

  return stopDateNew;
}
