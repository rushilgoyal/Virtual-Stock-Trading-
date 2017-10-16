# Virtual-Stock-Trading

The Account Management System Program has a derived class structure.
Account Class is our Abstract Base class from which the other classes are inherited. It has a protected data Current_Cash_Balance. This data field gets updated evertime a transaction is made either in the Bank Account or the Portfolio Account class. 

It has 3 virtual functions which can be overridden based on the functional requirements of inherited class. 
Display_History(), Get_Cash_Balance(), Set_Cash_Balance()

There are two derived classes:

1.	Bank_Account - This class has basically two data members which are private, so they can only be used within the class. 
-	deposit_amount – The money to be deposited in each transaction
-	withdrawl_amount – The money to be withdrawn in each transaction

      It has the following member functions to provide functionality to our Bank Account System 
      -	Deposit_Cash
      -	Display_Cash_Balance
      -	Withdraw_Cash

      The other functions include the functions declared in the base class Account but they have been declared here as virtual       so that they can be called using the Base class pointer as well. 

      The transactional details are updated in a separate file: “Account_Transaction_History.txt”.

      The updated Current_Cash_Balance is written in a separate text file: “Balance_Sheet.txt”
      Since this doesn’t exist initially an initial cash balance of $10000 is put into it. 

2.	Portfolio Account - The other derived class is Portfolio_Account. This class uses a double linked list data structure in order to store the information related to the shares bought in each of the node. 
        Each node consists of following data attributes:
        1.	number_of_shares
        2.	value_per_share
        3.	interim_value_per_share
        4.	interim_absolute_node_value
        5.	symb representing a string data type to match the stock symbol

        In terms of the member function functionality, the constructor basically first transfers the data from the text files         to the map based associative array structure for easier data accessibility. It creates two such maps for both the              given text files – result1 and result2. 
        The constructor also stores the size of the portfolio if there is already an existing one to a text file named                 “Portfolio.txt”. Initially the list of portfolio will be empty. Both the tail and the head pointer will be null                initially for an empty linked list. 
        
The other member functions include the following:
-	Display_Stock_Value – basically iterates through the double linked list and displays value of the stock value of the node input by user. This is done through randomly choosing a number through rand() function and taking the modulus with 2. The result is either 0 or 1. Based on this Results1.txt or Results2.txt file is chosen to get the price per share.

-	Display_Present_Portfolio – Iterates and displays the existing nodes with their attributes, thus representing user’s current portfolio. 

-	Buy_Company_Shares – This function asks the user to enter the stock symbol, number of shares and maxmum amount he is willing to pay to buy the share. The function then writes transactional details to Account_Transaction_History.txt, stock_transaction_history.txt. It also updates the Current_Cash_Balance in the Balance_Sheet.txt. The function also updates the linked list. All the conditionality checks regarding amount and non-matching stocks are also implemented. 

-	Sell_Company_Shares – This function asks the user to enter the stock symbol, number of shares and minimum amount he is willing to sell the share for. The function then again writes transactional details to Account_Transaction_History.txt, stock_transaction_history.txt. It also updates the Current_Cash_Balance in the Balance_Sheet.txt. The function also updates the linked list. While updating the nodes it also checks if the number of shares has become zero

-	Display_Portfolio_Trend – Plot the absolute value portfolio held by the user after transaction. This function uses Matlab based engine to provide additional plotting functionality. The “balance_sheet.txt” file is read and the time & portfolio values are stored in arrays which are the passed to mxArrays variables that can be recognized by matlab.
Then there are other important functions including the following:
-	Sort_Portfolio
-	Save_Stock_Portfolio
-	Access_Stock_Portfolio
-	Save_Portfolio_Valuation
-	Access_Portfolio_Valuation
The main file allows you to select options between picking a Stock Portfolio account or Bank Account or simply exit. For the both the options, you can choose between any of the functions defined in the above classes. 


Stockval = cumulative sum of all the stocks in your portfolio
Portfolioval = Stockval + Current_Cash_Balance
Current_Cash_Balance = balance in your account



account_transaction_history.txt
Deposit                                      $ (deptemp= 100)    on  (date)      Current_Cash_Balance(5000)
Withdraw                                   $ (deptemp= 500)    on (date)      Current_Cash_Balance (4500)
stock account debited                $ (total_amount=2000)   on (date)  Current_Cash_Balance (2500)


stock_transaction_history.txt

Buy         stock symbol            number of shares            stock price           total_amount         date

Buy = activity
Stock_symbol = company name
Number of shares = number of shares bought
Stock_price = price per share (based on random slection of file from two given text files)
Total_amount = total value of shares bought
Date = date of transaction



