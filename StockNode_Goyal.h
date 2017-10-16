// Name: Rushil Goyal
// Final project: Bank and stock account program
// Date of Submission: 12-23-2016

#pragma once
#include<iostream>
#include<string>
#include "Account_Bhandare.h"
#include "StockAccount_Bhandare.h"
using namespace std;

#ifndef STOCKNODE_GOYAL_H
#define STOCKNODE_GOYAL_H

class StockNode
{
	friend class StockAccount;

private:
	StockNode *nextptr;
	StockNode *prevptr;

	//Each node contains no. of shares and stock symbol.
	int numshares;
	double price_per_share;      // price per share at the time of buying
	double temp_price_per_share; // temporary price per share at the time of sorting
	double tempval;              // value of a node = numshares*temp_price_per_share(/price_per_share)
	string symb;

public:
	StockNode()
	{
		this->nextptr = NULL;
		this->prevptr = NULL;
	}
};

#endif
