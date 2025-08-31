#pragma once
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUser.h"
class clsDeleteClientScreen : protected clsScreen
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
public:
	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessPermissions(clsUser::pDeleteClients))
			return;
		_DrawScreenHeader("Delete Client Screen");
		string AccountNumber = "";
		cout << "\n\t\t\t\t\tPlease Enter Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n\t\t\t\t\tAccount Number is not found, choose another one!";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		char Answer = 'n';
		cout << "\nAre You Sure you want to delete this client y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			if (Client1.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(Client1);
			}
			else
				cout << "\nError Client Was not Deleted :-(\n";
		}
	}


};

