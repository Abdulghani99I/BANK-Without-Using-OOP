#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const string ClientsFileName = "D:\\FileCPP\\Pjt5BankProject\\Debug\\Clients.txt";
const string UsersFileName = "D:\\FileCPP\\Pjt5BankProject\\Debug\\InfoLogin.txt";


enum enMainMenueOptions 
{
	eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3, eUppdateClientInfo = 4,
	eFindClient = 5, eShowTransactionsMenue = 6, eShowManageMenue = 7, eSingOut = 8
};

enum enMainMenueTransaction
{
	eDposit = 1, eWithdraw = 2, eShowTotalBlances = 3, eShowMainMenue = 4
};

enum enMainMenueManager
{
	eUserstsList = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eExitToMainMenue = 6
};

enum enMainMenuePermissions
{
	pAll = -1, pShowClientList = 1, pAddNewClient = 2, pDeleteClient = 4,
	pUpdateClient = 8, pFindClient = 16, pShowTransactionsMenue = 32, pShowManageMenue = 64 
};

enum enMainMenueATM
{
	eQuickWithdraw = 1, eNormalWithDraw = 2, eDepositATM = 3, eCheckBalance = 4, eUpdateAccountNumberAndPin = 5 ,eLogout = 6
};

void GoBackToMainMenue();
void PerformMainMenueOption(enMainMenueOptions MainMenueOptions);
void ShowTransactionsMineMinue();
void ShowManageMineMinue();
int ReadPermissionsToSet();
void BankLogin();
void ATMLogin();
void ShowATMMainMenue();
void ShowScreenQuickWithdraw();
void ShowScreenNormalWithdraw();


struct sClients
{
	string AccountNumber;
	string PinCode;
	string ClientName;
	string Phone;
	double AccountBalance;
	bool MarkClientDelete = false;
};

struct sUsers
{
	std::string Username = "";
	std::string Password = "";
	int Permissons = 0;
	bool MarkForDelete = false;
};

sUsers CurrentUser;
sClients CurrentClietn;

short ReadNumberShort(string Message = "Invalid Number, Enter a valid one:")
{
	short Number = 0;

	cout << Message; 
	cin >> Number;

	

	while (cin.fail())
	{ 
		// user didn't input a number   
		cin.clear();      
		
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << Message; 
		cin >> Number;
	} 
	
	return Number;
}

int ReadNumberInt(string Message = "Invalid Number, Enter a valid one:")
{
	int Number = 0;
	cout << Message; 
	cin >> Number;
	
	while (cin.fail())
	{ // user didn't input a number   
		cin.clear();      
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << Message; 
		cin >> Number;
	} 
	
	return Number;
}

double ReadNumberDouble(string Message = "Invalid Number, Enter a valid one:")
{
	double Number = 0;
	cout << Message; 
	cin >> Number;
	
	while (cin.fail())
	{ // user didn't input a number   
		cin.clear();      
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << Message; 
		cin >> Number;
	} 
	
	return Number;
}

double ReadPositiveNumber(string Message = "")
{
	double NumPositive = 0;

	do
	{
		NumPositive = ReadNumberDouble(Message);

	} while (NumPositive < 0.01);

	return NumPositive;
}

sClients ReadNewClient()
{
	sClients Client;

	cout << "Enter Account Number: ";
	getline(cin >> ws, Client.AccountNumber);

	cout << "Enter PinCode: ";
	getline(cin, Client.PinCode);

	cout << "Enter Name: ";
	getline(cin, Client.ClientName);

	cout << "Enter Phone: ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance: ";
	cin >> Client.AccountBalance;

	return Client;
}

string ReadString(string Message = "")
{
	string Tixt = "";

	cout << Message;
	getline(cin >> ws, Tixt);

	return Tixt;
}

char ReadChar(string Message = "")
{
	char CH1 = ' ';

	cout << Message;
	cin >> CH1;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return CH1;
}

string ReadClientAccountNumber(string Message = "please enter AccountNumber ? ")
{
	string S = "";

	cout << Message;
	cin >> S;

	return S;
}

vector<string> SplitString(string sLine, string Delim = "#//#")
{
	short Pos = 0;
	string sWord = "";
	vector<string> vLine;

	while ((Pos = sLine.find(Delim)) != string::npos)
	{
		sWord = sLine.substr(0, Pos);

		if (sWord != "")
			vLine.push_back(sWord);

		sLine.erase(0, Pos + Delim.length());
	}

	if (sLine != "")
		vLine.push_back(sLine);

	return vLine;
}

string ConvertRecordToLine(sClients Client, string Seperator = "#//#") {
	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.ClientName + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}

string ConvertRecordToLine(sUsers User, string Seperator = "#//#") {
	string stClientRecord = "";

	stClientRecord += User.Username + Seperator;
	stClientRecord += User.Password + Seperator;
	stClientRecord += to_string(User.Permissons);

	return stClientRecord;
}

