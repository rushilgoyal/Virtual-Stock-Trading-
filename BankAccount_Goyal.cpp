// Name: Rushil Goyal
// Final project: Bank and stock account program
// Date of Submission: 12-23-2016

#include<iostream>
#include<iomanip>
#include<time.h>  
#include<fstream>  
#include<string>
#include<stdlib.h>
using namespace std;

#include "BankAccount_Bhandare.h"

//constructor
BankAccount::BankAccount()
{
	setcbal();
	depTemp = 0;
	witTemp = 0;
}

// destructor
BankAccount::~BankAccount()
{
	cout << "\nObject has been deleted!";
}

//function for viewing balance
void BankAccount::viewBal()
{
	setcbal();
	//-----displaying current cash balance-----
	cout << "\nCurrent Balance is : " << getcbal() << "$" << endl;
}

//function for depositing cash
void BankAccount::depCash(double depAmount)
{
	depTemp = depAmount;
	//setcbal();
	CashBal = getcbal();

	CashBal = CashBal + depTemp;
	cout << "\nAmount of $" << depTemp << " is Deposited to the Account\n";

	//generating the current date and time for deposit transaction
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	std::string str(buffer);

	// writing deposit transaction to bank_transaction_history.txt file
	myfile.open("bank_transaction_history.txt", ios::app);
	myfile << endl << left << setw(30) << "Deposit";
	myfile << left << setw(1) << "$";
	myfile << left << setw(15) << depTemp;
	myfile << right << setw(15) << str;
	myfile << right << setw(5) << "$" << CashBal;
	myfile.close();

	// writing to a balance file
	writebalfile.open("balfile.txt", std::ios_base::out);
	writebalfile << CashBal;
	writebalfile.close();

	//setcbal();
}

//function for withdrawing cash
void BankAccount::witCash(double witAmount)
{
	witTemp = witAmount;
	setcbal();
	CashBal = getcbal();

	//------checking if the cash balance is greater than 0 for withdrawal------
	if (CashBal > 0)
	{
		//------if withdrwal amount is greater than cash balance then withdrawal operation should not proceed------
		if (witTemp > CashBal)
		{
			cout << "\nBalance Nor Sufficient! Please Check the Balance and then Withdraw!\n";
			return;
		}

		//------withdrawal operation------
		else
		{
			CashBal = CashBal - witTemp;
			cout << "\nAmount of $" << witTemp << " is withdrwan from the Account\n";

			//generating the current date and time for withdrawal transaction
			time_t rawtime;
			struct tm timeinfo;
			char buffer[80];
			time(&rawtime);
			localtime_s(&timeinfo, &rawtime);
			strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
			std::string str(buffer);

			// writing withdrawal transaction to bank_transaction_history.txt file
			myfile.open("bank_transaction_history.txt", ios::app);
			myfile << endl << left << setw(30) << "Withdrawal";
			myfile << left << setw(1) << "$";
			myfile << left << setw(15) << witTemp;
			myfile << right << setw(15) << str;
			myfile << right << setw(5) << "$" << CashBal;
			myfile.close();

			// writing to a balance file
			writebalfile.open("balfile.txt", std::ios_base::out);
			writebalfile << CashBal;
			writebalfile.close();

			//setcbal();

			return;
		}
	}
	else
	{
		cout << "\nAccount Balance is 0$, can't withdraw Anything now!\n";
	}
}

//function for printing history
void BankAccount::printHis()
{
	myReadFile.open("bank_transaction_history.txt", ios::app);
	cout << endl << left << setw(30) << "Activity";
	cout << left << setw(16) << "Amount";
	cout << left << setw(23) << "Date & Time";
	cout << right << setw(5) << "Balance"<<endl;
	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			while (getline(myReadFile, line))
				cout << line << "\n";
		}
	}
	myReadFile.close();
}

double BankAccount::getcbal()
{
	return CashBal;
}

void BankAccount::setcbal()
{
	streampos length;
	ifstream filestr;
	filestr.open("balfile.txt", ios::binary);     // open your file
	if (filestr.is_open())
	{
		filestr.seekg(0, ios::end);              // put the "cursor" at the end of the file
		length = filestr.tellg();                // find the position of the cursor
		filestr.close();                         // close your file
	}

	if (!length) // if length is not found, create the file and put 10,000 cash balance into it.
	{
		double putbalance = 10000.00;
		ofstream outputfile;
		outputfile.open("balfile.txt", ios_base::out);
		outputfile << putbalance;
		outputfile.close();

		// setting the balance of 10,000
		ifstream readbal("balfile.txt", ios_base::in);
		readbal >> CashBal;
		readbal.close();
	}
	else
	{
		// else setting balance from existing cash balance file.
		ifstream readbalance("balfile.txt", ios_base::in);
		readbalance >> CashBal;
		readbalance.close();
	}
}
