// Name: Rushil Goyal
// Final project: Bank and stock account program
// Date of Submission: 12-23-2016

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libmex.lib" )  
#pragma comment( lib, "libeng.lib" )

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
// end
#include<engine.h>
#include<cmath>
#include<time.h>
#include<iostream>
#include<iomanip>
#include<map>
#include<cstdlib>
#include<time.h>
#include<utility>
#include<sstream>
#include<fstream>  
#include<string>
#include<stdlib.h>
using namespace std;

#include "StockAccount_Bhandare.h"

#include "StockNode_Bhandare.h"



StockAccount::StockAccount()
{
	headptr = NULL;
	valArray2[20] = { 0 };
	ctr2 = 0;
	portfolioval = 0;
	tailptr = NULL;

	setcbal();

	srand((unsigned int)time(NULL));

	// code to copy data from result-1 and result-2 into two maps for better data accessability.
	myfile.open("Results_1.txt");
	myfile2.open("Results_2.txt");
	if (myfile.is_open() && myfile2.is_open())
	{
		while (!myfile.eof() && !myfile2.eof())
		{
			getline(myfile, line);
			ss << line;
			ss >> symb1 >> price1;
			result1.insert(pair<string, double>(symb1, price1));
			ss.str("");
			ss.clear();

			getline(myfile2, line);
			ss << line;
			ss >> symb1 >> price1;
			result2.insert(pair<string, double>(symb1, price1));
			ss.str("");
			ss.clear();
		}
	}
	myfile.close();
	myfile2.close();

	// getting size of previously stored portfolio (doubly linked list)
	myfile.open("size.txt", ios_base::in);
	myfile >> size;
	myfile.close();
	if (size != 0)
		this->retrievePortfolio(); 	// retrieing the previously stored portfolio in a double linked list
	this->retrievePortVal(); // retrieve portflio value in double array for plotting
}

// destructor
StockAccount::~StockAccount()
{
	cout << "\nObject has been deleted!";
}

//display stock price for one file
void StockAccount::dispStockPrice()
{
	bool flag = false;
	
	cout << "\nEnter Stock Symbol : ";
	cin >> stkSymbol;

	randfile = rand() % 2; // generate random numbers for selecting between two text filesS

	//if random no. is 0, then search for stock symbol in result1 map(Results_1.txt file)
	if (randfile == 0)
	{
		// iterating through map
		for (map<string, double>::iterator ii = result1.begin(); ii != result1.end(); ii++)
		{
			// if symbol is found then display its stock price
			if (stkSymbol == (*ii).first)
			{
				cout << left << setw(10) << "Symbol";
				cout << left << setw(10) << "Price/Share" << endl;
				cout << left << setw(10) << (*ii).first;
				cout << left << setw(10) << (*ii).second << endl;
				flag = true;
			}
		}
		if (flag == false)
			cout << "\nSymbol not found!\n";
		return;
	}

	//if random no. is 1, then search for stock symbol in result2 map(Results_2.txt file)
	else if (randfile == 1)
	{
		// iterating through map
		for (map<string, double>::iterator ii = result2.begin(); ii != result2.end(); ii++)
		{
			// if symbol is found then display its stock price
			if (stkSymbol == (*ii).first)
			{
				cout << left << setw(10) << "Symbol";
				cout << left << setw(10) << "Price/Share" << endl;
				cout << left << setw(10) << (*ii).first;
				cout << left << setw(10) << (*ii).second << endl;
				flag = true;
			}
		}
		// if symbol not found then print that.
		if (flag == false)
			cout << "\nSymbol not found!\n";
		return;
	}
}