sClients ConvertLinetoRecord(string sLine)
{
	vector<string> vClient = SplitString(sLine);
	sClients Client;


	Client.AccountNumber = vClient[0];
	Client.PinCode = vClient[1];
	Client.ClientName = vClient[2];
	Client.Phone = vClient[3];
	Client.AccountBalance = stod(vClient[4]);

	return Client;
}


vector<sClients> LoadCleintsDataFromFile(string FileName)
{
	vector<sClients> vClients;
	fstream MyFile;

	MyFile.open(FileName, ios::in); // Read Mode

	string sLine;

	if (MyFile.is_open())
	{

		while (getline(MyFile, sLine))
		{
			vClients.push_back(ConvertLinetoRecord(sLine));
		}

		MyFile.close();
	}

	return vClients;
}

void AddDataLineToFile(string FileName, string stDataLine) 
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClients> vClients, sClients &Client)
{
	for (sClients& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}

	return false;
}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClients& Client)
{
	vector<sClients> vClients = LoadCleintsDataFromFile(ClientsFileName);

	for (sClients& C : vClients)
	{
		if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
		{
			Client = C;
			return true;
		}
	}

	return false;
}

bool FindUserByUsername(string UserName, vector<sUsers> vUsers, sUsers &User)
{
	for (sUsers& U : vUsers)
	{
		if (U.Username == UserName)
		{
			User = U;
			return true;
		}
	}

	return false;
}

sClients ChangeClientRecord(string AccountNumber)
{
	sClients Client;

	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.ClientName);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	Client.AccountBalance = ReadNumberDouble("Enter AccountBalance? ");

	return Client;
}

sUsers ChangeUserRecord()
{
	sUsers User;

	cout << "\nWell, be Updating to:\n\n";

	cout << "Enter Username? ";
	getline(cin >> ws, User.Username);
	
	cout << "Enter password? ";
	getline(cin >> ws, User.Password);

	User.Permissons = ReadPermissionsToSet();

	return User;
}


sUsers ConvertLineUsersToRecord(string sLine)
{
	vector<string> vUsers = SplitString(sLine);
	sUsers User;

	User.Username = vUsers[0];
	User.Password = vUsers[1];
	User.Permissons = stoi(vUsers[2]);

	return User;
}

vector<sUsers> LoadUsersDataFromFile(string FileName)
{
	vector<sUsers> vUsers;

	fstream MyFile;

	MyFile.open(FileName, ios::in); // Read Mode

	string sLine;

	if (MyFile.is_open())
	{

		while (getline(MyFile, sLine))
		{
			vUsers.push_back(ConvertLineUsersToRecord(sLine));
		}

		MyFile.close();
	}

	return vUsers;
}


bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	sClients Client;
	fstream MyFile;

	MyFile.open(FileName, ios::in); // read mode

	if (MyFile.is_open())
	{
		string Line;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);

			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
		}

		MyFile.close();
	}

	return false;
}

bool UserExistsByUsername(string UserName, string FileName)
{
	sUsers User;
	fstream MyFile;

	MyFile.open(FileName, ios::in); // read mode

	if (MyFile.is_open())
	{
		string Line;

		while (getline(MyFile, Line))
		{
			User = ConvertLineUsersToRecord(Line);

			if (User.Username == UserName)
			{
				MyFile.close();
				return true;
			}
		}

		MyFile.close();
	}

	return false;
}

void AddNewClient(vector<sClients> &vClients)
{
	sClients Client;

	//string AccountNumber2 = ReadAccountNumber("Enter Your Account Number? ");
	cout << "Enter Your Account Number ? ";

	cin >> Client.AccountNumber;

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		Client.AccountNumber = ReadString("\nClient with [" + Client.AccountNumber + "] already exists, another Account Number? ");
	}
	
	Client = ChangeClientRecord(Client.AccountNumber);

	vClients.push_back(Client);          // Save Changing to vector (vClient)
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client)); 
}

