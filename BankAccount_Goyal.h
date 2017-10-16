// Name: Rushil Goyal
// Final project: Bank and stock account program
// Date of Submission: 12-23-2016

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<iostream>
#include<fstream> 
#include<string>
#include<time.h>

using namespace std;
#include "Account_Bhandare.h"

#ifndef BANKACCOUNT_BHANDARE_H
#define BANKACCOUNT_BHANDARE_H

// Class Bank account derived from base class Account.
class BankAccount : public Account
{
private:
	double depTemp;
	double witTemp;

	ofstream myfile;
	ifstream myReadFile;

	ifstream balfile;
	ofstream writebalfile;

	string line;

public:
	BankAccount();             // consructor
	~BankAccount();            // destructor
	void viewBal();            // view cash balance
	void depCash(double);      // deposit cash
	void witCash(double);      // withdraw cash
	virtual void printHis();   // print history
	virtual double getcbal();  // get cash balance
	virtual void setcbal();    // set cash balance
};

#endif
