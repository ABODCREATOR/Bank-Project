#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{

private:
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

public:
	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\t   Delete User Screen.");

		string UserName = "";
		cout << "\nPlease Enter UserName: ";
		UserName = clsInputValidate<string>::ReadString();
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser With [" << UserName << "] isn't Found Please Enter Another Existing One ? ";
			UserName = clsInputValidate<string>::ReadString();
		}
		clsUser User1 = clsUser::Find(UserName);
		_PrintUser(User1);

		cout << "\nAre You Sure you want to delete this user (y/n) ? ";
		char answer = 'y';
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			if (User1.Delete())
			{
				cout << "\nUser Deleted Successfully :-)\n";
				_PrintUser(User1);
			}
			else
				cout << "\nError User Was not deleted :-(\n";
			
		}
	}

};