void AddClients(vector<sClients> &vDataClients)
{
	char AddMore = 'Y';

	do 
	{
		cout << "Adding New Client:\n\n";
		AddNewClient(vDataClients);
		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

void Print(sClients Client)
{
	cout << Client.AccountNumber << endl;
	cout << Client.PinCode << endl;
	cout << Client.ClientName << endl;
	cout << Client.Phone << endl;
	cout << Client.AccountBalance << endl;
}

void PrintInfo(sClients vDataClient)
{
	cout << "|" << left << setw(15) << vDataClient.AccountNumber;
	cout << "|" << left << setw(10) << vDataClient.PinCode;
	cout << "|" << left << setw(30) << vDataClient.ClientName;
	cout << "|" << left << setw(15) << vDataClient.Phone;
	cout << "|" << left << setw(7) << vDataClient.AccountBalance;
}

void PrintAlLClientsData(vector<sClients> vDataClients)
{
	cout << "\t\t\t Clients List " << size(vDataClients) << " Clients(s)\n";
	cout << "___________________________________________________________________________________\n";
	cout << "|" << left << setw(15) << "Account Number";
	cout << "|" << left << setw(10) << "Pin Code";
	cout << "|" << left << setw(30) << "Client Name";
	cout << "|" << left << setw(15) << "Phone";
	cout << "|" << left << setw(7) << "Balance|";
	cout << "\n___________________________________________________________________________________\n";

	for (sClients& Client : vDataClients)
	{
		PrintInfo(Client);
		cout << "|\n___________________________________________________________________________________\n";
	}

}

void PrintDetailsClient(sClients Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "----------------------------------\n";
	cout << "Account Number: " << Client.AccountNumber << endl;
	cout << "Pin Code      : " << Client.PinCode << endl;
	cout << "Name          : " << Client.ClientName << endl;
	cout << "Phone         : " << Client.Phone << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
	cout << "----------------------------------\n";
}

void PrintDetailsUser(sUsers User)
{
	cout << "\nThe following are the User details:\n";
	cout << "----------------------------------\n";
	cout << "Username    : " << User.Username << endl;
	cout << "Password    : " << User.Password << endl;
	cout << "Permissions : " << User.Permissons << endl;
	cout << "----------------------------------\n";
}

enMainMenueOptions ReadMainMenueOption()
{
	short OpetionUser = 0;

	do
	{
		OpetionUser = ReadNumberShort("Choose what do you want to do? [1 to 8]? ");

	} while (1 > OpetionUser || 8 < OpetionUser);

	

	return enMainMenueOptions(OpetionUser);
}

enMainMenueTransaction ReadMainMenueTrasaction()
{
	short OpetionUser = 0;

	do
	{
		OpetionUser = ReadNumberShort("Choose what do you want to do? [1 to 4]? ");

	} while (1 > OpetionUser || 4 < OpetionUser);

	return enMainMenueTransaction(OpetionUser);
}

void SaveCleintsDataToFile(string FileName, vector<sClients> vUsers)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (sClients& C : vUsers)
		{
			if (C.MarkClientDelete == false)
			{
				MyFile << ConvertRecordToLine(C) << endl;
			}
		}

		MyFile.close();
	}

}

void SaveUsersDataToFile(string FileName, vector<sUsers> vUsers)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (sUsers& U : vUsers)
		{
			if (U.MarkForDelete == false)
			{
				MyFile << ConvertRecordToLine(U) << endl;
			}
		}

		MyFile.close();
	}

}

void UpdateClientByAccountNumber(string AccountNumber, vector<sClients>& vClients)
{
	sClients Client;
	char Answer;


	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\n\n";
		PrintDetailsClient(Client);

		Answer = ReadChar("\n\nAre you sure you want update this client? y/n ? ");
		
		if (Answer == 'Y' || Answer == 'y')
		{
			for (sClients& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			 
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.";
			return;
		}
	}
	else
		cout << "\n\nClient with Account Number (" << AccountNumber << ") Not Found!";
}

void UpdateUsersByUsername(string Username, vector<sUsers>& vUsers)
{
	sUsers User;
	char Answer;


	if (FindUserByUsername(Username, vUsers, User))
	{
		cout << "\n\n";
		PrintDetailsUser(User);

		Answer = ReadChar("\n\nAre you sure you want update this User? y/n ? ");

		if (Answer == 'Y' || Answer == 'y')
		{
			for (sUsers& U : vUsers)
			{
				if (U.Username == Username)
				{
					U = ChangeUserRecord();
					break;
				}
			}

			SaveUsersDataToFile(UsersFileName, vUsers);
			cout << "\n\nUser Updated Successfully.";
			return;
		}
	}
	else
		cout << "\n\nClient with Account Number (" << Username << ") Not Found!";
}

void MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClients>& vClients)
{
	for (sClients& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkClientDelete = true;
			return;
		}
	}
}

void MarkUserForDeleteByUsername(string Username, vector<sUsers>& vUsers)
{
	for (sUsers& U : vUsers)
	{
		if (U.Username == Username)
		{
			U.MarkForDelete = true;
			return;
		}
	}
}

void DeleteClientByAccountNumber(string AccountNumber, vector<sClients> &vClients)
{
	sClients Client;

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "The following are the client details:\n\n";
		PrintDetailsClient(Client);

		char IsitWillDeleted = ReadChar("\n\n Are you sure you want delete this client? (Y/N) ? ");

		if (toupper(IsitWillDeleted) == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
		}
	}
	else
		cout << "Client with Account Number (" << AccountNumber << ") Not Found!";
}

bool isUserAdmin(sUsers User)
{
	return (User.Username == "Admin" && User.Permissons == -1);
}

void DeleteUserByUsername(string Username, vector<sUsers> &vUsers)
{
	sUsers User;

	if (FindUserByUsername(Username, vUsers, User))
	{
		cout << "The following are the User details:\n\n";
		PrintDetailsUser(User);

		if (isUserAdmin(User))
		{
			cout << "\n\nThis User is Admin so You can't Deleted.";
			return;
		}

		char IsitWillDeleted = ReadChar("\n\n Are you sure you want delete this Users? (Y/N) ? ");

		if (toupper(IsitWillDeleted) == 'Y')
		{
			MarkUserForDeleteByUsername(Username, vUsers);
			SaveUsersDataToFile(UsersFileName, vUsers);
			vUsers = LoadUsersDataFromFile(UsersFileName);
			cout << "\n\nUser Deleted Successfully.";
		}
	}
	else
		cout << "User (" << Username << ") Not Found!";
}

