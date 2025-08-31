#pragma once
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsListUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageUsersScreen : protected clsScreen
{
private : 
	enum enManageUsersList {eListUsers = 1 , eAddNewUser = 2 , eDeleteUsers = 3,
	eUpdateUser = 4 , eFindUser = 5, eShowMainMenu = 6};


	static short _ReadManageUserOption()
	{
		short Choice = 0;
		cout << "\n\t\t\t\t\tPlease Enter Any Option From [1 to 6] ? ";
		Choice = clsInputValidate<short>::ReadNumberBetween(1, 6, "Invalid Input Please Enter a valid Input From [1 to 6] ? ");
		return Choice;
	}

	static void _ShowUsersList()
	{
		//cout << "\n\t\t\t\tUsers List Will Be Here.\n";
		clsListUserScreen::ShowUsersList();
	}

	static void _AddNewUser()
	{
		//cout << "\n\t\t\t\tAdd New User Will Be Here.\n";
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _DeleteUser()
	{
		//cout << "\n\t\t\t\tDelete User Will Be Here.\n";
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _UpdateUser()
	{
		//cout << "\n\t\t\t\tUpdate User Will Be Here.\n";
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _FindUser()
	{
		//cout << "\n\t\t\t\tFind User Will Be Here.\n";
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _GoBackToManageUsersMenu()
	{
		cout << "\n\t\t\t\tPress Any Key To Go Back to Manage Users Menu...\n";
		system("pause>0");
		ShowManageUsersMenu();
	}
	
	static void _PerformManageUserOption(enManageUsersList ManageOption)
	{
		switch (ManageOption)
		{
		case enManageUsersList::eListUsers:
			system("cls");
			_ShowUsersList();
			_GoBackToManageUsersMenu();
			break;
		case enManageUsersList::eAddNewUser:
			system("cls");
			_AddNewUser();
			_GoBackToManageUsersMenu();
			break;	
		case enManageUsersList::eDeleteUsers:
			system("cls");
			_DeleteUser();
			_GoBackToManageUsersMenu();
			break;	
		case enManageUsersList::eUpdateUser:
			system("cls");
			_UpdateUser();
			_GoBackToManageUsersMenu();
			break;
		case enManageUsersList::eFindUser:
			system("cls");
			_FindUser();
			_GoBackToManageUsersMenu();
			break;
		case enManageUsersList::eShowMainMenu:
		{
			// nothing
		}
		}

	}

public:
	static void ShowManageUsersMenu()
	{
		if (!CheckAccessPermissions(clsUser::enPermissions::pManageUsers))
			return;
		system("cls");

		_DrawScreenHeader("\t  Manage Users Screen");

		cout << "\n\t\t\t\t\t==========================================\n";
		cout << "\t\t\t\t\t\t\tManage Users List.";
		cout << "\n\t\t\t\t\t==========================================\n";
		cout << "\t\t\t\t\t\t\t[1] List Users.\n";
		cout << "\t\t\t\t\t\t\t[2] Add New User.\n";
		cout << "\t\t\t\t\t\t\t[3] Delete User.\n";
		cout << "\t\t\t\t\t\t\t[4] Update User.\n";
		cout << "\t\t\t\t\t\t\t[5] Find User.\n";
		cout << "\t\t\t\t\t\t\t[6] Main Menu.\n";
		cout << "\t\t\t\t\t==========================================\n";

		_PerformManageUserOption(enManageUsersList(_ReadManageUserOption()));
	}


};

