#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrencyListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"
class clsCurrencyMainScreen : protected clsScreen
{
private:
	enum enCurrencyChoices {eListCurrencies = 1 , eFindCurrency = 2 , 
	eUpdateRate = 3 , eCurrencyCalculator = 4 , eCurrencyShowMainMenu = 5};

	static short _ReadCurrencyMenuOption()
	{
		cout << setw(37) << left << "" << "\tChoose what do you want from [1 to 5] ? ";
		short Choice = clsInputValidate<short>::ReadNumberBetween(1, 5, "Invalid Input Please enter a Valid Input From [1 to 5] ? ");
		return Choice;
	}


	static void _GoBackToCurrencyScreen() {

		cout << "\n\t\t\t\t\tPlease enter any Key to Go Back to Currency Menu....";
		system("pause>0");
		ShowCurrencyMainScreen();
	}

	static void _ShowListCurrencies()
	{
		//cout << "\nCurrency List Screen Will be here...\n";
		clsCurrencyListScreen::ShowCurrencyListScreen();
	}
	static void _ShowFindCurrency()
	{
		//cout << "\nFind Currency Will Be Here ...\n";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRate()
	{
		//cout << "\nUpdate Rate Screen Will be here ...\n";
		clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
	}

	static void _ShowCurrencyCalculator()
	{
		//cout << "\nCurrency Calculator Will be here ...\n";
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrencyMenuOption(enCurrencyChoices Choice)
	{

		switch (Choice)
		{

		case enCurrencyChoices::eListCurrencies:
			system("cls");
			_ShowListCurrencies();
			_GoBackToCurrencyScreen();
			break;
		case enCurrencyChoices::eFindCurrency:
			system("cls");
			_ShowFindCurrency();
			_GoBackToCurrencyScreen();
			break;
		case enCurrencyChoices::eUpdateRate:
			system("cls");
			_ShowUpdateRate();
			_GoBackToCurrencyScreen();
			break;
		case enCurrencyChoices::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculator();
			_GoBackToCurrencyScreen();
			break;
		case enCurrencyChoices::eCurrencyShowMainMenu:
		{
			// don't nothing :-(
		}
		}

	}
public:
	static void ShowCurrencyMainScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tCurrency Exchange Main Screen");
		cout << setw(37) << left << "" << "\t============================================\n";
		cout << setw(37) << left << "" << "\t\t\tCurrency Exchange Menu\n";
		cout << setw(37) << left << "" << "\t============================================\n";
		cout << setw(37) << left << "" << "\t\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t\t[5] Main Menu.\n";
		cout << setw(37) << left << "" << "\t============================================\n";
		_PerformCurrencyMenuOption(enCurrencyChoices(_ReadCurrencyMenuOption()));
	}


};