void FindClient(string AccountNumber, vector<sClients> vClients)
{
	sClients Client;


	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nThe following are the client details:\n\n";
		PrintDetailsClient(Client);
	}	
	else
		cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!";
}

void FindUser(string Username, vector<sUsers> vUsers)
{
	sUsers User;


	if (FindUserByUsername(Username, vUsers, User))
	{
		cout << "\nThe following are the User details:\n\n";
		PrintDetailsUser(User);
	}	
	else
		cout << "\nClient with Username (" << Username << ") Not Found!";
}

void ShowAccessDeniedMessage()
{
	cout << "\n------------------------------------\n";
	cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
	cout << "\n------------------------------------\n";
}

bool CheckAccessPermission(enMainMenuePermissions Permission)
{
	if (CurrentUser.Permissons == enMainMenuePermissions::pAll)
	{
		return true;
	}
	if ((Permission & CurrentUser.Permissons) == Permission)
	{
		return true;
	}
	else
		return false;
}

void ShowFindClientScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
		
	}

	cout << "\n--------------------------------\n";
	cout << "\tFind CLient Screen\n";
	cout << "\n--------------------------------\n";

	vector<sClients> vDataClients = LoadCleintsDataFromFile(ClientsFileName);

	FindClient(ReadClientAccountNumber(), vDataClients);
}

void ShowAllClientsScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pShowClientList))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}
	vector<sClients> vDataClients = LoadCleintsDataFromFile(ClientsFileName);

	PrintAlLClientsData(vDataClients);
}

void ShowAddNewClientsScreen()
{

	if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}

	cout << "-------------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "\n-------------------------------------\n";

	vector<sClients> vDataClients = LoadCleintsDataFromFile(ClientsFileName);

	AddClients(vDataClients);
}

void ShowDeleteClientScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}

	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "\n-----------------------------------\n";

	vector<sClients> vDataClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber("\nEnter Account Number which you want delete: ");
	DeleteClientByAccountNumber(AccountNumber, vDataClients);
}

void ShowUpdateClientScreen()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClient))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}

	cout << "\n-----------------------------------------\n";
	cout << "\tUpdate client Info screen\n";
	cout << "\n-----------------------------------------\n";

	vector<sClients> vDataClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vDataClients);

}

void ShowEndProgramScreen()
{
	cout << "\n--------------------------------\n";
	cout << "\tProgram End :-)";
	cout << "\n--------------------------------\n";
}

void ShowMainMenue() 
{
	system("cls");

	cout << "=================================================\n";
	cout << "\t\t Bank Main Menu Screen\n";
	cout << "=================================================\n";
	cout << "\t [1] Show Client List.\n";
	cout << "\t [2] Add New Client.\n";
	cout << "\t [3] Delete Client.\n";
	cout << "\t [4] Update CLient Info.\n";
	cout << "\t [5] Find CLient.\n";
	cout << "\t [6] Transactions.\n";
	cout << "\t [7] Mange User.\n";
	cout << "\t [8] Exit.\n";
	cout << "=================================================\n";

	PerformMainMenueOption(ReadMainMenueOption());
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClients>&vClients)
{
	char Answer = 'n';

	cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
	cin >> Answer;
	//cin.ignore(numeric_limits<streamsize>::min(), '\n');


	if (Answer == 'y' || Answer == 'Y')
	{
		for (sClients& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New blance is: " << C.AccountBalance;

				return true;
			}
		}

	}

	return false;
}

void PrintShortInfoClients(sClients Client)
{
	cout << "|" << left << setw(15) << Client.AccountNumber;
	cout << "|" << left << setw(30) << Client.ClientName;
	cout << "|" << left << setw(7) << Client.AccountBalance;
}

void ShowDepositScreen()
{
	cout << "\n---------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n---------------------------------\n\n";

	sClients Client;

	vector<sClients>vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist\n";
		AccountNumber = ReadClientAccountNumber();
	}
	 
	PrintDetailsClient(Client);

	double Amount = 0;

	Amount = ReadPositiveNumber("Please enter deposit amount? ");

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithdrawScreen()
{
	cout << "\n---------------------------------\n";
	cout << "\tWithdraw Screen\n";
	cout << "---------------------------------\n\n";

	sClients Client;

	vector<sClients>vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintDetailsClient(Client);

	double Amount = 0;

	Amount = ReadPositiveNumber("Please enter withdraw amount? ");

	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance;
		Amount = ReadPositiveNumber("Please enter withdraw amount? ");
		cout << "\nPlease enter withdraw amount? ";
		cin >> Amount;
	}
	
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void ShowTotalBlanceScreen()
{
	double TotalBalances = 0;
	vector<sClients> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\t\t\t Clients List " << size(vClients) << " Clients(s)\n";
	cout << "______________________________________________________________________________\n";
	cout << "|" << left << setw(15) << "Account Number";
	cout << "|" << left << setw(30) << "Client Name";
	cout << "|" << left << setw(7) << "Balance";
	cout << "\n______________________________________________________________________________\n";


	if (vClients.size() == 0)
	{
		cout << "\t\t\t\t No Clients Avalable In the Systme!";
	}
	else
	{
		for (sClients& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
			PrintShortInfoClients(Client);
			cout << "\n";
		}
	}

	cout << "______________________________________________________________________________\n";
	cout << "\n\t\t\t Total Balances = " << TotalBalances;
}