// display portfolio
void StockAccount::dispPortfolio()
{
	StockNode *cur = headptr;
	setcbal();
	double stockval = 0, CashBal = getcbal();
	
	while (cur != NULL)
	{
		randfile = rand() % 2;
		// if random number is 0 then assign temporary stock price to corresponding symbol in portfolio and calculate temporary value of the node
		if (randfile == 0)
		{
			for (map<string, double>::iterator ii = result1.begin(); ii != result1.end(); ii++)
			{
				// checking whether node symbol is matched
				if (cur->symb == (*ii).first)
				{
					cur->temp_price_per_share = (*ii).second;                // assign current stock price to each symbol in portfolio
					cur->tempval = cur->numshares*cur->temp_price_per_share; // calculate temp node value
				}
			}
		}

		// if random number is 1 then assign temporary stock price to corresponding symbol in portfolio and calculate temporary value of the node
		else if (randfile == 1)
		{
			for (map<string, double>::iterator ii = result2.begin(); ii != result2.end(); ii++)
			{
				// checking whether node symbol is matched
				if (cur->symb == (*ii).first)
				{
					cur->temp_price_per_share = (*ii).second;                // assign current stock price to each symbol in portfolio
					cur->tempval = cur->numshares*cur->temp_price_per_share; // calculate temp node value
				}
			}
		}
		cur = cur->nextptr; // advacne to next node
	}
	this->sortStockList(); // sorting the potfolio before displaying to show dynamic changes according to share values.
	if (size > 0) // checking if size is greater than 0
	{
		cout << endl << left << setw(15) << "Symbol";
		cout << left << setw(15) << "Shares";
		cout << left << setw(15) << "Price/Share($)";
		cout << left << setw(15) << "Total Value($)" << endl;
		cur = headptr;  // dummy node pointer for iterating loop
		while (cur != NULL)
		{
			//prints symbol, no. of share, current price of share, current value.
			cout << left << setw(15) << cur->symb;
			cout << left << setw(15) << cur->numshares;
			cout << left << setw(15) << cur->temp_price_per_share;
			cout << left << setw(15) << cur->tempval << endl;

			stockval = stockval + cur->tempval;
			cur = cur->nextptr; // increment the pointer
		}
		portfolioval = CashBal + stockval;
		cout << "\nCash Balance  : $" << CashBal;
		cout << "\nStock Balance : $" << stockval;
		cout << "\nTotal Portfolio value is : $" << portfolioval << endl; // print total portfolio value

		valArray2[ctr2] = portfolioval; // store portfolio value changes in double type array.
		ctr2++;
	}
	// if size is 0, print that.
	else if (size == 0)
	{
		portfolioval = CashBal;
		cout << "\nYou don't have any shares right now!\n";
	}
}

// buying shares
void StockAccount::buyShares(StockNode *n)
{
	setcbal();
	bool flag2 = true, flag3 = true, flag4 = true, flag5 = true;
	double shareval1, shareval2;
	CashBal = getcbal();
	double total_amount;

	cout << "\nEnter the Ticker Symbol : ";
	cin >> stkSymbol;

	// iterating in any map (result1/result2) to check the symbol is present or not!
	for (map<string, double>::iterator ii = result1.begin(); ii != result1.end(); ii++)
	{
		if (stkSymbol == (*ii).first)
		{
			flag4 = false;
		}
	}

	// if it is not present then show that and return.
	if (flag4 == true)
	{
		cout << "\nSymbol Not found!\n";
		return;
	}

	//else ask for furthur inforamtion.
	cout << "\nEnter Number of shares you want to buy : ";
	cin >> sharenos;
	cout << "\nEnter Maximum Amount you are willing to pay per share : ";
	cin >> maxamount;

	// iterating both the maps and getting corresponding share values for entered symbol.
	for (map<string, double>::iterator ii = result1.begin(); ii != result1.end(); ii++)
	{
		if (stkSymbol == (*ii).first)
		{
			shareval1 = (*ii).second;
		}
	}
	for (map<string, double>::iterator ii = result2.begin(); ii != result2.end(); ii++)
	{
		if (stkSymbol == (*ii).first)
		{
			shareval2 = (*ii).second;
		}
	}

	randfile = rand() % 2;

	// if randfile is 0 then select share price from map-1 (result-1)
	if (randfile == 0)
	{
		//if maximum amount entered is greater than or equal to current share value then proceed furthur.
		if (maxamount >= shareval1)
		{
			total_amount = sharenos * shareval1;
			price1 = shareval1;
		}
		//otherwise display share value is more, can't proceed with buying.
		else
		{
			cout << "\nMaximum Value entered is less than current Share value! Can't buy stock right now at this value!\n";
			return;
		}
	}

	// if randfile is 0 then select share price from map-2 (result-2)
	else if (randfile == 1)
	{
		//if maximum amount entered is greater than or equal to current share value then proceed furthur.
		if (maxamount >= shareval2)
		{
			total_amount = sharenos * shareval2;
			price1 = shareval2;
		}
		//otherwise display share value is more, can't proceed with buying.
		else
		{
			cout << "\nMaximum Value entered is less than current Share value! Can't buy stock right now at this value!\n";
			return;
		}
	}

	// if total amount is greater than current cash balance display can't buy and return.
	if (total_amount > CashBal)
	{
		cout << "\nTotal Amount Exceeds avaible Cash Balance!\n";
		return;
	}

	// else deduct amount from the cash balance.
	else
	{
		CashBal = CashBal - total_amount;

		cout << "\nYou have purchased " << sharenos << " shares of " << stkSymbol << " for a total of $" << total_amount;

		// writing to a balance file.
		writebalancefile.open("balfile.txt", std::ios_base::out);
		writebalancefile << CashBal;
		writebalancefile.close();

		//generating the current date and time for updating withdrawing from bank transaction
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);
		strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
		std::string str(buffer);

		// writing deposit transaction to bank_transaction_history.txt file
		writebankhis.open("bank_transaction_history.txt", ios::app);
		writebankhis << endl << left << setw(30) << "Debited to Stock Acct.";
		writebankhis << left << setw(1) << "$";
		writebankhis << left << setw(15) << total_amount;
		writebankhis << right << setw(15) << str;
		writebankhis << right << setw(5) << "$" << CashBal;
		writebankhis.close();

		// writing event transaction to stock_transaction_history.txt file
		writebankhis.open("stock_transaction_history.txt", ios::app);
		writebankhis << endl << left << setw(7) << "Buy";
		writebankhis << left << setw(14) << stkSymbol;
		writebankhis << left << setw(7) << sharenos;
		writebankhis << left << setw(14) << price1;
		writebankhis << left << setw(10) << total_amount;
		writebankhis << left << setw(15) << str;
		writebankhis.close();

		//-------updating doubly linked list--------

		// if you are inserting first node, then proceed with following code.
		if (tailptr == NULL&&headptr == NULL)
		{
			//if you are adding first node, then head and tail should point to the same node
			tailptr = n;
			headptr = n;
			n->symb = stkSymbol;
			n->numshares = sharenos;
			n->price_per_share = price1;
		}

		// else you are updating current node or adding node at the end.
		else
		{
			StockNode *cur = headptr;
			while (cur != NULL)
			{
				// if shares of same symbol are present then don't add node just update existing node shares.
				if (stkSymbol == cur->symb)
				{
					cur->numshares = cur->numshares + sharenos;
					return;
				}
				cur = cur->nextptr;
			}

			// adding new node at the end with new symbol and new no. of shares.
			StockNode *copy = tailptr;
			tailptr->nextptr = n;
			tailptr = n;
			tailptr->prevptr = copy;
			n->symb = stkSymbol;
			n->numshares = sharenos;
			n->price_per_share = price1;

		}
		size++; // increasing size of list with each iteration
	}
}

