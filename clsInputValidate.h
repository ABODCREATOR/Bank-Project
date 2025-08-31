#pragma once
#include "clsDate.h"
template <typename T1>
class clsInputValidate
{
public:
	
	
	static bool IsNumberBetween(T1 Target, T1 From, T1 To)
	{
		return Target >= From && Target <= To;
	}
	
	static bool IsDateBetween(T1 Date, T1 From, T1 To)
	{
		// Date >= From ---> Date Must Be equal or greater than from
		// Date <= To ---> Date Must Be equal or lower than to

		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			&& (clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)))
			return true;

		if ((clsDate::IsDate1AfterDate2(Date , To) || clsDate::IsDate1EqualDate2(Date , To))
			&& (clsDate::IsDate1BeforeDate2(Date , From) || clsDate::IsDate1EqualDate2(Date , From)))
			return true;

	}

	static T1 ReadNumber(string Message = "Invalid Input Please Enter a Valid integer number ? ")
	{

		T1 Number = 0;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();

			cin.ignore(numeric_limits<streamsize> ::max(), '\n');

			cout << Message << "\n";
			cin >> Number;
		}
		return Number;
	}

	static T1 ReadNumberBetween(T1 From, T1 To ,  string Message = "Invalid Input Please Enter a valid number between 1 and 5")
	{

		T1 Number = 0;
		cin >> Number;

		while (!IsNumberBetween(Number, From, To))
		{
			cout << Message;
			Number = ReadNumber();
		}
		
		return Number;
	}
	static bool IsValidDate(T1 Date1)
	{
		return clsDate::IsValidDate(Date1);
	}

	static string ReadString()
	{
		string S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}

	
};