void GoBackToTransactionMenue()
{
	cout << "\n\nPress any key to go back to Transactions Menue...";
	system("pause>0");
	ShowTransactionsMineMinue();
}

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

void GoBackToMangeMenue()
{
	cout << "\n\nPress any key to go back to Manage Menue...";
	system("pause>0");
	ShowManageMineMinue();
}

void GoBackToMenueATM()
{
	cout << "\n\nPress any key to go back to ATM Menue...";
	system("pause>0");
	ShowATMMainMenue();
}

void PerfromTransacctionMenueOption(enMainMenueTransaction TransactionMenueOption)
{
	switch (TransactionMenueOption)
	{
	case enMainMenueTransaction::eDposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionMenue();
		break;
	}
	case enMainMenueTransaction::eWithdraw:
	{
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionMenue();
		break;
	}
	case enMainMenueTransaction::eShowTotalBlances:
	{
		system("cls");
		ShowTotalBlanceScreen();
		GoBackToTransactionMenue();
		break;
	}
	case enMainMenueTransaction::eShowMainMenue:
	{
		ShowATMMainMenue();
	}

	}
}
 
void ShowTransactionsMineMinue()
{
	system("cls");

	if (!CheckAccessPermission(enMainMenuePermissions::pShowTransactionsMenue))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}

	cout << "\n=========================================\n";
	cout << "\tTransaction Menue Screen\n";
	cout << "=========================================\n";	
	cout << "[1] Deposit.\n";
	cout << "[2] Withdraw.\n";
	cout << "[3] Total Balances.\n";
	cout << "[4] Main Menue.\n";
	cout << "=========================================\n";

	PerfromTransacctionMenueOption(ReadMainMenueTrasaction());
}

short ReadNumFromXToY(short From, short To)
{
	short Number = 0;

	cin >> Number;
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (Number < From || Number > To)
	{
		cout << "Your Chosse Eror!\n\n Enter Correct Choice agine";
		cin >> Number;

	}

	return Number;
}

enMainMenueManager ReadManageMenueOption()
{
	short Option = 0;

	do
	{
		Option = ReadNumberShort("Choose what do you want to do? [1 to 6]? ");

	} while (1 > Option || 6 < Option);


	return ((enMainMenueManager)Option);
}

void ShowAllUsers(vector<sUsers> vUsers)
{
	cout << "\n\t\t\t\t Users List (" << size(vUsers) << ") Users(s).\n";
	cout << "_____________________________________________________________________________________________\n";
	cout << left << setw(15)  <<  "| User Name"
		 << left << setw(15)  <<  "| Password"
		 << left << setw(15)  <<  "| Permissions \n";
	cout << "_____________________________________________________________________________________________\n";

	for (sUsers& U : vUsers)
	{
		
		cout << "| " << left << setw(13) << U.Username;
		cout << "| " << left << setw(13) << U.Password;
		cout << "| " << left << setw(13) << U.Permissons;
		cout <<"\n_____________________________________________________________________________________________\n";
	}
}

void ShowScreenListUsers()
{
	vector<sUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
	
	ShowAllUsers(vUsers);	
}

int ReadPermissionsToSet()
{
	int Permissions = 0;
	char Answers = 'n';

	Answers = ReadChar("\nDo You Want to give full access y/n? ");

	if (Answers == 'y' || Answers == 'Y')
	{
		return -1;
	}
	
	cout << "\nDo You want to give access to :\n";

	Answers = ReadChar("\nShow Client List? y/n? ");
	
	if (Answers == 'y' || Answers == 'Y')
	{
		Permissions += enMainMenuePermissions::pShowClientList;
	}
	
	Answers = ReadChar("\nAdd New Client? y/n? ");
	
	if (Answers == 'y' || Answers == 'Y')
	{
		Permissions += enMainMenuePermissions::pAddNewClient;
	}
	
	Answers = ReadChar("\nDelete Client? y/n? ");
	
	if (Answers == 'y' || Answers == 'Y')
	{
		Permissions += enMainMenuePermissions::pDeleteClient;
	}

	Answers = ReadChar("\nUpdate Client? y/n? ");
	
	if (Answers == 'y' || Answers == 'Y')
	{
		Permissions += enMainMenuePermissions::pUpdateClient;
	}

	Answers = ReadChar("\nFind Client? y/n? ");
	
	if (Answers == 'y' || Answers == 'Y')
	{
		Permissions += enMainMenuePermissions::pFindClient;
	}
	
	Answers = ReadChar("\nShow Transaction Menue? y/n? ");
	
	if (Answers == 'y' || Answers == 'Y')
	{
		Permissions += enMainMenuePermissions::pShowTransactionsMenue;
	}

	Answers = ReadChar("\nShow Manage Menue? y/n? ");
	
	if (Answers == 'y' || Answers == 'Y')
	{
		Permissions += enMainMenuePermissions::pShowManageMenue;
	}
	
	return Permissions;
}

