#pragma once
#pragma warning (disable : 4996)
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <cstdio>
using namespace std;

class clsDate
{
private:
	 int _Day, _Month, _Year;
public:
	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}

	static vector <string> SplitString(string S1, string Delim = "/")
	{
		string sWord;
		short pos = 0;
		vector <string> vString;
		while ((pos = S1.find(Delim)) != string::npos)
		{
			sWord = S1.substr(0, pos);
			if (sWord != "")
				vString.push_back(sWord);
			S1.erase(0, pos + Delim.length());
		}
		if (S1 != "")
			vString.push_back(S1);
		return vString;
	}

	static bool isLeapYear(short Year)
	{
		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
	}

	static short NumberOfDaysInAYear(short Year)
	{
		return (isLeapYear(Year)) ? 366 : 365;
	}

	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}

	static int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}

	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}

	static short NumberOfDaysInAmonth(short Month, short Year)
	{
		short NumberOfDaysInMonth[]{ 31, 28, 31 , 30 , 31 , 30, 31, 31 , 30 , 31, 30, 31 };
		if (Month < 1 || Month > 12)
			return 0;
		else
			return (Month == 2) ? ((isLeapYear(Year)) ? 29 : 28) : NumberOfDaysInMonth[Month - 1];
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static short DayOfWeekOrder(clsDate Date)
	{
		return DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
	}

	static string MonthShortName(short MonthName)
	{
		string arr12Months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul"
		, "Aug", "Sep", "Oct", "Nov", "Dec" };
		return arr12Months[MonthName - 1];
	}

	static void PrintMonthCalendar(short Month , short Year)
	{

		int NumberOfDays;
		// Index the Days From 0 to 6
		int Current = DayOfWeekOrder(1, Month, Year);

		NumberOfDays = NumberOfDaysInAmonth(Month, Year);
		// Print the Current Month Name
		printf("\n  ___________________%s___________________\n\n", MonthShortName(Month).c_str());
		// Print The Columns

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n\n");

		// Print Appropriate Spaces
		int i;
		for (i = 0; i < Current; i++)
			printf("     ");
		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n  _________________________________________\n");
	}
	void PrintMonthCalendar() {
		PrintMonthCalendar(_Month, _Year);
	}
	static void PrintYearCalendar(short Year)
	{

		for (short i = 1; i <= 12; ++i)
			PrintMonthCalendar(i , Year);
	}
	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}

    static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;
		for (short i = 1; i < Month; i++)
			TotalDays += NumberOfDaysInAmonth(i, Year);
		TotalDays += Day;
		return TotalDays;
	}

	short NumberOfDaysFromTheBeginingOfTheYear()
	{
		return NumberOfDaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
	}

	clsDate(string strDate)
	{
		vector <string> vString = SplitString(strDate);
		_Day = stoi(vString[0]);
		_Month = stoi(vString[1]);
		_Year = stoi(vString[2]);
	}

	clsDate(int Day, int Month, int Year)
	{

		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short TotalDaysFromTheBeginingOfTheYear, short Year)
	{
		short RemainingDays = TotalDaysFromTheBeginingOfTheYear;
		short MonthDays = 0;
		_Year = Year;
		_Month = 1;
		while (true)
		{
			MonthDays = NumberOfDaysInAmonth(_Month, Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				_Month++;
			}
			else
			{
				_Day = RemainingDays;
				break;
			}
		}

	}

	static string DateToString(clsDate Date)
	{
		return to_string(Date._Day) + "/" + to_string(Date._Month) + "/"
			+ to_string(Date._Year);
	}
	clsDate GetDateOrderFromDayOrderInYear(short DateOrderOfYear, short Year)
	{
		clsDate Date;
		short RemainingDays = DateOrderOfYear;
		short MonthDays = 0;
		Date._Year = Year;
		Date._Month = 1;
		while (true)
		{
			MonthDays = NumberOfDaysInAmonth(Date._Month, Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month++;
			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	clsDate DateAddDays(short Days, clsDate Date)
	{

		short RemainingDays = Days + NumberOfDaysFromTheBeginingOfTheYear(Date._Day, Date._Month
			, Date._Year);
		while (RemainingDays > (isLeapYear(Date._Year) ? 366 : 365))
		{

			RemainingDays -= (isLeapYear(Date._Year) ? 366 : 365);
			Date._Year++;
		}
		Date = GetDateOrderFromDayOrderInYear(RemainingDays, Date._Year);
		return Date;
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{

		return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year)
			? (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ?
				Date1._Day < Date2._Day : false)) : false);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? ((Date1._Day == Date2._Day)
			? true : false) : false) : false;
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return !(IsDate1EqualDate2(Date1, Date2) && IsDate1BeforeDate2(Date1, Date2));
	}

	bool IsLastDayInAMonth(clsDate Date)
	{
		return Date._Day == NumberOfDaysInAmonth(_Month, _Year);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return Month == 12;
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}

	clsDate IncreaseDateByOneDay(clsDate Date)
	{

		if (IsLastDayInAMonth(Date))
		{

			if (IsLastMonthInYear(Date._Month))
			{

				Date._Day = 1;
				Date._Month++;
				Date._Year++;
			}
			else
			{
				Date._Day = 1;
				Date._Month++;
			}
		}
		else
			Date._Day++;
		return Date;
	}

	int GetDiffrenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SwapFlag = 1;
		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			Swap(Date1, Date2);
			SwapFlag = -1;
		}
		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}
		return IncludeEndDay ? ++Days * SwapFlag : Days * SwapFlag;
	}

	static void Swap(clsDate& Date1, clsDate& Date2)
	 {
		clsDate Temp;
		Temp._Day = Date1._Day;
		Temp._Month = Date1._Month;
		Temp._Year = Date1._Year;

		Date1._Day = Date2._Day;
		Date1._Month = Date2._Month;
		Date1._Year = Date2._Year;

		Temp._Day = Date2._Day;
		Temp._Month = Date2._Month;
		Temp._Year = Date2._Year;

	 }

	 short DaysUntilEndOfWeek(clsDate Date)
	 {
		 return 6 - DayOfWeekOrder(Date);
	 }

	 short DaysUntilEndOfMonth(clsDate Date)
	 {
		 clsDate EndOfMonth;

		 EndOfMonth._Day = NumberOfDaysInAmonth(Date._Month, Date._Year);

		 EndOfMonth._Month = Date._Month;
		 EndOfMonth._Year = Date._Year;
		 return GetDiffrenceInDays(Date, EndOfMonth);
	 }

	 short DaysUntilEndOfYear(clsDate Date)
	 {
		 clsDate EndOfYear;

		 EndOfYear._Day = 31;
		 EndOfYear._Month = 12;
		 EndOfYear._Year = Date._Year;

		 return GetDiffrenceInDays(Date, EndOfYear);
	 }

	 bool IsEndOfWeek(clsDate Date)
	 {
		 return DayOfWeekOrder(Date) == 6;
	 }

	 bool IsWeekEnd(clsDate Date)
	 {
		 return DayOfWeekOrder(Date) == 6 || DayOfWeekOrder(Date) == 5;
	 }

	 bool IsBusinessDay(clsDate Date)
	 {
		 return !IsWeekEnd(Date);
	 }

	 short CalculateVacationDays(clsDate Date1, clsDate Date2)
	 {
		 short DaysCount = 0;

		 while (IsDate1BeforeDate2(Date1, Date2))	
		 { 
			 if (IsBusinessDay(Date1))
				 DaysCount++;
			 Date1 = IncreaseDateByOneDay(Date1);
		 }
		 return DaysCount;
	 }

	 clsDate GetReturnDate(clsDate Date, short VacationDays)
	 {

		 short WeekEndCounter = 0;
		 while (IsWeekEnd(Date))
			 Date = IncreaseDateByOneDay(Date);

		 for (int i = 0; i <= VacationDays + WeekEndCounter; ++i)
		 {

			 if (IsWeekEnd(Date)) WeekEndCounter++;

			 Date = IncreaseDateByOneDay(Date);

		 }

		 while (IsWeekEnd(Date))
			 Date = IncreaseDateByOneDay(Date);
		 return Date;
	 }

	 enum enDateCompare {Before = -1 , Equal = 0 , After = 1};

	 enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	 {
		 if (IsDate1BeforeDate2(Date1, Date2))
			 return enDateCompare::Before;
		 else if (IsDate1EqualDate2(Date1, Date2))
			 return enDateCompare::Equal;
		 return enDateCompare::After;
	 }

	 static bool IsValidDate(clsDate Date1)
	 {
		 if (Date1._Day < 1 || Date1._Day > 31) return false;
		 if (Date1._Month < 1 || Date1._Month > 12) return false;
		 if (Date1._Month == 2)
		 {
			 if (isLeapYear(Date1._Year))
			 {
				 if (Date1._Day > 29) return false;
			 }
			 else {
				 if (Date1._Day > 28) return false;
			 }

		 }

		 short DaysInMonth = NumberOfDaysInAmonth(Date1._Month, Date1._Year);

		 if (Date1._Day > DaysInMonth) return false;

		 return true;
	 }

	 static string GetSystemDateString()
	 {

		 short Day, Month, Year, Hour, Minute, Second;
		 // System Datetime string
		 time_t t = time(0);
		 tm* now = localtime(&t);

		 Year = now->tm_year + 1900;
		 Month = now->tm_mon + 1;
		 Day = now->tm_mday;
		 Hour = now->tm_hour;
		 Minute = now->tm_min;
		 Second = now->tm_sec;
		 return (to_string(Day) + "/" + to_string(Month) + "/"
			 + to_string(Year) + " - " + to_string(Hour)
			 + ":" + to_string(Minute) + ":" + to_string(Second));
	 }
	 void Print() 
	 {
		cout << _Day << "/" << _Month << "/" << _Year << "\n";
	 }

};

