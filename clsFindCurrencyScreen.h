#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
class clsFindCurrencyScreen : protected clsScreen
{
private:

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\n\t\t\t\t\tCurrency Card:\n";
        cout << "\t\t\t\t\t_____________________________\n";
        cout << "\n\t\t\t\t\tCountry    : " << Currency.Country();
        cout << "\n\t\t\t\t\tCode       : " << Currency.CurrencyCode();
        cout << "\n\t\t\t\t\tName       : " << Currency.CurrencyName();
        cout << "\n\t\t\t\t\tRate(1$) = : " << Currency.Rate();

        cout << "\n\t\t\t\t\t_____________________________\n";

    }

public:

    static void ShowFindCurrencyScreen()
    {
        _DrawScreenHeader("\t  Find Currency Screen.");
        cout << "\t\t\t\t\tFind By [1] Code or [2] Country ? ";
        short Choice = clsInputValidate<short>::ReadNumberBetween(1, 2, "Invalid Input Please Enter a valid Number Between [1] & [2] ? ");
        if (Choice == 1)
        {
            cout << "\n\t\t\t\t\tPlease Enter Currency Code : ";
            string CurrencyCode = clsInputValidate<string>::ReadString();
            while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode))
            {
                cout << "\n\t\t\t\t\tCurrency isn't Found Please Enter another One ? ";
                CurrencyCode = clsInputValidate<string>::ReadString();
            }

            clsCurrency Currency = Currency.FindByCode(CurrencyCode);
            if (!Currency.IsEmpty())
            {
                cout << "\n\t\t\t\t\tCurrency Found :-)\n";
            }
            else
                cout << "\n\t\t\t\t\tCurrency is not Found :-(\n";
            _PrintCurrency(Currency);
        }
        else if (Choice == 2)
        {
            cout << "\n\t\t\t\t\tPlease Enter Currency Country : ";
            string Country = clsInputValidate<string>::ReadString();
            while (!clsCurrency::IsCurrencyExistByCountry(Country))
            {
                cout << "\n\t\t\t\t\tCurrency isn't Found Please Enter another One ? ";
                Country = clsInputValidate<string>::ReadString();
            }
            clsCurrency Currency = Currency.FindByCountry(Country);
            if (!Currency.IsEmpty())
            {
                cout << "\n\t\t\t\t\tCurrency Found :-)\n";
            }
            else
                cout << "\n\t\t\t\t\tCurrency is not Found :-(\n";
            _PrintCurrency(Currency);
        }

    }

};