sUsers AddNewUser()
{
	sUsers Users;
	char AddMore = 'Y';


	cout << "\n_____________________________________________\n";
	cout << "\t Add New User Screen\n";
	cout << "\n_____________________________________________\n";
	
	Users.Username = ReadString("Enter Username: ");

	while (UserExistsByUsername(Users.Username, UsersFileName))
	{
		Users.Username = ReadString("\nClient with [" + Users.Username + "] already exists, Enter Account Number? ");
	}

	Users.Password = ReadString("Enter Password: ");

	Users.Permissons = ReadPermissionsToSet();
	

	return Users;
}

void ShowScreenAddNewUsers()
{
	sUsers Users;
	char AddmMore = 'n';

	do
	{
		Users = AddNewUser();
	
		AddDataLineToFile(UsersFileName, ConvertRecordToLine(Users));

		AddmMore = ReadChar("\nClient Aded Successfully, do you want to add more Users? Y/N? ");

	} while (toupper(AddmMore) == 'Y');
}

void ShowScreenDeleteUsers()
{
	cout << "\n--------------------------------\n";
	cout << "\tDelete User Screen\n";
	cout << "\n--------------------------------\n";

	vector<sUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
	string Username = ReadString("\nPlease enter Username? ");
	DeleteUserByUsername(Username, vUsers);
}

void ShowScreenUpdateUsers()
{
	cout << "\n-----------------------------------------\n";
	cout << "\tUpdate User Info screen\n";
	cout << "\n-----------------------------------------\n";

	vector<sUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
	string Username = ReadString("\nEnter Username: ");
	UpdateUsersByUsername(Username, vUsers);

}

void ShowScreenFindUsers()
{
	cout << "\n--------------------------------\n";
	cout << "\tFind User Screen\n";
	cout << "\n--------------------------------\n";

	vector<sUsers> vUsers = LoadUsersDataFromFile(UsersFileName);

	string Username = ReadString("Enter Username: ");

	FindUser(Username, vUsers);
}

void PerforfmManageMenueOption(enMainMenueManager MainMenueManager)
{
	switch (MainMenueManager)
	{
	case enMainMenueManager::eUserstsList:
		system("Cls");
		ShowScreenListUsers();
		GoBackToMangeMenue();
		break;
	
	case enMainMenueManager::eAddNewUser:
		system("Cls");
		ShowScreenAddNewUsers();
		GoBackToMangeMenue();
		break;
	
	case enMainMenueManager::eDeleteUser:
		system("Cls");
		ShowScreenDeleteUsers();
		GoBackToMangeMenue();
		break;
	
	case enMainMenueManager::eUpdateUser:
		system("Cls");
		ShowScreenUpdateUsers();
		GoBackToMangeMenue();
		break;
	
	case enMainMenueManager::eFindUser:
		system("Cls");
		ShowScreenFindUsers();
		GoBackToMangeMenue();
		break;
	
	case enMainMenueManager::eExitToMainMenue:
		ShowMainMenue();
	}
}

void ShowManageMineMinue()
{
	system("Cls");

	if (!CheckAccessPermission(enMainMenuePermissions::pShowManageMenue))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();

	}

	cout << "==============================================\n";
	cout << "\t  Manage Users Menue Screen\n";
	cout << "==============================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "==============================================\n";
	
	PerforfmManageMenueOption(ReadManageMenueOption());
	
}

void PerformMainMenueOption(enMainMenueOptions MainMenueOptions)
{	
	switch(MainMenueOptions)
	{
		
		case enMainMenueOptions::eShowClientList:
		{
			system("Cls");
			ShowAllClientsScreen();
			GoBackToMainMenue();
			break;

		}

		case enMainMenueOptions::eAddNewClient:
		{
			system("Cls");
			ShowAddNewClientsScreen();
			GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eDeleteClient:
		{
			system("Cls");
			ShowDeleteClientScreen();
			GoBackToMainMenue();
			break;
		}
		
		case enMainMenueOptions::eUppdateClientInfo:
		{
			system("Cls");
			ShowUpdateClientScreen();
			GoBackToMainMenue();
			break;
		}
	
		case enMainMenueOptions::eFindClient:
		{
			system("Cls");
			ShowFindClientScreen();
			GoBackToMainMenue();
			break;
		}

		case enMainMenueOptions::eShowTransactionsMenue:
		{
			system("Cls");
			ShowTransactionsMineMinue();
			break;
		}
		
		case enMainMenueOptions::eShowManageMenue:
		{
			system("Cls");
			ShowManageMineMinue();
			break;
		}
		
		case enMainMenueOptions::eSingOut:
 		{
			BankLogin();
		}
	}
}

bool IsUserNameAndPsswordValid(sUsers InfoUsers)
{
	vector<sUsers> vUsers = LoadUsersDataFromFile(UsersFileName);


	for (sUsers& U : vUsers)
	{
		if (U.Username == InfoUsers.Username && U.Password == InfoUsers.Password)
		{
			CurrentUser = U;
			return true;
		}
	}

	return false;
};

bool IsAccountNumberAndPincodeValid(string AccountNumber, string PinCode)
{
	if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClietn))
		return true;
	else
		return false;
};

