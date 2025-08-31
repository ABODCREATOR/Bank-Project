#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include <iomanip>
using namespace std;
class clsTransactionsScreen : protected clsScreen
{
private:
	enum enTransactionsMenuOptions {
		eDeposit = 1 , eWithdraw = 2 , eShowTotalBalance = 3 ,
		eTransfer = 4  , eTransferLog = 5, eShowMainMenu = 6
	};

	static short ReadTransactionMenuOption()
	{
	
		cout << setw(37) << left << "" << "\tChoose What do you want from [1 to 6] ? ";
		short Choice = clsInputValidate<short>::ReadNumberBetween(1, 6, "Invalid Input Please enter a Valid input From range [1 to 4] ? ");
		return Choice;
	}

	static void _ShowDepositScreen()
	{
		//cout << "\n Deposit Screen Will Be Here.\n";
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen()
	{
		//cout << "\nWithdraw Screen Will Be Here.\n";
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalances()
	{
		//cout << "\nTotal Balances Will Be Here.\n";
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransferScreen()
	{
		//cout << "\nTransfer Screen Will Be Here.\n";
		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}
	static void _GoBackTotransactionMenu()
	{
		cout << "\n\n\t\t\t\t\tPress any Key to go back to transaction menu ...\n";
		system("pause>0");
		ShowTransactionMenu();
	}


	static void _PerformTransactionMenuOption(enTransactionsMenuOptions Option)
	{
		switch (Option)
		{
		case enTransactionsMenuOptions::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackTotransactionMenu();
			break;
		case enTransactionsMenuOptions::eWithdraw:
			system("cls");
			_ShowWithdrawScreen();
			_GoBackTotransactionMenu();
			break;	
		case enTransactionsMenuOptions::eShowTotalBalance:
			system("cls");
			_ShowTotalBalances();
			_GoBackTotransactionMenu();
			break;
		case enTransactionsMenuOptions::eTransfer:
			system("cls");
			_ShowTransferScreen();
			_GoBackTotransactionMenu();
			break;
		case enTransactionsMenuOptions::eTransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackTotransactionMenu();
			break;	
		case enTransactionsMenuOptions::eShowMainMenu:
		{
			// Don't Do Any Thing
		}

		}


	}

public:

	static void ShowTransactionMenu()
	{
		system("cls");
		if (!CheckAccessPermissions(clsUser::enPermissions::pTransactions))
			return;
		_DrawScreenHeader("\t  Transactions Screen\n");

		cout << setw(37) << left << "" << "\t===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tTransactions Menu\n";
		cout << setw(37) << left << "" << "\t===========================================\n";
		cout << setw(37) << left << "" << "\t\t\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t\t\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t\t\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t\t\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t\t\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t\t\t[6] Main Menu.\n";
		cout << setw(37) << left << "" << "\t===========================================\n";

		_PerformTransactionMenuOption((enTransactionsMenuOptions)ReadTransactionMenuOption());
	}

};