// selling the shares
void StockAccount::sellShares()
{
	bool flag3 = false, flag4 = true, flagsym = false;
	setcbal();
	CashBal = getcbal();

	cout << "\nEnter the Symbol of a company that you want to sell shares : ";
	cin >> stkSymbol;

	StockNode *curtemp = headptr;

	// checking if the symbol entered is present in your portfolio by iterating from start to end of the linked list
	while (curtemp != NULL)
	{
		if (stkSymbol == curtemp->symb)
		{
			flagsym = true;
		}
		curtemp = curtemp->nextptr;
	}

	// if not present then display that and return.
	if (flagsym == false)
	{
		cout << "\nSymbol not found in your portfolio!\n";
		return;
	}
	
	// else perfor furthur operations.
	cout << "\nEnter the no. of share you want to sell : ";
	cin >> sharenos;

	cout << "\nEnter Minimum Amount you are willing to pay for each share : ";
	cin >> minamount;

	randfile = rand() % 2;

	if (size > 0) // checking if size is greater than 0
	{
		StockNode *cur = headptr;  // dummy node pointer for iterating loop

		while (cur != NULL)
		{
			if (stkSymbol == cur->symb && sharenos <= cur->numshares)
			{
				flag3 = true;
				cur->numshares = cur->numshares - sharenos;

				//finding the current value of share to sell 
				if (randfile == 0)
				{
					//get price1 from result1 
					for (map<string, double>::iterator ii = result1.begin(); ii != result1.end(); ii++)
					{
						// stock symbol is found.
						if (stkSymbol == (*ii).first)
						{
							// if min. price entered is greater than current share value then print can't sell and return.
							if (minamount > ((*ii).second))
							{
								cout << "\nMinimum Value entered is greater than current Share value! Can't sell shares right now at this value!\n";
								return;
							}	
							price1 = (*ii).second; // if found then sell shares at this price.
						}
					}
				}
				else if (randfile == 1)
				{
					//get price1 from result2
					for (map<string, double>::iterator ii = result2.begin(); ii != result2.end(); ii++)
					{
						// if min. price entered is greater than current share value then print can't sell and return.
						if (stkSymbol == (*ii).first)
						{
							// if min. price entered is greater than current share value then print can't sell and return.
							if (minamount > ((*ii).second))
							{
								cout << "\nMinimum Value entered is greater than current Share value! Can't sell shares right now at this value!\n";
								return;
							}
							price1 = (*ii).second; // if found then sell shares at this price.
						}
					}
				}

				//updating balance after selling the shares.
				CashBal = CashBal + (sharenos*price1);

				// print the statement for share sell.
				cout << "\nYou have sold " << sharenos << " shares of " << stkSymbol << " at rate " << price1 << " per share\n";

				//generating the current date and time for updating withdrawing from bank transaction
				time_t rawtime;
				struct tm timeinfo;
				char buffer[80];
				time(&rawtime);
				localtime_s(&timeinfo, &rawtime);
				strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
				std::string str(buffer);

				// writing deposit transaction to bank_transaction_history.txt file
				writebankhis.open("bank_transaction_history.txt", ios::app);
				writebankhis << endl << left << setw(30) << "Credited from Stock Acct.";
				writebankhis << left << setw(1) << "$";
				writebankhis << left << setw(15) << sharenos*price1;
				writebankhis << right << setw(15) << str;
				writebankhis << right << setw(5) << "$" << CashBal;
				writebankhis.close();

				// writing event transaction to stock_transaction_history.txt file
				writebankhis.open("stock_transaction_history.txt", ios::app);
				writebankhis << endl << left << setw(7) << "Sell";
				writebankhis << left << setw(14) << stkSymbol;
				writebankhis << left << setw(7) << sharenos;
				writebankhis << left << setw(14) << price1;
				writebankhis << left << setw(10) << sharenos*price1;
				writebankhis << left << setw(15) << str;
				writebankhis.close();

				//updating current balance in the balfile
				writebalancefile.open("balfile.txt", std::ios_base::out);
				writebalancefile << CashBal;
				writebalancefile.close();

				//if no. of shares of particular symbol are zero then delete the node.
				if (cur->numshares == 0)
				{
					//if current node is head
					if (cur == headptr)
					{
						if (cur == tailptr)
						{
							headptr = NULL;
							tailptr = NULL;
							delete cur;
							size--;
							return;
						}
						StockNode *temp = cur->nextptr;
						headptr = cur->nextptr;
						temp->prevptr = NULL;
						delete cur; // delete the node.
						size--;     // reduce the size.
						return;
					}
					//if current node is tail
					else if (cur == tailptr)
					{
						if (cur == headptr)
						{
							headptr = NULL;
							tailptr = NULL;
							delete cur;
							size--;
							return;
						}
						StockNode *temp2 = cur->prevptr;
						tailptr = cur->prevptr;
						temp2->nextptr = NULL;
						delete cur;    // delete the node
						size--;        // reduce the size.
						return;
					}
					//else is the current node is middle node
					else
					{
						StockNode *temp3 = cur->prevptr;
						StockNode *temp4 = cur->nextptr;
						temp3->nextptr = cur->nextptr;  // prev node's next pointer should be current node's next pointer.
						temp4->prevptr = cur->prevptr;  // current node's next node prev pointer should be current node's prev. pointer
						delete cur;                     // delete current node.
						size--;                         // reduce the size.
						return;
					}
				}
				return;
			}
			cur = cur->nextptr; // increment the pointer
		}
	}
	if (flag3 == false)
		cout << "\nEnter Number of shares within range of your portfolio!\n"; // if  entered no. of shares are greater than current shares.
}

