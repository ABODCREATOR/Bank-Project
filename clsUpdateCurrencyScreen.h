#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsUpdateCurrencyScreen : protected clsScreen
{
private :

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

    static void ShowUpdateCurrencyScreen()
    {

        _DrawScreenHeader("\t  Update Currency Screen");
        cout << "\n\t\t\t\t\tPlease Enter Currency Code: ";
        string CurrencyCode = clsInputValidate<string>::ReadString();

        while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode))
        {
            cout << "\n\t\t\t\t\tCurrency isn't Found Please Enter another One ? ";
            CurrencyCode = clsInputValidate<string>::ReadString();
        }

        clsCurrency Currency = Currency.FindByCode(CurrencyCode);
        _PrintCurrency(Currency);
        char Answer = 'n';
        cout << "\n\t\t\t\t\tAre you sure you want to update the rate of this currency y/n? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
            cout << "\n\t\t\t\t\tUpdate Currency Rate:\n";
            cout << "\t\t\t\t\t__________________________\n";
            double Rate = 0.00;
            cout << "Enter New Rate: ";
            Rate = clsInputValidate<double>::ReadNumber();
            Currency.UpdateRate(Rate);
            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrency(Currency);
        }
        else
            cout << "\n\t\t\t\t\tOperation is cancelled :-(\n";
    }

};

