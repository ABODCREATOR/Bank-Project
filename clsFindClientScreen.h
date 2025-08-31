#pragma once
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUser.h"
class clsFindClientScreen : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\n\t\t\t\t\tEnter First Name: ";
		Client.FirstName = clsInputValidate<string>::ReadString();
		cout << "\n\t\t\t\t\tEnter Last Name : ";
		Client.LastName = clsInputValidate<string>::ReadString();
		cout << "\n\t\t\t\t\tEnter Email: \n";
		Client.Email = clsInputValidate<string>::ReadString();
		cout << "\n\t\t\t\t\tEnter Phone: \n";
		Client.Phone = clsInputValidate<string>::ReadString();
		cout << "\n\t\t\t\t\tEnter PinCode: \n";
		Client.PinCode = clsInputValidate<string>::ReadString();
		cout << "\n\t\t\t\t\tEnter Account Balance: \n";
		Client.AccountBalance = clsInputValidate<float>::ReadNumber();

	}
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n\t\t\t\t\tClient Card:";
		cout << "\n\t\t\t\t\t_____________________";
		cout << "\n\t\t\t\t\tFirstName : " << Client.FirstName;
		cout << "\n\t\t\t\t\tLastName	 : " << Client.LastName;
		cout << "\n\t\t\t\t\tFullName  : " << Client.FullName();
		cout << "\n\t\t\t\t\tEmail     : " << Client.Email;
		cout << "\n\t\t\t\t\tPhone	 : " << Client.Phone;
		cout << "\n\t\t\t\t\tAcc.Number: " << Client.AccountNumber();
		cout << "\n\t\t\t\t\tPassWord  : " << Client.PinCode;
		cout << "\n\t\t\t\t\tBalance   : " << Client.AccountBalance;
		cout << "\n\t\t\t\t\t_____________________\n";
	}

public:

	static void _ShowFindClientScreen() {

		if (!CheckAccessPermissions(clsUser::enPermissions::pFindClient))
			return;

		_DrawScreenHeader("Find Client Screen");
		string AccountNumber = "";
		cout << "\n\t\t\t\t\tPlease Enter Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n\t\t\t\t\tAccount Number is not found, choose another one!";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		

		if (!Client1.IsEmpty())
		{
			cout << "\n\t\t\t\t\tClient Found :-)\n";
		}
		else
			cout << "\n\t\t\t\t\tClient Not Found :-(\n";
		_PrintClient(Client1);
	}
};

