#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUser.h"
class clsUpdateClientScreen : protected clsScreen
{

private:
	static void _PrintClient(clsBankClient Client)
	{

		cout << "\nClient Card:";
		cout << "\n_____________________";
		cout << "\nFirstName : " << Client.FirstName;
		cout << "\nLastName	 : " << Client.LastName;
		cout << "\nFullName  : " << Client.FullName();
		cout << "\nEmail     : " << Client.Email;
		cout << "\nPhone	 : " << Client.Phone;
		cout << "\nAcc.Number: " << Client.AccountNumber();
		cout << "\nPassWord  : " << Client.PinCode;
		cout << "\nBalance   : " << Client.AccountBalance;
		cout << "\n_____________________\n";
	}

	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter First Name: ";
		Client.FirstName = clsInputValidate<string>::ReadString();
		cout << "\nEnter Last Name : ";
		Client.LastName = clsInputValidate<string>::ReadString();
		cout << "\nEnter Email: \n";
		Client.Email = clsInputValidate<string>::ReadString();
		cout << "\nEnter Phone: \n";
		Client.Phone = clsInputValidate<string>::ReadString();
		cout << "\nEnter PinCode: \n";
		Client.PinCode = clsInputValidate<string>::ReadString();
		cout << "\nEnter Account Balance: \n";
		Client.AccountBalance = clsInputValidate<float>::ReadNumber();

	}

public:
	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessPermissions(clsUser::pUpdateClient))
			return;
		_DrawScreenHeader("Update Client Screen");
		string AccountNumber = "";

		cout << "\n\t\t\t\t\tPlease enter Client Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n\t\t\t\t\tAccount Number is not found, please enter a valid one!";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);
		cout << "\n\t\t\t\t\tAre you sure you want to update this client y/n ? ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\n\n\t\t\t\t\tUpdate Client Info:";
			cout << "\n\t\t\t\t\t_____________________\n";
			_ReadClientInfo(Client1);
			clsBankClient::enSaveResults SaveResult = Client1.Save();

			switch (SaveResult)
			{

			case clsBankClient::enSaveResults::svSucceeded:
				cout << "\n\t\t\t\t\tAccount Updated Successfully  :-)\n";
				_PrintClient(Client1);
				break;
			case clsBankClient::enSaveResults::svFaildEmptyObject:
				cout << "\nError Account Was not Updated because it's Empty :-(\n";
				break;
			case clsBankClient::enSaveResults::svFaildAccountNumberExists:
				cout << "\nError Account Was not Updated because it's exists :-(\n";
				break;
			}

		}

	}

};