// view portfolio value graph on matlab as well shows the variation in tabular form on console.
void StockAccount::viewPortGraph()
{
	// creating a pointer to the engine
	Engine *ep;
	ep = engOpen(NULL);

	// if matlab engine is not opened show error.
	if (ep == NULL)
	{
		cout << "Error: Not Found." << endl;
		exit(1);
	}
	// end
	
	cout << "Potfolio Value" << setw(15) << "Date & Time" <<endl;
	for (int i = 0;i < ctr2;i++)
	{
		cout << valArray2[i] << setw(30) << timeArr[i] << endl;
	}

	// create mxArray and copy your c++ double array of portfolio value into it.
	mxArray *A;
	A = mxCreateDoubleMatrix(1, ctr2, mxREAL);
	memcpy((void *)mxGetPr(A), (void *)valArray2,ctr2*sizeof(double));
	engPutVariable(ep, "yy", A);
	
	// plotting function.
	engEvalString(ep, "plot(yy);");

	// setting up the title for graph
	engEvalString(ep, "title('Portfolio Value Variation graph');");

	mxDestroyArray(A); // destroy mxArray A
}

// printing history
void StockAccount::printHis()
{
	cout << endl << left << setw(7) << "Event";
	cout << left << setw(14) << "CompanySym";
	cout << left << setw(7) << "Shares";
	cout << left << setw(14) <<"Price/Share($)";
	cout << left << setw(10) << "Value($)";
	cout << left << setw(15) << "Date & Time"<<endl;

	myFile.open("stock_transaction_history.txt", ios::app); // open history file
	// if the file is open, read the file line by line till the end.
	if (myFile.is_open())
	{
		while (!myFile.eof())
		{
			while (getline(myFile, line2))
				cout << line2 << "\n";
		}
	}
	myFile.close();  // close the file
}

