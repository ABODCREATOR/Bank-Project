#pragma once
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"
#include <chrono>
#include <thread>
class clsLoginScreen : protected clsScreen
{
private:

	static void _ShowSleepScreen(short seconds)
	{
		short i = 0;
		while (i < seconds)
		{
			system("cls");
			_DrawScreenHeader("\t   Login Screen.");
			cout << "\t\t\t\t\tThe System will be start after ";
			cout << seconds - i;
			this_thread::sleep_for(chrono::seconds(1));
			i++;
		}

	}

	static bool _Login()
	{
		bool LoginFaild = false;
		short Trial = 3;
		string UserName = "", PassWord = "";

		do {

			if (LoginFaild)
			{
				Trial--;
				cout << "\n\t\t\t\t\tInvalid UserName/PassWord!\n\n";
				cout << "\n\t\t\t\t\tYou Have " << Trial << " Trial(s) to login\n";
			}
			if (Trial == 0)
			{
				cout << "\n\t\t\t\t\tInvalid UserName/PassWord!\n\n";
				cout << "\n\t\t\t\t\tYou Have " << Trial << " Trial(s) to login";
				cout << "\n\n\t\t\t\t\tYou are Locked after 3 faild trails :-(";
				system("pause>0");
				exit(0);
				return false;
			}
			cout << "\n\t\t\t\t\tEnter UserName? ";
			getline(cin >> ws, UserName);
			cout << "\n\t\t\t\t\tEnter Password? ";
			getline(cin >> ws, PassWord);

			CurrentUser = clsUser::Find(UserName, PassWord);
			LoginFaild = CurrentUser.IsEmpty();
		} while (LoginFaild);
		CurrentUser.ShowLoginRegister();
		_ShowSleepScreen(5);
		clsMainScreen::ShowMainMenu();
		return true;
	}

public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t   Login Screen.");
		_Login();
		return true;
	}
};
