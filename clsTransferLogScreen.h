#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
class clsTransferLogScreen : protected clsScreen
{
private :
	static void _PrintTransferLogRecord(clsBankClient::stTransfer Transfer)
	{
		cout << setw(8) << left << "" << "| " << setw(23) << left << Transfer.DateTime;
		cout << "| " << setw(8) << left << Transfer.SourceAccountNumber;
		cout << "| " << setw(8) << left << Transfer.DestinationAccountNumber;
		cout << "| " << setw(8) << left << Transfer.Amount;
		cout << "| " << setw(10) << left << Transfer.Balance1;
		cout << "| " << setw(10) << left << Transfer.Balance2;
		cout << "| " << setw(8) << left << Transfer.UserName;
	}

public:

	static void ShowTransferLogScreen()
	{

		vector <clsBankClient::stTransfer> vTransfers = clsBankClient::GetTransferLogList();

		string Title = "\t   Transfer Log List Screen";
		string SubTitle = "\t   (" + to_string(vTransfers.size()) + ") Transfer(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_________________________________________";
		cout << "__________________________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
		cout << "| " << setw(8) << left << "s.Acct";
		cout << "| " << setw(8) << left << "d.Acct";
		cout << "| " << setw(8) << left << "Amount";
		cout << "| " << setw(10) << left << "s.Balance";
		cout << "| " << setw(10) << left << "d.Balance";
		cout << "| " << setw(8) << left << "User";
		cout << setw(8) << left << "" << "\n\t_________________________________________";
		cout << "__________________________________________________________________\n\n";
		if (vTransfers.size() == 0)
			cout << "\t\t\t\t\tNo Transfers Log Available in the system :-(";
		else
			for (clsBankClient::stTransfer Transfer : vTransfers)
			{
				_PrintTransferLogRecord(Transfer);
				cout << endl;
			}
		cout << setw(8) << left << "" << "\n\t_________________________________________";
		cout << "__________________________________________________________________\n\n";
	}
};

