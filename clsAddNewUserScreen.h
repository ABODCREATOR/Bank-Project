#pragma once

#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{

private:
	static void _ReadUserInfo(clsUser& User)
	{

		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate<string>::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate<string>::ReadString();
		cout << "\nEnter Email: ";
		User.Email = clsInputValidate<string>::ReadString();
		
		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate<string>::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate<string>::ReadString();
		
		cout << "\nEnter Permissions: ";
		User.Permissions = _ReadPermissionsToSet();
	}

	static void _PrintUser(clsUser User)
	{

		cout << "\nUser Card";
		cout << "\n____________";
		cout << "\nFirstName: " << User.FirstName;
		cout << "\nLastName: " << User.LastName;
		cout << "\nEmail: " << User.Email;
		cout << "\nPhone: " << User.Phone;
		cout << "\nPassword: " << User.Password;
		cout << "\nPermissions: " << User.Permissions;
		cout << "\n____________";

	}
	
	static int _ReadPermissionsToSet()
	{

		short Permissions = 0;
		char Answer = 'n';

		cout << "\nDo You Want to Give Full Access (y/n) ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
			return Permissions = clsUser::enPermissions::eAll;
		
			cout << "\nDo You Want to Give Access to \n";
			cout << "List Clients (y/n) ? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
				Permissions += clsUser::enPermissions::pListClients;
			cout << "\nAdd New Client (y/n) ? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
				Permissions += clsUser::enPermissions::pAddNewClient;
			cout << "\nDelete Client (y/n) ? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
				Permissions += clsUser::enPermissions::pDeleteClients;
			cout << "\nUpdate Client (y/n) ? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
				Permissions += clsUser::enPermissions::pUpdateClient;
			cout << "\nFind Client (y/n) ? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
				Permissions += clsUser::enPermissions::pFindClient;
			cout << "\nTransactions (y/n) ? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
				Permissions += clsUser::enPermissions::pTransactions;
			cout << "\nManage Users (y/n) ? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
				Permissions += clsUser::enPermissions::pManageUsers;
			cout << "\nLogin Register (y/n) ? ";
			cin >> Answer;
			if (Answer == 'y' || Answer == 'Y')
				Permissions += clsUser::enPermissions::pLoginRegister;
			return Permissions;
		
	}


public :
	static void ShowAddNewUserScreen()
	{

		_DrawScreenHeader("\t   Add New User Screen");

		string UserName = "";

		cout << "\nPlease enter a UserName : \n";
		UserName = clsInputValidate<string>::ReadString();
		
		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName is already exist please enter another one!";
			UserName = clsInputValidate<string>::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
		
		_ReadUserInfo(NewUser);
		clsUser::enSaveResults SaveResults = NewUser.Save();

		switch (SaveResults)
		{
		case clsUser::enSaveResults::svSuccedded :
			cout << "\nUser Added Successfully :-)";
			_PrintUser(NewUser);
			break;
		case clsUser::enSaveResults::svFaildEmptyObject:
			cout << "\nError User Was not Saved Because the System is Empty :-(";
			break;
		case clsUser::enSaveResults::svFaildUserExists:
			cout << "\nError User Was not Saved Because UserName is Already Exists!\n";
			break;
		}

	}

};

