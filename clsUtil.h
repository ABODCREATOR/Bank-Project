#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include "clsDate.h"
using namespace std;
class clsUtil
{

public:
	static int RandomNumber(int From, int To)
	{
		return rand() % (To - From + 1) + From;
	}

	static void Srand()
	{
		return srand((unsigned)time(0));
	}

	enum enCharType {SmallLetter = 1 , CapitalLetter = 2 , SpecialCharacter = 4 , Digit = 3 , 
	MixChars = 5};

	static char GetRandomCharacter(enCharType CharType)
	{
		if (CharType == MixChars)
			CharType = enCharType(RandomNumber(1, 3));
		switch (CharType)
		{

		case enCharType::SmallLetter:
			return char(RandomNumber(97, 122));
			break;
		case enCharType::CapitalLetter:
			return char(RandomNumber(65, 90));
			break;
		case enCharType::SpecialCharacter:
			return char(RandomNumber(33, 47));
			break;
		case enCharType::Digit:
			return char(RandomNumber(48, 57));
			break;
		default:
			return char(RandomNumber(65, 90));
		}

	}
	
	static string GenerateWord(enCharType CharType, short Length = 4)
	{
		string Word = "";
		for (int i = 1; i <= Length; i++)
		{
			Word += GetRandomCharacter(CharType);
		}
		return Word;
	}

	static string GenerateKey(enCharType CharType)
	{
		string Key = "";

		Key = GenerateWord(enCharType::MixChars) + "-";
		Key += GenerateWord(enCharType::MixChars) + "-";
		Key += GenerateWord(enCharType::MixChars) + "-";
		Key += GenerateWord(enCharType::MixChars);
		return Key;
	}

	static void GenerateKeys(short NumberOfKeys, enCharType CharType)
	{
		for (int i = 1; i <= NumberOfKeys; i++)
			cout << "Key [" << i << "] : " << GenerateKey(CharType) << endl;
	}

	static void Swap(int& Num1, int& Num2)
	{
		int Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}

	static void Swap(string& Num1, string& Num2)
	{
		string Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}

	static void Swap(double& Num1, double& Num2)
	{
		double Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}

	static void Swap(clsDate& Date1, clsDate& Date2)
	{
		clsDate::Swap(Date1, Date2);
	}

	static void ShuffleArray(int arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; ++i)
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
	}

	static void PrintArray(int arr[100], int arrLength)
	{
		cout << "\nArray Elements : \n";
		for (int i = 0; i < arrLength; i++)
			cout << "Element [" << i << "]  is : " << arr[i] << " ";
		cout << "\n";
	}

	static void ShuffleArray(string arr[100], int arrLength)
	{
		for (int i = 0; i < arrLength; ++i)
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
	}

	static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int rand1 = 1, int rand2 = 100)
	{
		for (int i = 0; i < arrLength; ++i)
			arr[i] = RandomNumber(rand1, rand2);
	}

	static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType)
	{

		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateKey(CharType);
	}

	static string Tabs(short NumberOfTabs)
	{
		string tabs = "";
		for (int i = 0; i <= NumberOfTabs; i++)
		{
			tabs += '\t';
			cout << tabs;
		}
		return tabs;
	}

	static string EncryptText(string Text, short EncryptionKey = 2)
	{
		for (int i = 0; i < Text.length(); i++)
			Text[i] = char((int)Text[i] + EncryptionKey);
		return Text;
	}

	static string DecryptText(string Text, short EncryptionKey = 2)
	{
		for (int i = 0; i < Text.length(); i++)
			Text[i] = char((int)Text[i]  -  EncryptionKey);
		return Text;
	}
	static string NumberToText(long long Number)
	{

		if (Number == 0) 
			return "";
		if (Number >= 1 && Number <= 19)
		{

			string arr[] = { "", "One", "Two", "Three", "Four", "Five"
			, "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirtten", "Fourteen"
			, "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" }; 
			return arr[Number] + " ";
		}

		if (Number >= 20 && Number <= 99)
		{

			string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty"
			, "Seventy", "Eighty", "Ninety" };
			return arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return NumberToText(Number / 100) + " Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return NumberToText(Number / 1000) + " Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return NumberToText(Number / 1000000) + " Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return "One Billion " + NumberToText(Number % 1000000000);
		}

		else
		{
			return NumberToText(Number / 1000000000) + " Billions " + NumberToText(Number % 1000000000);
		}

	}

};

