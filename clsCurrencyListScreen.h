#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrencyListScreen : protected clsScreen
{
private:
	static void _PrintCurrencyRecord(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
		cout << "| " << setw(8) << left << Currency.CurrencyCode();
		cout << "| " << setw(45) << left << Currency.CurrencyName();
		cout << "| " << setw(10) << left << Currency.Rate();
	}


public:
	static void ShowCurrencyListScreen()
	{
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string Title = "\t Currencies List Screen";
		string SubTitle = "\t   (" + to_string(vCurrencies.size()) + ") Currency(s).";

		_DrawScreenHeader(Title, SubTitle);
		
		cout << setw(8) << left << "" << "\n\t_____________________________________________";
		cout << "___________________________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << setw(30) << "Country";
		cout << "| " << setw(8) << left << "Code";
		cout << "| " << setw(45) << left << "Name";
		cout << "| " << setw(10) << left << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t_____________________________________________";
		cout << "___________________________________________________________________\n\n";
		if (vCurrencies.size() == 0)
			cout << "\t\t\t\t\tNo Currencies Available in the system :-(";
		else
			for (clsCurrency Currency : vCurrencies)
			{
				_PrintCurrencyRecord(Currency);
				cout << "\n";
			}
		cout << setw(8) << left << "" << "\n\t_____________________________________________";
		cout << "___________________________________________________________________\n\n";
	}
};

