#pragma once
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsPerson.h"
class clsFindUserScreen : protected clsScreen
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
	static void ShowFindUserScreen() {
		_DrawScreenHeader("\t  Find User Screen.");
		
		string UserName = "";

		cout << "\nPlease Enter UserName: ";
		UserName = clsInputValidate<string>::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Name With [" << UserName << "] isn't Found Please Enter a Valid One !";
			UserName = clsInputValidate<string>::ReadString();
		}

		clsUser User1 = clsUser::Find(UserName);

		if (!User1.IsEmpty())
		{
			cout << "\nUser Found :-)\n";
		}
		else
			cout << "\nUser Not Found :-(\n";
		_PrintUser(User1);
	}

};