//sorting the list
bool StockAccount::sortStockList()
{
	StockNode *cur = headptr;
	int counter = 0;

	//getting random price of a share before sorting;
	while (cur != NULL)
	{
		randfile = rand() % 2;
		if (randfile == 0)
		{
			for (map<string, double>::iterator ii = result1.begin(); ii != result1.end(); ii++) // map iterater
			{
				if (cur->symb == (*ii).first)
				{
					cur->temp_price_per_share = (*ii).second;
					cur->tempval = cur->numshares*cur->temp_price_per_share; // temp node value for sorting
				}
			}
		}
		else if (randfile == 1)
		{
			for (map<string, double>::iterator ii = result2.begin(); ii != result2.end(); ii++) // map iterater
			{
				if (cur->symb == (*ii).first)
				{
					cur->temp_price_per_share = (*ii).second;
					cur->tempval = cur->numshares*cur->temp_price_per_share; // temp node value for sorting
				}
			}
		}
		cur = cur->nextptr; // increment the node
	}
		
	StockNode *current = headptr;

	if (headptr != NULL) // checking if list not empty.
	{
		StockNode* prev = 0;
		StockNode *tempPtr = NULL;
		int swapFlag = 0;

		// outer bubble sort loop iteration.
		for (int i = 0; i < size; i++)
		{
			// inner bubble sort loop iteration.
			while (current->nextptr != 0) // checking if it is not a tail pointer
			{
				tempPtr = current->nextptr;
				if (current->tempval < tempPtr->tempval)
				{
					tempPtr->prevptr = current->prevptr;
					current->prevptr = tempPtr;
					swapFlag = 1;
					current->nextptr = tempPtr->nextptr; 
					if (current->nextptr != NULL) // checking for tail pointer
						current->nextptr->prevptr = current;
					tempPtr->nextptr = current;   // after swapping temptr's next pointer should be current.
					if (prev != 0)				  // if previous pointer to the current is not NULL
						prev->nextptr = tempPtr;  // then previous's next pointer should be temptr after swapping.
					prev = tempPtr;               // and for next iteration previous should be temptr.
					if (headptr == current)       // if headptr is current, then after swapping, headptr should be temptr.
						headptr = tempPtr;
					if (current->nextptr == 0)    // if current's next pointer is tailpointer then after swapping, tailpointer should be current.
						tailptr = current;
				}
				else
				{
					prev = current;               // if no swapping, then for next iteration, previous pointer should be current.
					current = current->nextptr;   // increment the node.
				}
			}
			if (swapFlag == 0) // if no swapping in one iteration, then list is sorted! and break out of the loop.
				break;
			else               // else, start the next iteration from the head pointer.
			{
				prev = 0;          
				current = headptr; 
				swapFlag = 0;     
			}
		}
	}
	else // list is empty
	{
		return false;
		//cout << "\nList is Empty! Can't Sort!\n";
	}
	return true;
}

// saing portfolio (only symbols and corresponding no. of shares) in separate text file
void StockAccount::savePortfolio()
{
	StockNode *itr = headptr;
	writetoport.open("portfolio.txt", std::ios_base::out);
	// iterate thorugh the program and save compnay symbol and no. of shares 
	while (itr != NULL)
	{
		writetoport << itr->symb << "\t" << itr->numshares << "\n";
		itr = itr->nextptr;
	}
	writetoport.close();

	// save size of the doubly linked list.
	writetoport.open("size.txt");
	writetoport << size;
	writetoport.close();
}

