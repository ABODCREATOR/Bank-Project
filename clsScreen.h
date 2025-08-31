#pragma once
#include <iostream>
#include "Global.h"
#include "clsUser.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{
protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "\t\t\t\t\t___________________________________________________";
		cout << "\n\n\t\t\t\t\t  " << Title;
		if (SubTitle != "")
		{
			cout << "\n\t\t\t\t\t " << SubTitle;
		}
		cout << "\n\t\t\t\t\t___________________________________________________\n";
		cout << "\n\t\t\t\t\tUser : " << CurrentUser.UserName;
		cout << "\n\t\t\t\t\tDate : " << clsDate::DateToString(clsDate());
		cout << "\n\n";
	}

	static bool CheckAccessPermissions(clsUser::enPermissions Permission)
	{
		if (!CurrentUser.CheckAccessPermission(Permission))
		{
			cout << "\t\t\t\t\t________________________________________";
			cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin :-(\n";
			cout << "\n\t\t\t\t\t________________________________________";
			return false;
		}
		else
			return true;
	}
};

