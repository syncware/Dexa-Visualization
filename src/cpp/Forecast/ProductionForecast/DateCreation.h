#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include <chrono>
#include "Forecast.h"

using namespace std;
using namespace std::chrono;

class  DateCreation
{
private:

public:
	DateCreation();
	void GetDateList(vector<InputDeckStruct>& decks, Date& StopDate, 
	vector<Date>& equipmentsScheduleDates);
	bool Compare(const Date& d1, const Date& d2);
	bool EqualTo(const Date& d1, const Date& d2);
	bool EqualTo2(const Date& d1, const Date& d2);
	Date GetMinimumDate(const Date& d1, const Date& d2);
	Date GetMaximumDate(const Date& d1, const Date& d2);
	bool IsMinimumDate(Date& d1, Date& d2);
	bool IsMaximumDate(Date& d1, Date& d2);
	bool IsContains(vector<Date>& dates, Date& d1);
	Date DateIncrementByMonth(Date& d1);
	Date DateIncrementByMonth(Date& d, int& numberOfMonths);
	Date DateIncrementByYears(Date& d1, int& numberOfYears);
	void SortDate(vector<Date>& dates);
	int DaysInMonth(int& month);
	int DateDiff_TotalDays(Date& d1, Date& d2);
	void GetDaysList(Date& StartDate);
	~DateCreation();

	vector<Date> dateTimes;
	vector<int> daysList;
};


DateCreation::DateCreation()
{

}

DateCreation::~DateCreation()
{

}

bool DateCreation::Compare(const Date& d1, const Date& d2)
{
	if (d1.year < d2.year)
	{
		return true;
	}

	if (d1.year == d2.year && d1.month < d2.month)
	{
		return true;
	}

	if (d1.year == d2.year && d1.month == d2.month && d1.day < d2.day)
	{
		return true;
	}

	return false;
}

bool DateCreation::EqualTo(const Date& d1, const Date& d2)
{
	if (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day)
	{
		return true;
	}

	return false;
}

bool DateCreation::EqualTo2(const Date& d1, const Date& d2)
{
	//&& d1.day == d2.day
	if (d1.year == d2.year && d1.month == d2.month)
	{
		return true;
	}

	return false;
}

Date DateCreation::GetMinimumDate(const Date& d1, const Date& d2)
{
	bool check = false;

	check = Compare(d1, d2);

	if (check == true)
	{
		return d1;
	}
	else
	{
		return d2;
	}

}

Date DateCreation::GetMaximumDate(const Date& d1, const Date& d2)
{
	bool check = false;

	check = Compare(d1, d2);

	if (check == true)
	{
		return d2;
	}
	else
	{
		return d1;
	}

}

