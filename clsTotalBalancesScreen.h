#pragma once

#include <iostream>
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <iomanip>

class clsTotalBalancesScreen : protected clsScreen
{
private:
	static void PrintClientRecordLine(clsBankClient Client)
	{
		cout << setw(25) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(40) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.AccountBalance;

	}

public:

	static void ShowTotalBalances() {

		vector <clsBankClient> vClients = clsBankClient::GetClientList();
		string Title = "\t Balances List Screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";


		_DrawScreenHeader(Title, SubTitle);

		cout << setw(25) << left << "" << "\n\t\t___________________________";
		cout << "______________________________________________________________\n\n";


		cout << setw(25) << left << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Account Balance";
		cout << setw(25) << left << "" << "\t\t________________________________";
		cout << "____________________________________________________________\n\n";


		double TotalBalances = clsBankClient::CalculateTotalBalances();


		if (vClients.size() == 0)
		{
			cout << "\t\t\t\tNo Clients Available To The System :-(\n";
		}
		else
			for (clsBankClient Client : vClients)
			{
				PrintClientRecordLine(Client);
				cout << "\n";
			}

		cout << setw(25) << left << "" << "\n\t\t___________________________";
		cout << "___________________________________________________________\n\n";

		cout << setw(8) << left << "" << "\t\t\t\t\t\t\t      Total Balances = "
			<< TotalBalances << "\n";
		cout << setw(8) << left << "" << "\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << " )";

	}


};