void BankLogin()
{
	sUsers InfoLogin;
	bool LoginFaild = false;

	do
	{
		system("cls");


		cout << "------------------------------\n";
		cout << "\t Back Login Screen\n";
		cout << "------------------------------\n";

		cout << "\nNote: You Can Log by using Username: Admin | Password: Admin\n";
		
		if (LoginFaild)
		{
			cout << "\nVlaid UserName/Password!\n";
		}


		InfoLogin.Username = ReadString("\nEnter Username? ");

		InfoLogin.Password = ReadString("Enter Password? ");
		
		LoginFaild = !IsUserNameAndPsswordValid(InfoLogin);


	} while (LoginFaild);

	ShowMainMenue();
}

enMainMenueATM ReadAtmMainMenueOption()
{
	short NumOption = 0;

	do
	{
		NumOption = ReadNumberShort("Choose what do you want to do? [1 to 6]? ");

	} while (1 > NumOption || 6 < NumOption);

	return (enMainMenueATM)NumOption;
}

short ReadOptionWithDraw()
{
	short Option = 0;

	while (1 > Option || 9 < Option)
	{
		Option = ReadNumberShort("Choose Wat td witdraw from[1] to [9] ? ");
	}

	return Option;
}

short getQuickWithDrawAmount(short QuickWithDrawOption)
{
	short Withdraw[] = { 0, 20, 50, 100, 200, 400, 600, 800, 1000 };
	
	return Withdraw[QuickWithDrawOption];
}

void PerformQucikWithdrawOption(int QuickWithDrawOption)
{
	short WithDrawBalance = getQuickWithDrawAmount(QuickWithDrawOption);



	if (WithDrawBalance > CurrentClietn.AccountBalance)
	{
		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "\n\nPress any key to go back to ATM Menue...";
		system("pause>0");
		ShowScreenQuickWithdraw();
		return;
	}

	vector<sClients> vClietns = LoadCleintsDataFromFile(ClientsFileName);

	DepositBalanceToClientByAccountNumber(CurrentClietn.AccountNumber, WithDrawBalance * -1, vClietns);
	CurrentClietn.AccountBalance -= WithDrawBalance;
}

void ShowScreenQuickWithdraw()
{
	cout << "====================================\n";
	cout << "\t Qucik Withdraw\n";
	cout << "====================================\n";
	cout << "[1] 20         [2] 50\n";
	cout << "[3] 100        [4] 200\n";
	cout << "[5] 400        [6] 600\n";
	cout << "[7] 800        [8] 1000\n";
	cout << "[9] Exit\n";
	cout << "====================================\n";
	cout << "You Balance is " << CurrentClietn.AccountBalance << endl;

	PerformQucikWithdrawOption(ReadOptionWithDraw());
}

int ReadMultipleOf5(string Message = "")
{
	int Amount = 0;

	do
	{
		cout << endl << Message;
		Amount = ReadPositiveNumber("");

	} while (Amount % 5 != 0);

	return Amount;
}

void PerformNormalWithdrawOption()
{
	short WithDrawBalance = ReadMultipleOf5("Enter an amount multiple of 5's ? ");;

	if (WithDrawBalance > CurrentClietn.AccountBalance)
	{
		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "\n\nPress any key to continue...";
		system("pause>0");
		ShowScreenNormalWithdraw();
		return;
	}

	vector<sClients> vClietns = LoadCleintsDataFromFile(ClientsFileName);

	DepositBalanceToClientByAccountNumber(CurrentClietn.AccountNumber, WithDrawBalance * -1, vClietns);
	CurrentClietn.AccountBalance -= WithDrawBalance;
}

void ShowScreenNormalWithdraw()
{
	cout << "===========================================\n";
	cout << "\t Normal Withdraw Screen\n";
	cout << "===========================================\n";
	cout << "\nNote:- [If a decimal number is entered, it is converted to an integer]\n";

	PerformNormalWithdrawOption();
}

void PerfromDepositOption()
{
	int DepositAmount = ReadPositiveNumber("\nEnter a positive Deposit Amount? ");

	vector<sClients> vClietns = LoadCleintsDataFromFile(ClientsFileName);

	DepositBalanceToClientByAccountNumber(CurrentClietn.AccountNumber, DepositAmount, vClietns);
	CurrentClietn.AccountBalance += DepositAmount;
}

void ShowScreenDepositATM()
{
	cout << "===========================================\n";
	cout << "\tDeposit Screen\n";
	cout << "===========================================\n";

	PerfromDepositOption();
}

