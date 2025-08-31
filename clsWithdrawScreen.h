#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsWithdrawScreen : protected clsScreen
{
private:
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

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";

		cout << "\n\t\t\t\t\tPlease enter Account Number ? ";
		cin >> AccountNumber;
		return AccountNumber;
	}

public:
	static void ShowWithdrawScreen()
	{

		_DrawScreenHeader("\t  Withdraw Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n\t\t\t\t\tClient With [" << AccountNumber << "] does not exist :-(\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		_PrintClient(Client1);


		double Amount = 0.00;

		cout << "\n\t\t\t\t\tPlease Enter Withdraw Amount ? ";
		Amount = clsInputValidate<double>::ReadNumber();

		cout << "\n\t\t\t\t\tAre you sure you want to perform this transaction ? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			while (Amount > Client1.AccountBalance)
			{
				cout << "\n\t\t\t\t\tAmount Exceeds The Client Balance Please enter a Valid Withdraw ? ";
				Amount = clsInputValidate<double>::ReadNumber();
			}
			Client1.Withdraw(Amount);
			cout << "\n\t\t\t\t\tAmount Withdrawed Successfully.\n";
			cout << "\n\t\t\t\t\tNew Balance is : " << Client1.AccountBalance;
		}
		else
		{
			cout << "\n\t\t\t\t\tOperation Was Cancelled.\n";
		}



	}


};

