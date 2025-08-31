#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "Global.h"
using namespace std;

class clsBankClient : public clsPerson
{

private :
	enum enMode { EmptyMode = 0 , UpdateMode = 1 , AddNewMode = 2};
	enMode _Mode;

	string _AccountNumber, _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;


	static clsBankClient _ConvertLinetoClientObject(string Line, string Separator = "#//#")
	{
		vector <string> vClientData;
		vClientData = clsString::Split(Line, Separator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2]
			, vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Separator;
		stClientRecord += Client.LastName + Separator;
		stClientRecord += Client.Email + Separator;
		stClientRecord += Client.Phone + Separator;
		stClientRecord += Client.AccountNumber() + Separator;
		stClientRecord += Client.PinCode + Separator;
		stClientRecord += to_string(Client.AccountBalance);
		return stClientRecord;
	}
	struct stTransfer;

	static stTransfer _ConvertTransferLogLineToRecord(string Line, string Separator = "#//#")
	{
		stTransfer TransferRecord;
		vector <string> vString = clsString::Split(Line, Separator);
		TransferRecord.DateTime = vString[0];
		TransferRecord.SourceAccountNumber = vString[1];
		TransferRecord.DestinationAccountNumber = vString[2];
		TransferRecord.Amount = stof(vString[3]);
		TransferRecord.Balance1 = stod(vString[4]);
		TransferRecord.Balance2 = stod(vString[5]);
		TransferRecord.UserName = vString[6];
		return TransferRecord;
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient
		, string UserName, string Separator = "#//#")
	{
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateString() + Separator;
		TransferLogRecord += AccountNumber() + Separator;
		TransferLogRecord += DestinationClient.AccountNumber() + Separator;
		TransferLogRecord += to_string(Amount) + Separator;
		TransferLogRecord += to_string(AccountBalance) + Separator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Separator;
		TransferLogRecord += UserName;
		return TransferLogRecord;
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
	{
		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << stDataLine << "\n";
			MyFile.close();
		}
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{

		fstream MyFile;
		vector <clsBankClient> _vClients;
		MyFile.open("Clients.txt ", ios::in); // ReadMode
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLinetoClientObject(Line);
				_vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _vClients;
	}


	static void _SaveClientDataFromFile(vector <clsBankClient>&_vClients)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out); // Write Mode

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsBankClient &C : _vClients)
			{
				if (C.MarkedForDeleted() == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << "\n";
				}
			}
			MyFile.close();
		}
	}

	 void _Update()
	 {
		vector <clsBankClient> _vClients = _LoadClientsDataFromFile();
		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientDataFromFile(_vClients);
	 } 

	 void _AddDataLineToFile(string DataLine)
	 {
		 fstream MyFile;
		 MyFile.open("Clients.txt", ios::out | ios::app);

		 if (MyFile.is_open())
		 {
			 MyFile << DataLine << "\n";
			 MyFile.close();
		 }

	 }

	 void _AddNew()
	 {

		 _AddDataLineToFile(_ConvertClientObjectToLine(*this));
	 }

public:
	struct stTransfer {
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		double Balance1;
		double Balance2;
		string UserName;
	};
	
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone
		, string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
	
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;
	void Print()
	{
		/* No UI Related in the Object
		cout << "\nClient Card:";
		cout << "\n_____________________";
		cout << "\nFirstName : " << FirstName;
		cout << "\nLastName	 : " << LastName;
		cout << "\nFullName  : " << FullName();
		cout << "\nEmail     : " << Email;
		cout << "\nPhone	 : " << Phone;
		cout << "\nAcc.Number: " << _AccountNumber;
		cout << "\nPassWord  : " << _PinCode;
		cout << "\nBalance   : " << _AccountBalance;
		cout << "\n_____________________\n";
		*/
	}


	static clsBankClient Find(string AccountNumber)
	{
		vector <clsBankClient> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in); // read mode

		if (MyFile.is_open())
		{

			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();

		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector <clsBankClient> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in); // read mode

		if (MyFile.is_open())
		{

			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber
					&& Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();

		}
		return _GetEmptyClientObject();
	}

	enum enSaveResults {
	svFaildAccountNumberExists = 0 , svSucceeded = 1, svFaildEmptyObject = 2
	};

	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::EmptyMode:
			if (IsEmpty())
			return enSaveResults::svFaildEmptyObject;
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;
		case enMode::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber))
				return enSaveResults::svFaildAccountNumberExists;
			else
			_AddNew();
			_Mode = enMode::UpdateMode;
			return enSaveResults::svSucceeded;
		}


	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0.f);
	}

	bool Delete()
	{
		vector <clsBankClient> _vClients;

		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{

			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}

		}

		_SaveClientDataFromFile(_vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector <clsBankClient> GetClientList()
	{
		return _LoadClientsDataFromFile();
	}

	static double CalculateTotalBalances()
	{
		double Sum = 0.00;
		vector <clsBankClient> _vClients = GetClientList();
		for (clsBankClient &C : _vClients)
		{
			Sum += C.AccountBalance;
		}
		return Sum;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}
	
	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
			return false;
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}

	}

	bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName)
	{
		if (Amount > AccountBalance)
			return false;
		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);
		return true;
	}

	static vector <stTransfer> GetTransferLogList()
	{
		vector <stTransfer> vTransfers;
		string Line;
		stTransfer Transfer;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in); //readmode

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				Transfer = _ConvertTransferLogLineToRecord(Line);
				vTransfers.push_back(Transfer);
			}
			MyFile.close();
		}
		return vTransfers;
	}
};

