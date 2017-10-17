// Name: Rushil Goyal
// Final project: Bank and stock account program
// Date of Submission: 12-23-2016

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<utility>
#include "Account_Bhandare.h"
#include "BankAccount_Bhandare.h"
#include "StockAccount_Bhandare.h"
#include "StockNode_Bhandare.h"
using namespace std;

int main()
{
	int option1 = 0, option2 = 0, option3 = 0;
	double depAmount = 0, witAmount = 0;
	bool fg = true;

	BankAccount B;
	StockAccount *newp = new StockAccount();
	StockNode *node = NULL;

	cout << "Welcome to the Account Management System!";

	while (option1 != 3)
	{
		// displaying main options.
		cout << "\n1. Stock Portfolio Account"
			<< "\n2. Bank Account"
			<< "\n3. Exit";

		cout << "\nPlease Select Account to Access : ";
		cin >> option1;

		switch (option1)
		{
		case 1:
			// Stock Account Options
			while (option2 != 8)
			{
				cout << "\nStock Portfolio account";
				cout << "\n1. Display the price for a Stock Symbol"
					<< "\n2. Display Current Portfolio"
					<< "\n3. Buy Shares"
					<< "\n4. Sell Shares"
					<< "\n5. View a Graph for the Portfolio Value"
					<< "\n6. View Transaction History"
					<< "\n7. Sort the Stock List"
					<< "\n8. Return to the Previous Menu";
				cout << "\nEnter Your Choice : ";
				cin >> option2;
				switch (option2)
				{
				case 1:
					newp->dispStockPrice();
					break;
				case 2:
					newp->dispPortfolio();
					break;
				case 3:
					node = new StockNode();
					newp->buyShares(node);
					break;
				case 4:
					newp->sellShares();
					break;
				case 5:
					newp->viewPortGraph();
					break;
				case 6:
					newp->printHis();
					break;
				case 7:
					fg = newp->sortStockList();
					if(fg==false)
						cout << "\nList is Empty! Can't Sort!\n";
					else
						cout << "\nStock list sorted!\n";
					break;
				case 8:
					break;
				default:
					cout << "\nEnter Valid Option!";
				}
			}
			option2 = 0;
			break;

		case 2:
			// Bank account options
			while (option3 != 5)
			{
				cout << "\nBank Account";
				cout << "\n1. View Account Balance"
					<< "\n2. Deposit Money"
					<< "\n3. Withdraw Money"
					<< "\n4. Print History"
					<< "\n5. Return to Previous Menu";
				cout << "\nEnter Your Choice : ";
				cin >> option3;
				switch (option3)
				{
				case 1:
					B.viewBal();
					break;
				case 2:
					cout << "\nEnter Amount in $ to be Deposited : ";
					cin >> depAmount;
					B.depCash(depAmount);
					break;
				case 3:
					cout << "\nEnter Amount  int $ to be Withdrawn : ";
					cin >> witAmount;
					B.witCash(witAmount);
					break;
				case 4:
					B.printHis();
					break;
				case 5:
					break;
				default:
					cout << "\nEnter Valid Option!";
				}
			}
			option3 = 0;
			break;
		case 3:
			newp->savePortfolio();    // saving portfolio.
			newp->savePortfolioVal(); // saving portfolio value and time 
		default:
			cout << "\nEnter Valid Option!";
		}
	}
}