// retrieving portfolio in a doubly linked list at the start of program.s
void StockAccount::retrievePortfolio()
{
	// open the portfolio text file and save everything in that text file into the STL map with key=Symbol and value=Price/share
	portfile.open("portfolio.txt", ios_base::in);
	if (portfile.is_open())
	{
		while (!portfile.eof())
		{
			getline(portfile, line);
			sj << line;             // getting line into the stringstream object 
			sj >> tempp >> sharetempp;  // dividing stringstream object into string and double value 
			portfolio.insert(pair<string, int>(tempp, sharetempp)); // inserting it into map pairwise
			sj.clear();
		}
	}
	portfile.close();

	// iterating into map and creating double linked list.
	for (map<string, int>::iterator ii = portfolio.begin(); ii != portfolio.end(); ++ii)
	{
		StockNode *current = new StockNode();
		current->symb = (*ii).first;
		current->numshares = (*ii).second;

		// if entering first node
		if (prev == NULL)
		{
			current->prevptr = NULL;
			current->nextptr = NULL;
			headptr = current;
			tailptr = current;
		}

		// enter the node at the end.
		else
		{
			current->prevptr = prev;
			prev->nextptr = current;
		}

		prev = current;
		tailptr = prev;
	}
	StockNode *cur = headptr;

	while (cur != NULL)
	{
		randfile = rand() % 2;
		// if random number is 0 then assign temporary stock price to corresponding symbol in portfolio and calculate temporary value of the node
		if (randfile == 0)
		{
			for (map<string, double>::iterator ii = result1.begin(); ii != result1.end(); ii++)
			{
				// checking whether node symbol is matched
				if (cur->symb == (*ii).first)
				{
					cur->temp_price_per_share = (*ii).second;                // assign current stock price to each symbol in portfolio
					cur->tempval = cur->numshares*cur->temp_price_per_share; // calculate temp node value
				}
			}
		}
		// if random number is 1 then assign temporary stock price to corresponding symbol in portfolio and calculate temporary value of the node
		else if (randfile == 1)
		{
			for (map<string, double>::iterator ii = result2.begin(); ii != result2.end(); ii++)
			{
				// checking whether node symbol is matched
				if (cur->symb == (*ii).first)
				{
					cur->temp_price_per_share = (*ii).second;                // assign current stock price to each symbol in portfolio
					cur->tempval = cur->numshares*cur->temp_price_per_share; // calculate temp node value
				}
			}
		}
		portfolioval = portfolioval + cur->tempval;
		cur = cur->nextptr; // advance to next node
	}
	portfolioval += CashBal;
	
}

void StockAccount::retrievePortVal()
{
	string line2, temp;
	//open portfolioValue text file and get the historical data from it and save it in two arrays.
	portvalfile.open("portfolioValue.txt", ios_base::in);
	if (portvalfile.is_open())
	{
		while (!portvalfile.eof())
		{
			getline(portvalfile, line2); 
			sk << line2;
			sk >> valArray2[ctr2] >> timeArr[ctr2] >> temp; // storing porfolio values in valArray2.
			if (timeArr[ctr2] == "") // retrieve corresponding date in timeArr
				continue;
			else
			{
				timeArr[ctr2].append(" ");
				timeArr[ctr2].append(temp); // append time to it.
			}
			ctr2++; // increment counter for both arrays.
			sk.clear();
		}
	}
	portvalfile.close();
}


// get cash balance
double StockAccount::getcbal()
{
	return CashBal;
}

// set cash balance
void StockAccount::setcbal()
{
	streampos length;
	ifstream filestr;
	filestr.open("balfile.txt", ios::binary);    // open your file
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

		//cout << "HI" << endl;

		// setting the balance of 10,000
		ifstream readbal("balfile.txt", ios_base::in);
		readbal >> CashBal;
		readbal.close();
	}
	else
	{
		// else setting balance from existing cash balance file.
		ifstream readbalance("balfile.txt",ios_base::in);
		readbalance >> CashBal;
		readbalance.close();
	}
}

// save portfolio value and time.
void StockAccount::savePortfolioVal()
{
	//generating the current date and time for updating withdrawing from bank transaction
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", &timeinfo);
	std::string str(buffer);

	if (size == 0)
		portfolioval = CashBal; // if at the time of exiting the program, size portfolio is empty, then store portfolio value as CashBal.
	writetoport.open("portfolioValue.txt.", ios::app);
	writetoport << portfolioval << "  " << str << endl;
	writetoport.close();
}
