#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsCurrencyCalculatorScreen  : protected clsScreen
{
private:
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\n\t\t\t\t\t_____________________________\n";
        cout << "\n\t\t\t\t\tCountry    : " << Currency.Country();
        cout << "\n\t\t\t\t\tCode       : " << Currency.CurrencyCode();
        cout << "\n\t\t\t\t\tName       : " << Currency.CurrencyName();
        cout << "\n\t\t\t\t\tRate(1$) = : " << Currency.Rate();

        cout << "\n\t\t\t\t\t_____________________________\n";

    }

    static double ConvertFromRateToDollar(double Amount, clsCurrency Currency1)
    {
        return (Amount / Currency1.Rate());
    }

    static double ConvertFromRateToAnother(double Amount, clsCurrency Currency1 , clsCurrency Currency2)
    {
        return  ConvertFromRateToDollar(Amount, Currency1) * Currency2.Rate();
    }

public:
    static void ShowCurrencyCalculatorScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Currency Calculator Screen");
        cout << "\n\t\t\t\t\tPlease Enter Currency Code 1: ";
        string CurrencyCode1 = clsInputValidate<string>::ReadString();

        while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode1))
        {
            cout << "\n\t\t\t\t\tCurrency isn't Found Please Enter another One ? ";
            CurrencyCode1 = clsInputValidate<string>::ReadString();
        }
        cout << "\n\t\t\t\t\tPlease Enter Currency Code 2: ";
        string CurrencyCode2 = clsInputValidate<string>::ReadString();


        while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode2))
        {
            cout << "\n\t\t\t\t\tCurrency isn't Found Please Enter another One ? ";
            CurrencyCode2 = clsInputValidate<string>::ReadString();
        }
        if (CurrencyCode1 == CurrencyCode2)
        {
            cout << "\n\t\t\t\t\tCannot Calculate, Because the Codes are the same :-(\n";
            return;
        }
        if (CurrencyCode2 == "usd" || CurrencyCode2 == "USD")
        {
            clsCurrency Currency1 = clsCurrency::FindByCode(CurrencyCode1);
            clsCurrency Currency2 = clsCurrency::FindByCode(CurrencyCode2);
            double Amount = 0.00;
            cout << "\n\t\t\t\t\tEnter Amount to Exchange: ";
            Amount = clsInputValidate<float>::ReadNumber();
            cout << "\n\t\t\t\t\tConvert From: ";
            _PrintCurrency(Currency1);
            cout << "\t\t\t\t\t" << Amount << " " << Currency1.CurrencyCode() << " = "
                << ConvertFromRateToDollar(Amount, Currency1)
                << " " << Currency2.CurrencyCode();
            char Answer = 'n';
            cout << "\n\t\t\t\t\tDo you want to perform another calculation? y/n ? ";
            cin >> Answer;
            if (tolower(Answer) == 'y')
                ShowCurrencyCalculatorScreen();
        }
        else
        {
            clsCurrency Currency1 = clsCurrency::FindByCode(CurrencyCode1);
            clsCurrency Currency2 = clsCurrency::FindByCode(CurrencyCode2);
            double Amount = 0.00;
            cout << "\n\t\t\t\t\tEnter Amount to Exchange: ";
            Amount = clsInputValidate<float>::ReadNumber();
            cout << "\n\t\t\t\t\tConvert From: ";
            _PrintCurrency(Currency1);
            cout << "\t\t\t\t\t" << Amount << " " << Currency1.CurrencyCode() << " = "
                << ConvertFromRateToAnother(Amount, Currency1, Currency2)
                << " " << Currency2.CurrencyCode();
            char Answer = 'n';
            cout << "\n\t\t\t\t\tDo you want to perform another calculation? y/n ? ";
            cin >> Answer;
            if (tolower(Answer) == 'y')
                ShowCurrencyCalculatorScreen();
        }
    }
};

