#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
class clsUpdateUserScreen : protected clsScreen
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

public:

	static void ShowUpdateUserScreen()
	{

		_DrawScreenHeader("\t   Update User Screen.");
		string UserName = "";
		cout << "\nPlease Enter UserName: ";
		UserName = clsInputValidate<string>::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Name With [" << UserName << "] isn't Found Please Enter a Valid One !";
			UserName = clsInputValidate<string>::ReadString();
		}
		
		clsUser User1 = clsUser::Find(UserName);

		_PrintUser(User1);

		cout << "\nAre You Sure you want to Update this User (y / n) ? ";
		char Answer = 'n';
		cin >> Answer;
		
		if (tolower(Answer) == 'y')
		{
			cout << "\n\nUpdate User Info:";
			cout << "\n___________________\n";

			_ReadUserInfo(User1);
			clsUser::enSaveResults SaveResult;

			SaveResult = User1.Save();

			switch (SaveResult)
			{

			case clsUser::enSaveResults::svSuccedded:
				cout << "\nUser Updated Successfully :-)\n";
				_PrintUser(User1);
				break;
			case clsUser::enSaveResults::svFaildEmptyObject:
				cout << "\nError User was not save because it's already an empty object :-(";
				break;
			}
		}

	}
};