bool DateCreation::IsMinimumDate(Date& d1, Date& d2)
{
	bool check = false;

	check = Compare(d1, d2);

	if (check == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DateCreation::IsMaximumDate(Date& d1, Date& d2)
{
	bool check = false;

	check = Compare(d1, d2);

	if (check == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DateCreation::IsContains(vector<Date>& dates, Date& d1)
{
	bool check = false;
	int datessize = dates.size();
	for (int i = 0; i < datessize; i++)
	{
		if (dates[i].year == d1.year && dates[i].month == d1.month && dates[i].day == d1.day)
		{
			check = true; break;
		}
	}

	return check;
}

Date DateCreation::DateIncrementByMonth(Date& d, int& numberOfMonths)
{
	Date date;
	date.day = d.day;
	date.month = d.month;
	date.year = d.year;
	int i = 1;
	for(i = 1; i <=  numberOfMonths; i++){
		date = DateIncrementByMonth(date);
	}
	return date;
}

Date DateCreation::DateIncrementByMonth(Date& d)
{
	
	Date d2;
	d2.day = d.day;
	d2.month = d.month;
	d2.year = d.year;

	switch (d2.month)
	{
	case 1:
		d2.month = d2.month + 1;
		if(d2.day > 28)
		{
			d2.day = 28;
		}
		break;
	case 2:
		d2.month = d2.month + 1;
		if(d2.day > 31)
		{
			d2.day = 31;
		}
		break;
	case 3:
		d2.month = d2.month + 1;
		if(d2.day > 30)
		{
			d2.day = 30;
		}
		break;
	case 4:
		d2.month = d2.month + 1;
		if(d2.day > 31)
		{
			d2.day = 31;
		}
		break;
	case 5:
		d2.month = d2.month + 1;
		if(d2.day > 30)
		{
			d2.day = 30;
		}
		break;
	case 6:
		d2.month = d2.month + 1;
		if(d2.day > 31)
		{
			d2.day = 31;
		}
		break;
	case 7:
		d2.month = d2.month + 1;
		if(d2.day > 31)
		{
			d2.day = 31;
		}
		break;
	case 8:
		d2.month = d2.month + 1;
		if(d2.day > 30)
		{
			d2.day = 30;
		}
		break;
	case 9:
		d2.month = d2.month + 1;
		if(d2.day > 31)
		{
			d2.day = 31;
		}
		break;
	case 10:
		d2.month = d2.month + 1;
		if(d2.day > 30)
		{
			d2.day = 30;
		}
		break;
	case 11:
		d2.month = d2.month + 1;
		if(d2.day > 31)
		{
			d2.day = 31;
		}
		break;
	case 12:
		d2.month = 1;
		d2.year = d2.year + 1;
		if(d2.day > 31)
		{
			d2.day = 31;
		}
		break;
	}

	return d2;
}

Date DateCreation::DateIncrementByYears(Date& d1, int& numberOfYears)
{
	Date d2;
	d2.day = d1.day;
	d2.month = d1.month;
	d2.year = d1.year + numberOfYears;
	return d2;

}


void DateCreation::SortDate(vector<Date>& dates)
{
	int datessize = dates.size();

	for (int i = 0; i < datessize - 1; i++)
	{
		for (int j = i + 1; j < datessize; j++)
		{
			if (IsMaximumDate(dates[i], dates[j]) == true)
			{
				Date temp = dates[i];
				dates[i] = dates[j];
				dates[j] = temp;
			}
		}
	}
}


void DateCreation::GetDateList(vector<InputDeckStruct>& decks,
Date& StopDate, vector<Date>& equipmentsScheduleDates)
{

	int size = decks.size();
	Date StartDate;
	std::vector<Date> dateTimesTemp;
	int nEquipmentsScheduleDates = equipmentsScheduleDates.size();
	//int& numberOfYears
	//std::cout << "size: " << size << std::endl;

	//Well OSDs
	for (int i = 0; i < size; i++)
	{
		//std::cout << decks->Date_1P_1C.day << "/" << decks->Date_1P_1C.month << "/" << decks->Date_1P_1C.year << std::endl;

		if (IsContains(dateTimesTemp, decks[i].Date_1P_1C) == false)
			dateTimesTemp.push_back(decks[i].Date_1P_1C);

		//std::cout << decks->Date_2P_2C.day << "/" << decks->Date_2P_2C.month << "/" << decks->Date_2P_2C.year << std::endl;

		if (IsContains(dateTimesTemp, decks[i].Date_2P_2C) == false)
			dateTimesTemp.push_back(decks[i].Date_2P_2C);

		//std::cout << decks->Date_3P_3C.day << "/" << decks->Date_3P_3C.month << "/" << decks->Date_3P_3C.year << std::endl;

		if (IsContains(dateTimesTemp, decks[i].Date_3P_3C) == false)
			dateTimesTemp.push_back(decks[i].Date_3P_3C);
	
		 //std::cout << dateTimes[i].day << "/" << dateTimes[i].month << "/" << dateTimes[i].year << std::endl;
	}

	//Equipments Schedules Dates
	/* for (int i = 0; i < nEquipmentsScheduleDates; i++)
	{
		
		if (IsContains(dateTimesTemp, equipmentsScheduleDates[i]) == false)
			dateTimesTemp.push_back(equipmentsScheduleDates[i]);
	} */

	StartDate = dateTimesTemp[0];
	int dateTimesTempsize = dateTimesTemp.size();
	for (int i = 1; i < dateTimesTempsize; i++)
	{
		StartDate = GetMinimumDate(StartDate, dateTimesTemp[i]);
	}

	Date d = StartDate;
	//StopDate = DateIncrementByYears(StartDate,  numberOfYears);

	dateTimes.clear();

	while (IsMinimumDate(d, StopDate) == true) {

		if (IsContains(dateTimes, d) == false)
			dateTimes.push_back(d);

		d = DateIncrementByMonth(d);

			//std::cout << d.day << "/" << d.month << "/" << d.year << std::endl;
	}

	/* dateTimesTempsize = dateTimesTemp.size();
	for (int i = 0; i < dateTimesTempsize; i++)
	{
		if (IsContains(dateTimes, dateTimesTemp[i])  == false && IsMinimumDate(dateTimesTemp[i], StopDate))
		{
			dateTimes.push_back(dateTimesTemp[i]);
		}
	} */
	

	SortDate(dateTimes);

	dateTimesTempsize = dateTimes.size();
	std::cout << dateTimes[0].day << "/" << dateTimes[0].month 
	<< "/" << dateTimes[0].year << std::endl;

	std::cout << dateTimes[dateTimesTempsize-1].day 
	<< "/" << dateTimes[dateTimesTempsize-1].month << "/" 
	<< dateTimes[dateTimesTempsize-1].year << std::endl;

	/* cout << ""  << endl;
	cout << ""  << endl;

	
	for (int i = 0; i < dateTimesTempsize; i++)
	{
		cout << dateTimes[i].day << endl;
		cout  << dateTimes[i].month << endl;
		cout <<  dateTimes[i].year << endl;
		cout << dateTimes[i].day << "/" << dateTimes[i].month << "/" << dateTimes[i].year << endl;
	}  */

}


int DateCreation::DaysInMonth(int& month)
{
	int days = 0;
	switch (month)
	{
	case 1:
		days = 31;
		break;
	case 2:
		days = 28;
		break;
	case 3:
		days = 31;
		break;
	case 4:
		days = 30;
		break;
	case 5:
		days = 31;
		break;
	case 6:
		days = 30;
		break;
	case 7:
		days = 31;
		break;
	case 8:
		days = 31;
		break;
	case 9:
		days = 30;
		break;
	case 10:
		days = 31;
		break;
	case 11:
		days = 30;
		break;
	case 12:
		days = 31;
		break;
	}

	return days;
}

int DateCreation::DateDiff_TotalDays(Date& d1, Date& d2)
{
	/* int days = 0;

	 if (d1.year > d2.year)
	{
		for (int i = d2.year; i < d1.year; i++)
		{
			if ((i % 4) == 0)days = days + 366;
			else days = days + 365;

		}
	}
	else
	{
		for (int i = d2.year; i < d1.year; i++)
		{
			if ((i % 4) == 0)days = days - 366;
			else days = days - 365;
		}
	}

	if (d1.month > d2.month)
	{
		for (int i = d2.month; i < d1.month; i++)
		{
			days = days + DaysInMonth(i);
		}
	}
	else
	{
		for (int i = d1.month; i < d2.month; i++)
		{
			days = days - DaysInMonth(i);
		}
	}

	if (d1.day > d2.day)
	{
		days = days + (d1.day - d2.day);
	}
	else
	{
		days = days - (d2.day - d1.day);
	} */

	// Define two dates
    tm date1 = {0}; // Initialize with all fields set to 0
    date1.tm_year = d2.year - 1900; // Year since 1900 (2024 - 1900)
    date1.tm_mon = d2.month - 1;    // Month (0 - 11)
    date1.tm_mday = d2.day;  // Day of the month (1 - 31)

    std::tm date2 = {0}; // Initialize with all fields set to 0
    date2.tm_year = d1.year - 1900; // Year since 1900 (2024 - 1900)
    date2.tm_mon = d1.month - 1;    // Month (0 - 11)
    date2.tm_mday = d1.day;  // Day of the month (1 - 31)

    // Convert std::tm to time_t
    std::time_t time1 = std::mktime(&date1);
    std::time_t time2 = std::mktime(&date2);

    // Calculate the difference in seconds
    double difference = std::difftime(time2, time1);

    // Convert seconds to days
    int days_difference = static_cast<int>(difference) / (60 * 60 * 24);

	return  days_difference;
}

void DateCreation::GetDaysList(Date& StartDate)
{
	int days = 0;
	int dateTimessize = dateTimes.size();
	for (int i = 0; i < dateTimessize; i++)
	{
		days = DateDiff_TotalDays(dateTimes[i], StartDate);
		if(i > 0){
			double a =  DateDiff_TotalDays(dateTimes[i], dateTimes[i-1]);
			if(a <= 0){
				break;
			}
		}
		//cout << "days: " << days << endl;
		daysList.push_back(days);
	}
}