void ShowScreenBalance()
{
	cout << "===========================================\n";
	cout << "\t Check Balance Screen\n";
	cout << "===========================================\n";
	cout << "\t Your Balance is " << CurrentClietn.AccountBalance;
}

void PrintCurentClientLoginInfo()
{
	cout << "Current Info:-";
	cout << "\n\n---------------------------------------\n";
	cout << "Account Number: " << CurrentClietn.AccountNumber << endl;
	cout << "Pin Code      : " << CurrentClietn.PinCode;
	cout << "\n---------------------------------------\n";

}

void UpdateAccountNumberAndPincodeForCurrentClient(string NewAccountNumber, string NewPincode)
{
	vector<sClients> vClients = LoadCleintsDataFromFile(ClientsFileName);

	for (sClients& C : vClients)
	{
		if (C.AccountNumber == CurrentClietn.AccountNumber && C.PinCode == CurrentClietn.PinCode)
		{
			C.AccountNumber = NewAccountNumber;
			C.PinCode = NewPincode;
			CurrentClietn = C;
			break;
		}
	}

	// Save Apdate Client
	SaveCleintsDataToFile(ClientsFileName, vClients);
}

void ShowScreenUpdateAccountNumberAndPin()
{
	cout << "===========================================\n";
	cout << "\t Update Account Number And Pin\n";
	cout << "===========================================\n";

	string AccountNumber, PinCode;
	char Answer = 'n';

	PrintCurentClientLoginInfo();
	

	Answer = ReadChar("\nAre You sure from Update Account Number? ");

	if (Answer == 'Y' || Answer == 'y')
	{
		
		cout << "Enter Account Number: ";
		cin >> AccountNumber;
		cout << "Enter Pin Code: ";
		cin >> PinCode;

		UpdateAccountNumberAndPincodeForCurrentClient(AccountNumber, PinCode);

		cout << "\nDone Successfully. New Info Client:\n";

		PrintCurentClientLoginInfo();
	}
}

void PerformATMMainMenueOption(enMainMenueATM OptionMenueATM)
{
	switch (OptionMenueATM)
	{
	case enMainMenueATM::eQuickWithdraw:
		system("Cls");
		ShowScreenQuickWithdraw();
		GoBackToMenueATM();
		break;
	
	case enMainMenueATM::eNormalWithDraw:
		system("Cls");
		ShowScreenNormalWithdraw();
		GoBackToMenueATM();
		break;
	
	case enMainMenueATM::eDepositATM:
		system("Cls");
		ShowScreenDepositATM();
		GoBackToMenueATM();
		break;
	
	case enMainMenueATM::eCheckBalance:
		system("Cls");
		ShowScreenBalance();
		GoBackToMenueATM();
		break;
	
	case enMainMenueATM::eUpdateAccountNumberAndPin:
		system("Cls");
		ShowScreenUpdateAccountNumberAndPin();
		GoBackToMenueATM();
		break;
	
	case enMainMenueATM::eLogout:
		ATMLogin();
	}
}

void ShowATMMainMenue()
{
	system("Cls");

	cout << "====================================\n";
	cout << "\t ATM Main Menue\n";
	cout << "====================================\n";
	cout << "[1] Quick Withdraw.\n";
	cout << "[2] Normal Withdraw.\n";
	cout << "[3] Deposit.\n";
	cout << "[4] Check Balance.\n";
	cout << "[5] Update Info Login\n";
	cout << "[6] Logeout.\n";
	cout << "====================================\n";

	PerformATMMainMenueOption(ReadAtmMainMenueOption());

	return;
}

void ATMLogin()
{
	string AccountNumber, PinCode;

	bool LoginFaild = false;

	do
	{
		system("cls");


		cout << "------------------------------\n";
		cout << "\t ATM Login Screen\n";
		cout << "------------------------------\n";

		cout << "\nNote: You Can Using AccountNumber: A120 | Pincode: 1234\n";

		if (LoginFaild)
		{
			cout << "\nVlaid AccountNumber/Pincode!\n";
		}

		AccountNumber = ReadString("\nEnter Account Number? ");

		PinCode = ReadString("Enter Pin? ");

		LoginFaild = !IsAccountNumberAndPincodeValid(AccountNumber, PinCode);


	} while (LoginFaild);

	ShowATMMainMenue();
}

short ReadChooseLogin()
{
	short Option = 0;
	cout << "\nWhat Your Chooice:";
	cin >> Option;

	while (1 > Option || 2 < Option)
	{
		cout << "\nWhat Your Chooice:";
		cin >> Option;
	}

	return Option;
}

void ChooseLogin()
{
	short Option = 0;

	cout << "\n==============================\n";
	cout << "\t ChooseLogin";
	cout << "\n==============================\n";
	cout << "   1- Enter To Bank Login.\n";
	cout << "   2- Enter To ATM Login.\n";

	Option = ReadChooseLogin();

	if (Option == 1) BankLogin();
	if (Option == 2) ATMLogin();
}

int main()
{
	ChooseLogin();

	system("pause>0");
	 
	return 0;
}