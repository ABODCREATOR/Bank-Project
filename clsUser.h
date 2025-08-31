#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"
#include "clsPerson.h"
#include "clsDate.h"
#include "clsUtil.h"
using namespace std;
class clsUser : public clsPerson
{

private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName, _Password;

	int _Permissions;
	bool MarkedForDelete = false;

	static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#")
	{
		vector <string> _vUsers = clsString::Split(Line, Separator);

		return clsUser(enMode::UpdateMode, _vUsers[0], _vUsers[1], _vUsers[2]
			, _vUsers[3], _vUsers[4], clsUtil::DecryptText(_vUsers[5]), stoi(_vUsers[6]));
	}


	static string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#")
	{
		string UserRecord = "";

		UserRecord = User.FirstName + Separator;
		UserRecord += User.LastName + Separator;
		UserRecord += User.Email + Separator;
		UserRecord += User.Phone + Separator;
		UserRecord += User._UserName + Separator;
		UserRecord += clsUtil::EncryptText(User.Password) + Separator;
		UserRecord += to_string(User._Permissions) + Separator;

		return UserRecord;
	}

	static vector <clsUser> _LoadUserDataFromFile()
	{
		vector <clsUser> vUsers;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			MyFile.close();

		}
		return vUsers;
	}
	struct stLogins;

	static void _SaveUserDataToFile(vector <clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		string Line;
		if (MyFile.is_open())
		{
			for (clsUser &U : vUsers)
			{
				if (U.MarkedForDelete == false)
				{
					Line = _ConvertUserObjectToLine(U);
					MyFile << Line << "\n";
				}

			}
			MyFile.close();
		}

	}


	void _Update()
	{
		vector <clsUser> vUsers = _LoadUserDataFromFile();
		for (clsUser&U : vUsers)
		{
			if (U._UserName == _UserName)
			{
				U = *this;
				break;
			}
		}
		_SaveUserDataToFile(vUsers);

	}


	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	void _AddDataLineToFile(string Line)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << Line << "\n";
			MyFile.close();
		}

	}
	

	static stLogins _ConvertLoginRegisterLineToRecord(string Line, string Separator = "#//#")
	{
		stLogins Logins;
		vector <string> vString = clsString::Split(Line, Separator);

		Logins.DateTime = vString[0];
		Logins.UserName = vString[1];
		Logins.Password = clsUtil::DecryptText(vString[2]);
		Logins.Permissions = stoi(vString[3]);
		return Logins;
	}

	string _PerformLoginRegisterRecord(string Separator = "#//#")
	{
		string LogRegister = "";
		LogRegister += clsDate::GetSystemDateString() + Separator;
		LogRegister += UserName + Separator;
		LogRegister += clsUtil::EncryptText(Password) + Separator;
		LogRegister += to_string(Permissions);
		return LogRegister;
	}


public:

	enum enPermissions {eAll = -1 , pListClients = 1 , pAddNewClient = 2 , pDeleteClients = 4, 
	pUpdateClient = 8, pFindClient = 16 , pTransactions = 32 , pManageUsers = 64
	, pLoginRegister = 128};

	struct stLogins {
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone
		, string UserName, string Password, short Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return MarkedForDelete;
	}

	string GetUserName()
	{
		return _UserName;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	_declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassWord(string PassWord)
	{
		_Password = PassWord;
	}
	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassWord)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	int GetPermission()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermission, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{

			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}


	static clsUser Find(string UserName, string PassWord)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{

			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName
					&& User.Password == PassWord)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}
	
	static bool IsUserExist(string UserName)
	{
		clsUser User1 = clsUser::Find(UserName);
		return (!User1.IsEmpty());
	}


	enum  enSaveResults {svFaildEmptyObject = 0 , svSuccedded = 1 , svFaildUserExists = 2};

	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::EmptyMode:
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
			break;
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSuccedded;
			break;
		case enMode::AddNewMode:
			if (clsUser::IsUserExist(_UserName))
				return enSaveResults::svFaildUserExists;
			else
			{
				_AddNew();
				_Mode = enMode::AddNewMode;
				return enSaveResults::svSuccedded;
			}
			break;
		}

	}

	bool Delete()
	{
		vector <clsUser> vUsers = GetUsersList();

		for (clsUser& U : vUsers)
		{
			if (U.UserName == UserName)
			{
				U.MarkedForDelete= true;
				break;
			}
		}
		_SaveUserDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "","" ,UserName, "", 0);
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUserDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;
		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

	void ShowLoginRegister()
	{
		string stDataLine = _PerformLoginRegisterRecord();
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	static vector <stLogins> GetLoginRecordsList()
	{
		vector <stLogins> vLogins;
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			stLogins Logins;
			

			while (getline(MyFile, Line))
			{
				Logins = _ConvertLoginRegisterLineToRecord(Line);
				vLogins.push_back(Logins);
			}
			MyFile.close();
		}
		return vLogins;
	}

};

