#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyMainScreen.h"
#include "Global.h"
#include <iomanip>
class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenueOptions {
	eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
	eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6, 
	eManageUsers = 7, eLogout = 8 , eLoginRegister = 9 , eCurrencyMainMenu = 10,  eExit = 11
	};
	static short _ReadMainMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want from [1 to 11] ? ";
		short Choice = clsInputValidate<short>::ReadNumberBetween(1, 11, "Invalid Input Please enter a Valid Input From [1 to 11] ? ");
		return Choice;
	}

	static void _GoBackToMainMenue() {

		cout << "\n\t\t\t\t\tPlease enter any Key to Go Back to Main Menu....";
		system("pause>0");
		ShowMainMenu();
	}
	
	static void _ShowAllClientsScreen()
	{
		//cout << "\nClient List Screen Will be here...\n";
		clsClientListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen() {
		//cout << "\nAdd New Clients Screen Will be here...\n";
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static  void _ShowDeleteClientScreen() {

		//cout << "\nDelete Client Screen Will Be Here ...\n";
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}
	static void _ShowUpdateClientsScreen() {

		//cout << "\nUpdate Client Screen Will Be Here ...\n";
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}
	static void _ShowFindClientScreen() {
		//cout << "\nFind Client Screen Will Be Here ...\n";
		clsFindClientScreen::_ShowFindClientScreen();
	}
	static void _ShowTransactions() {

		//cout << "\nTransactions Screen Will be Here ...\n";
		clsTransactionsScreen::ShowTransactionMenu();
	}
	static void _ShowManageUsersScreen() {
		//cout << "\nManage Users Screen Wil Be Here ...\n";
		clsManageUsersScreen::ShowManageUsersMenu();
	}
	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}
	static void _ShowCurrencyListScreen()
	{
		clsCurrencyMainScreen::ShowCurrencyMainScreen();
	}
	static void _ShowEndScreen() {

		cout << "\n____________________________________\n";
		cout << "\n\tBank System Ended :-)\n";
		cout << "\n____________________________________\n";
		system("pause>0");
		exit(0);
	}
	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
		// then it will go back to main function
	}
	static void _PerformMainMeunOption(enMainMenueOptions MainMenuOption)
	{

		switch (MainMenuOption)
		{
		case enMainMenueOptions::eListClients:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;

		case enMainMenueOptions::eAddNewClient:
			system("cls");
			_ShowAddNewClientsScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eUpdateClient:
			system("cls");
			_ShowUpdateClientsScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eShowTransactionsMenu:
			_ShowTransactions();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eManageUsers:
			system("cls");
			_ShowManageUsersScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eLogout:
			system("cls");
			_Logout();
			break;
		case enMainMenueOptions::eLoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eCurrencyMainMenu:
			system("cls");
			_ShowCurrencyListScreen();
			_GoBackToMainMenue();
			break;
		case enMainMenueOptions::eExit:
			system("cls");
			_ShowEndScreen();
			break;
		}

	}

public:

	static void ShowMainMenu()
	{
		system("cls");
		_DrawScreenHeader("\t\tMain Screen");
		cout << setw(37) << left << "" << "\t============================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
		cout << setw(37) << left << "" << "\t============================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client List.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Logout.\n";
		cout << setw(37) << left << "" << "\t[9] Login Register.\n";
		cout << setw(37) << left << "" << "\t[10] Currency Exchange.\n";
		cout << setw(37) << left << "" << "\t[11] Exit.\n";
		cout << setw(37) << left << "" << "\t============================================\n";
		_PerformMainMeunOption(enMainMenueOptions(_ReadMainMenueOption()));

	}

};

