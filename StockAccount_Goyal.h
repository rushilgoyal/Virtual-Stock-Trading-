// Name: Shreyas Bhandare
// Final project: Bank and stock account program
// Date of Submission: 12-13-2015

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma once
#include<iostream>
#include<fstream> 
#include<string>
#include<time.h>
#include<sstream>
#include<utility>
#include<map>
#include "Account_Goyal.h"
#include "StockNode_Goyal.h"

using namespace std;


#ifndef STOCKACCOUNT_GOYAL_H
#define STOCKACCOUNT_GOYAL_H

class StockNode;

class StockAccount : public Account
{
private:
	string stkSymbol;
	int offset;
	int size;
	int randfile;

	int ctr2;

	double portfolioval, valArray2[100];
	string timeArr[100];

	int sharenos;

	double maxamount, minamount;

	ifstream myFile, balancefile, portfile, portvalfile;

	string tempp;
	int sharetempp;

	map<string, double> result1, result2;
	map<string, int> portfolio;
	ifstream myfile, myfile2;
	stringstream ss;
	stringstream sj;
	stringstream sk;

	string line, line2, symb1, date1;
	double price1;

	ofstream writebalancefile, writebankhis, writetoport;

	StockNode *prev = NULL;
	StockNode *headptr;
	StockNode *tailptr;

public:
	StockAccount();              // constructor
	~StockAccount();             // destructor 
	void dispStockPrice();       // display stock price
	void dispPortfolio();        // display current portfolio
	void buyShares(StockNode *); // buying shares
	void sellShares();           // selling shares
	void viewPortGraph();        // view portfolio value variation graph
	virtual void printHis();     // overriding printHis function to print stock history
	bool sortStockList();        // sorting stock list
	void savePortfolio();        // saving portfolio
	void retrievePortfolio();    // retrieve portfolio at the beginning
	virtual double getcbal();    // get cash balance
	virtual void setcbal();      // setting cash balance
	void savePortfolioVal();     // save portfolio value and time.
	void retrievePortVal();      // retrieve portfolio value.
};

#endif
