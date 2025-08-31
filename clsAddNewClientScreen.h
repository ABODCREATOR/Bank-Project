#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include <iomanip>
class clsAddNewClientScreen : protected clsScreen
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
	static void _PrintClientInfo(clsBankClient Client)
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
	static void ShowAddNewClientScreen() {

		if (!CheckAccessPermissions(clsUser::enPermissions::pAddNewClient))
			return;
		_DrawScreenHeader("Add New Clients Screen ");
		string AccountNumber = "";
		cout << "\n\t\t\t\t\tPlease Enter Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();
		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n\t\t\t\t\tAccount Number Is Already Used, Choose Another One !\n";
			AccountNumber = clsInputValidate<string>::ReadString();

		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);
		clsBankClient::enSaveResults SaveResult = NewClient.Save();

		switch (SaveResult)
		{

		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\n\t\t\t\t\tAccount Added Successfully  :-)\n";
			_PrintClientInfo(NewClient);
			break;
		case clsBankClient::enSaveResults::svFaildEmptyObject:
			cout << "\n\t\t\t\t\tError Account Was not saved because it's Empty :-(\n";
			break;
		case clsBankClient::enSaveResults::svFaildAccountNumberExists:
			cout << "\n\t\t\t\t\tError Account Was not saved because it's exists :-(\n";
			break;
		}

	}

};

