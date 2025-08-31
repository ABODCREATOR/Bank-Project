#pragma once

#include "clsScreen.h"
#include "clsUser.h"
#include "clsDate.h"
class clsLoginRegisterScreen : protected clsScreen
{

private :
	static void _PrintLoginRegisterRecord(clsUser::stLogins LoginRegister)
	{
		cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegister.DateTime;
		cout << "| " << setw(20) << left << LoginRegister.UserName;
		cout << "| " << setw(20) << left << LoginRegister.Password;
		cout << "| " << setw(10) << left << LoginRegister.Permissions;
	}

public :
	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessPermissions(clsUser::enPermissions::pLoginRegister))
			return;
		vector <clsUser::stLogins> vLoginRegisters = clsUser::GetLoginRecordsList();
		

		string Title = "\t   Login Register List Screen";
		string SubTitle = "\t   (" + to_string(vLoginRegisters.size()) + ") Login(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_________________________________________";
		cout << "_______________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_________________________________________";
		cout << "_______________________________________________________\n\n";
		if (vLoginRegisters.size() == 0)
			cout << "\t\t\t\t\tNo Logins Available In The System :-(";
		else
			for (clsUser::stLogins Record : vLoginRegisters)
			{
				_PrintLoginRegisterRecord(Record);
				cout << "\n";
			}
		cout << setw(8) << left << "" << "\n\t_________________________________________";
		cout << "_______________________________________________________\n\n";
	}


};

