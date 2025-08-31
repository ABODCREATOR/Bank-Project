#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"
class clsTransferScreen : protected clsScreen
{

private:

	static void _PrintClient(clsBankClient Client)
	{

		cout << "\n\t\t\t\t\tClient Card:";
		cout << "\n\t\t\t\t\t_____________________";
		///*cout << "\n\t\t\t\t\tFirstName : " << Client.FirstName
		//cout << "\n\t\t\t\t\tLastName	 : " << Client.LastName;*/

		cout << "\n\t\t\t\t\tFullName  : " << Client.FullName();
		//cout << "\n\t\t\t\t\tEmail     : " << Client.Email;
		//cout << "\n\t\t\t\t\tPhone	 : " << Client.Phone;
		cout << "\n\t\t\t\t\tAcc.Number: " << Client.AccountNumber();
		//cout << "\n\t\t\t\t\tPassWord  : " << Client.PinCode;
		cout << "\n\t\t\t\t\tBalance   : " << Client.AccountBalance;
		cout << "\n\t\t\t\t\t_____________________\n";
	}

	static string _ReadAccountNumberFrom()
	{
		string AccountNumber = "";

		cout << "\n\t\t\t\t\tPlease enter Account Number to Transfer From: ";
		AccountNumber = clsInputValidate<string>::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number [" << AccountNumber << "] isn't Found. Choose Another One ? ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}
		return AccountNumber;
	}

	static float ReadAmount(clsBankClient SourceClient)
	{
		float Amount = 0.f;
		cout << "\nEnter Transfer Amount? ";
		Amount = clsInputValidate<float>::ReadNumber();
		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another One ? ";
			Amount = clsInputValidate<float>::ReadNumber();
		}
		return Amount;
	}


public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t  Transfer Screen.");
		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumberFrom());
		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumberFrom());
		_PrintClient(DestinationClient);

		float Amount = ReadAmount(SourceClient);

		cout << "\nAre you sure you want to perform this action ? (y/n) ? ";
		char Answer = 'n';
		cin >> Answer;
	
		if (tolower(Answer) == 'y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
			{
				cout << "\nTransfer done successfully :-)\n";
			}
			else
				cout << "\nTransfer Failed :-(\n";
		}
		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);
	}
};

