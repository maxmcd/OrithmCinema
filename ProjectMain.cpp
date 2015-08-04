/************************************************************************
This program is a pos system for a theatre called Orithm Cinema, 		*
The cinema has 15 rows of seats and 30 seats in reach row.				*
The program allows the user to:											*
	Sell Tickets and Generate a daily report 							*
There is also an admin menu that allows the user to: 					*
	Adjust pricing per row, Re-initialize all pricing, Adjust Tax, 		*
	and change Admin credentials. 										*
The program has two classes seperate that are used throughout the 		*
program called PosTerm and AdminTerm. A color coded chart is provided 	*
for the user for easier viewing;  										*
This chart is stored in an array for data handling. 					*
*************************************************************************


Written by:  James Crews
Date Written:  07/21/2014	
*/


#include <iostream>		//Used for displaying with cin and cout statements.
#include <fstream>		//Used for opening and closing files.
#include <string>		//Used to allow string data types
#include <iomanip>		//Used for output manipulation
#include <sstream>		//Used for functions in vaildation functions
#include <windows.h>	//Used to allow text coloring
#include <cstdlib>		//Used for exit failure and exit success functions

#include "classes/AdminTerm.cpp"	//Pulls admin file which pulls the adminTerm classe
#include "classes/PosTerm.cpp"		//Pulls the pos file which pulls the pos class
using namespace std;

void WelcomeMessage();		//Says hello and runs first time checks
void AdminCreation();		//Creates user name and password by user input
void ChartInitialization();	//Loads pre-built chart
void LoadChart();			//Loads saved chart
void SaveChart();			//Saves current chart
void PrintChart();			//Prints chart in memory
void InitializePricing();	//Reformats all pricing per row by user input
void MainMenu();		
void AdminTools();			//Admin menu selection
void PriceAdjust();			//Allows change of price for one row
void SellTickets();			
void GenReport();			//Prints report to screen and to a file
int RowValidate(int);		
int SeatValidate(int);
int InputValidate(string, int);
double TaxValidation();
double CashValidate(double);
double PriceValidate(int);
bool Password();			//Validates user name and password

ifstream inputFile;			//Create global access to input file data type inputFile
ofstream outputFile;		//Create global access to output file data type outputFile

const string S_FILE = "files/seatingChart.mer", S_COMPANY_NAME = "Orithm Cinema";
double dblChart[15][31];	

//Functions where the program starts
int main() {
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE); //Preset up for SetConsoleTextAttribute
	SetConsoleTextAttribute (screen,15);			 //Sets text color to white and background to black

	WelcomeMessage();
	MainMenu();
	return 0; 
}

//Tests if program has been used before if not it will 
// run a setup of user entered variables
void WelcomeMessage() {
	system("cls");	
	cout << endl;	
	PosTerm pos;							//Activate pos class for TaxValidation

	inputFile.open(S_FILE.c_str());	
	if (inputFile) {						//If file cannot open runs else statement
		inputFile.close();
		cout << " Welcome to " << S_COMPANY_NAME << "'s pos system. \n";
	} else {																			
		cout << " Welcome to " << S_COMPANY_NAME << "'s pos system. \n\n"
			 << " Since this is your first time I will need to peform a quick setup \n\n";
		
		ChartInitialization();				//Sets up chart from document given for program
		PosTerm PosTerm(TaxValidation());	//Gets tax and applies it.
		AdminCreation();					//Gets User Name and Password and applies it
		InitializePricing();				//Accepts the pricing per row and applies it
	}
	LoadChart();
}

//Has the user enter pricing for all rows in theatre
void InitializePricing() {
	int iRow;

	for (iRow = 0; iRow<15; iRow++) {			 //Loops through all 15 rows
		dblChart[iRow][0] = PriceValidate(iRow); //Sets prices to the first coloum in each row		
		}	
	system("cls");
	SaveChart();
}

//Changes the pricing of a row based on user input
void PriceAdjust() {
	int iRow;

	PrintChart();
	cout << "\n Enter the row you would like to adjust pricing for: ";	
		cin >> iRow;
		cin.clear();
		cin.ignore();	
		while (iRow < 1 || iRow > 15) {
			cout << "\n Please enter a number between 1 and 15 \n";
			cin >> iRow;
			cin.clear();
			cin.ignore();	
		}
	
	dblChart[iRow - 1][0] = PriceValidate(iRow - 1); //Accounts for starting at 0 and replaces the rows price	
	system("cls");
	SaveChart();
}

//Pulls the chart from a file and saves it into an array
void LoadChart() {
	inputFile.open(S_FILE.c_str());			

	for (int a=0; a<15; a++) {				//First loop copys row information 
		for (int b=0; b<31; b++) {			//Second loop copys coloum information
			inputFile >> dblChart[a][b];	//Finds information seperated by spaces
		}
	}

	inputFile.close();
}

//Saves the current file array into a chart in a file to be pulled for later use
void SaveChart() {
	int a, b;

	outputFile.open(S_FILE.c_str());	
	outputFile << fixed;											//Uses fixed to prevent any scientific notation
	for (a=0; a<15; a++) {											// and setprecision for easier viewing in the file
		outputFile << setprecision(2) << dblChart[a][0] << " ";		// where the chart is stored
		for (b=1; b<31; b++) {											
			outputFile << setprecision(0) << dblChart[a][b] << " ";	//The loop steps through 0.0 of the array in 
		}															// increments of 0.1 until it reaches 14.30 its full size
		outputFile << endl;											// The spaces are to help for loading the file.
	}
	outputFile.close();	
}

//Prints the current chart stored in the array to the screen
void PrintChart() {
	int a, b;
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE); //Preset for changing color
	
	cout << "\n\n\n" << setw(30) << "*" << S_COMPANY_NAME << "* \n\n"
		 << setw(5) << "";
	for (a=0; a<3; a++) {							 //Loop used to print 3 sets of 10 (0-9) to the screen
		for (b=1; b<10; b++) {						 //Here the 1-9 is looped and printed
			cout << setw(2) << b;
		}
		cout << " 0";							 	 //0 is set seperate to avoid having a 0 in the first position
	}
	cout << setw(9) << "Cost \n" << setw(6);
	for (a=0; a<70; a++) {							 //Loop presents a seprating line ont the screen
		cout << "-";
	}
	
	for (a=0; a<15; a++) {
		cout << endl << setw(4) << (a + 1) << "|";						//Prints from 1-15 on the screen and a seperator
		for (b=1; b<31; b++) {											//Loops through printing the Chart from the array

			if (dblChart[a][b] == 8) {									//Eight represents seat taken
				SetConsoleTextAttribute (screen, 11);					//Color coded red for taken
			} else {
				SetConsoleTextAttribute (screen, 12);					//Color coded blue for open
			}
			cout << setprecision(0) << setw(2) << dblChart[a][b];		//Prints the actual number
		}
		SetConsoleTextAttribute (screen,10);							//Color green for money 		
		cout << fixed << setprecision(2) << setw(8) << dblChart[a][0];	//Prints price per row
		SetConsoleTextAttribute (screen,15);							//Change color back to white
		cout << " |" << (a + 1) << " ";									//Prints 1-15 again with seperator line
	} 
	cout << endl;
}

//Chart given with job for starting template
//Stores to a file then calls loadchart to place into an array
void ChartInitialization() {

	//Number 8 is free seat and number 0 is a taken seat
	//Places in a file with 0.0 represnting the row prices and is then loaded back
	// in order to be placed in program's array.
	outputFile.open(S_FILE.c_str());	
	outputFile << 0.0 << " 0 0 0 8 8 8 0 0 0 8 8 8 0 8 8 8 8 8 8 8 8 0 0 0 0 0 8 8 8 8 "
			   << 0.0 << " 8 8 8 8 0 0 0 0 0 0 0 0 0 0 0 0 0 8 8 8 8 0 0 0 0 0 0 0 8 8 "
			   << 0.0 << " 0 0 8 8 8 0 0 0 0 0 0 0 0 0 0 8 8 8 8 8 8 8 8 0 0 0 0 8 8 8 "
			   << 0.0 << " 0 0 8 8 8 8 8 8 0 0 0 0 0 0 0 0 0 0 0 0 0 0 8 8 0 0 0 0 0 0 "	
			   << 0.0 << " 0 0 0 0 0 0 0 0 8 8 8 8 8 0 0 0 0 0 0 0 0 0 8 8 8 8 8 8 8 8 "
			   << 0.0 << " 8 8 8 8 8 8 8 8 8 8 8 8 8 8 0 0 0 0 0 0 0 0 0 0 0 0 0 8 8 8 "
			   << 0.0 << " 8 8 8 8 8 8 8 0 0 0 0 0 0 0 0 0 0 0 0 8 8 8 8 8 8 8 8 8 8 8 "
			   << 0.0 << " 0 0 0 0 0 0 0 0 0 0 0 0 8 8 0 0 0 0 8 8 8 8 8 8 8 8 8 8 8 8 "
			   << 0.0 << " 8 8 8 8 8 8 8 8 8 0 0 0 0 0 8 8 8 8 8 8 8 8 8 8 8 8 0 0 0 0 "
			   << 0.0 << " 8 8 8 8 8 8 0 0 0 0 0 0 0 0 0 0 0 0 0 8 8 8 8 8 8 8 8 8 8 8 "
			   << 0.0 << " 8 0 0 0 0 0 0 0 0 0 0 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 0 0 "
			   << 0.0 << " 8 8 8 8 8 8 8 8 8 8 8 8 8 0 0 0 0 0 0 0 0 8 8 8 8 8 8 8 8 0 "
			   << 0.0 << " 8 8 8 0 0 0 0 0 0 0 0 0 0 8 8 8 8 8 8 8 8 8 0 0 8 8 8 8 8 8 "
			   << 0.0 << " 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 "
			   << 0.0 << " 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 8 ";
	outputFile.close();
	LoadChart(); //Loads the freshly saved chart into an array for data handling
}

//Main menu used by user
void MainMenu() {
    string sInput;				
    bool bSuccess, bReset;
    int iChoice, iOptions = 4;
	bReset = true;    
    
	while (bReset) {									//Set to an infinite loop until the user choices exit
		iChoice = 0;									
		while (iChoice < 1 || iChoice > iOptions) {		//Repeats until a proper choice is made
			PrintChart();								
			cout << "\n\n Main Menu \n\n"				
				 << " 1. Sell Tickets \n"
				 << " 2. Generate Today's Report \n"
				 << " 3. Admin Tools \n"
				 << " 4. Exit \n\n"
				 << " Your Choice: ";
			getline(cin, sInput);						
			system("cls");								
			iChoice = InputValidate(sInput, iOptions);	
		}    
		 
		if (iChoice == 1) {
		   SellTickets();			//Goes to sell to menu
		} else if (iChoice == 2) {
		   GenReport();				//Runs end of day report
		} else if (iChoice == 3) {
			bSuccess = Password();	//Checks if user knows the admin name and password
			if (bSuccess) {			//If the data return is true given access to admin menu
				AdminTools();
			} 
		} else {
			exit(EXIT_SUCCESS);		//Exits the program
		}
	}   
}

//Menu for use after admin login
void AdminTools() {
    string sInput;
	double dblTax;
	bool bReset = true;
    int iChoice, iOptions = 7;
    PosTerm pos;									//Activates posterm class for Tax Reassigments

	while (bReset) {								//Set to an infinite loop until the user choices exit
		iChoice = 0;
		while (iChoice < 1 || iChoice > iOptions) { //Repeats until a proper choice is made
			PrintChart();
			cout << "\n\n Administration Tools \n\n"
				 << " 1. Adjust pricing per row \n"	
				 << " 2. Re-initialize pricing \n"
 				 << " 3. Adjust Tax \n"
				 << " 4. Reassign admin credentials \n"
				 << " 5. Logout of admin \n"
				 << " 6. Exit \n\n"
				 << " Your Choice: ";
				 
			getline(cin, sInput);
			system("cls");
			iChoice = InputValidate(sInput, iOptions);
		}    
		 
		if (iChoice == 1) {
			PriceAdjust();						//Change pricing by one row
		} else if (iChoice == 2) {
			InitializePricing();				//Change all row pricing
		} else if (iChoice == 3) {
			pos.reassignTax(TaxValidation());	//Changes the tax in file
			pos.setTax();						//Changes the tax in system
		} else if (iChoice == 4) {
			AdminCreation();					//Changes admin name and password
		} else if (iChoice == 5) {
			system("cls");
			return;								//Returns to previous menu
		} else {
			exit(EXIT_SUCCESS);					//Exits the program
		}
	}
}

void SellTickets() {
	string sInput;
	int iSeatHolder[10], iRowHolder[10];	//Place Holders in order to sell in bulk at different prices
	int iChoice, iSeat, iRow, iCounter = 0, iOptions = 3;		
	bool bFull, bReset = true, bRepeat = true, bBlocked = false;
	double dblCash, dblTotalHolder = 0, dblTotalHolderTax = 0;
	
	PosTerm pos;				//Activates pos class
	pos.setTax();				//Makes tax active

	while (bRepeat == true) {	//Main loop
		system("cls");
		PrintChart();

		bFull = true;						//Sets to automatic full seating and then
		for (int a=0; a<15; a++) {			// flags as false if any seat is open 
			for (int b=1; b<31; b++) {	
				if (dblChart[a][b] == 8) {	//Loops through every seat to check for an empty seat
					bFull = false;
				} 
			}
		}
		if (bFull == true) {				//If seating is full informs user then returns to main menu
			cout << "\n  ~The theatre is full~ ";
			system("pause");
			system("cls");
			return;							//Command to return to previous menu
		}

		cout << "\n Please enter the row: ";
		cin  >> iRow;
		iRow = RowValidate(iRow);
		cout << "\n Please enter the seat: ";
		cin  >> iSeat;
		iSeat = SeatValidate(iSeat);
		system("cls");
		PrintChart();

		bBlocked = false;						//Prevents user from buying same seat already in cart													
		for (int a = 0; a < iCounter; a++) {	//Loops through placeholders (cart) to check against recent choices
			if ((iRowHolder[a] == (iRow - 1)) && (iSeatHolder[a] == iSeat)) {	
				bBlocked = true;
			}
		}

		if ((dblChart[iRow - 1][iSeat] == 0) || bBlocked == true) {				//Checks if seat has been sold or in cart
			cout << "\n\n Row:" << iRow << " Seat:" << iSeat					
				 << " is currently taken. Please choice another seat. \n";
			system("pause");

		} else {
			bReset = true;
			while (bReset) {	
				iChoice = 0;
				system("cls");

				while (iChoice < 1 || iChoice > iOptions) {						//Loop for menu
					PrintChart();
					cout << "\n\n Row:" << iRow << " Seat:" << iSeat							
						 << " is $" << (dblChart[iRow - 1][0] * (1 + pos.getTax())) << " with tax."	
						 << "\n\n You currently have seats: "
						 << setw(5) << " Row:" << iRow << " Seat:" << iSeat;	//Prints last selected seat
					
					dblTotalHolder = dblChart[iRow - 1][0];						//Sets total without tax from selected item 
					for (int a = 0; a < iCounter; a++) {						//Loop prints off all seats that are saved in cart minus the last selected
						cout << endl << setw(32) << " Row:" << (iRowHolder[a] + 1) << " Seat:" << iSeatHolder[a];
						dblTotalHolder += dblChart[iRowHolder[a]][0];			//Adds item in cart to total
					}
					pos.setSale(1,dblTotalHolder);								//Runs pos math on total

					cout << "\n The total so far is $" << pos.getTotalSale();
					cout << "\n\n Would you like to "
						 << "\n 1. Add another seat to this cart."
						 << "\n 2. Finish and pay."
						 << "\n 3. Discard transaction. \n\n"
						 << " Your Choice: ";;
				getline(cin, sInput);
				system("cls");
				iChoice = InputValidate(sInput, iOptions);
				}    

				if (iChoice == 1) {							
					if (iCounter < 9) {						//Limits cart to 9 seats at a time
						iRowHolder[iCounter] = (iRow - 1);	//Sets current item into cart
						iSeatHolder[iCounter] = (iSeat);	
						iCounter++;							//Counter increase used to see how many seats are in the cart
						bReset = false;						
					} else {
						cout << "\n You cannot hold any more seats in your cart";
					}	

				} else if (iChoice == 2) {
					pos.setSale(1,dblTotalHolder);				//Runs pos math for total
					cout << "\n Great you want: " << (iCounter + 1) << " Seats"
						 << "\n That will be: $" << pos.getTotalSale() << " with tax \n";

					dblCash = CashValidate(pos.getTotalSale());	//Places a vaildated cash input into a place holder for next function						
					pos.setChange(dblCash);						//Finds change to give to person

					cout << "\n Your Receipt \n"
						 << "---------------------------"
						 <<  "\n Number of seats sold: " << (iCounter + 1)
						 << "\n\n You have seats: "
						 << setw(5) << " Row:" << iRow << " Seat:" << iSeat; 
					
					dblChart[iRow - 1][iSeat] = 0;				//Seats last seat selected to full
					for (int a = 0; a < iCounter; a++) {		//Runs through each seat in cart and sets as full
						cout << setw(32) << "\n Row:" << (iRowHolder[a] + 1) << " Seat:" << iSeatHolder[a];
						dblChart[iRowHolder[a]][iSeatHolder[a]] = 0;
						}
					SaveChart();								//Save changes to chart
					
					cout << "\n Total Cost $" << pos.getTotalSale()
						 << "\n Tax Rate Applied %" << (pos.getTax() * 100)	//Times 100 to be aligned with % output
						 << "\n Amount Tendered $" << pos.getPayment()
						 << "\n Change Due $" << pos.getChange()
						 << "\n\n Have a nice day! \n\n";
					system("pause");
					system("cls");
					bRepeat = false;
					bReset = false;
				} else {
					bRepeat = false;
					bReset = false;
				}
			}
		}
	}
}

//Basic Vaildation for entering row numbers and testing in range
int RowValidate(int iNum) {
	cin.clear();	//Clear and ignores used to prevent infinite looping with spaces and letters
	cin.ignore();	
	while (iNum < 1 || iNum > 15) {
		cout << "\n Please enter a number between 1 and 15: ";
		cin  >> iNum;
		cin.clear();
		cin.ignore();	
	}
	return iNum;
}

//Basic Vaildation for entering row numbers and testing in range
int SeatValidate(int iNum) {
	cin.clear();	//Clear and ignores used to prevent infinite looping with spaces and letters
	cin.ignore();	
	while (iNum < 1 || iNum > 30) {
		cout << "\n Please enter a number between 1 and 30: ";
		cin  >> iNum;
		cin.clear();
		cin.ignore();	
	}
	return iNum;
}

//Validates any input, used in this program with menu selections
// validation function accepts the string passed and the number of options to choice from: X (1-X)
int InputValidate(string sInput, int iMax) {
    int iTemp;
    
    stringstream(sInput) >> iTemp;
    if ( sInput.length() > 1 ) {
        cout << "\n Please choose from menu \n";
        iTemp = 0;
    } else if ( !isdigit(sInput[0]) ) {
        cout << "\n Please choose from menu \n";
        iTemp = 0;
    } else if ( iTemp < 1 || iTemp > iMax ) {
        cout << "\n Please choose from menu \n";
        iTemp = 0;
    }                       
    return iTemp;
}

//Vaildation tests user name and password
//If failed certain amount of time returns bool value stating unsuccessful else sets as successful
bool Password() {
	AdminTerm admin; 
    string sName;
	string sPass;
	int iAttempts = 4;
	bool bError = false;								//Resetting error to false

	while ((iAttempts != 0) && (bError != true)) {		//Checks attempts made and if passed creds if not repeats menu
		
		system("cls");									//Clearing screen for simulated menu selection
		cout << "\n Welcome to the login menu\n\n";
		cout << "\n Enter username: ";
		cin >> sName;
		cin.clear();
		cin.ignore();
		cout << "\n Enter password: ";
		cin >> sPass;
		cin.clear();
		cin.ignore();
		system("cls");
		
		bError = admin.getAdmin(sName,sPass);			//Checking information entered against what is stored in class and sets value to pass or fail
		if (!bError) {
			cout << "\n Authentication Failed!\n ";
			--iAttempts;								//Decrementing count of attempts
			cout << iAttempts << " Attempts left\n\n";
			system("pause");
		}
	}

	if (iAttempts == 0) {	//Runs if all attempts are failed else says success
		system("cls");
		cout << "\n Excessive Failed attempts. Returning to previous menu!\n\n";
		system("pause");
	} else {
		cout << "\n Authentication Success!\n";
	}
	return bError;
}

//Validation for user to enter correct format of tax information in percentage form.
double TaxValidation() {
    string sInput;
    int iLength, iN, iCount;
    double dblTemp;
    bool again = true;
    
    while (again) {		//Runs until the user enters number that matches conditions listed below
        iN = -1;
        again = false;		
		cout << "\n Please enter the % of tax in 0.00 format."
			 << "\n\n Tax %";
        getline(cin, sInput);
        system("cls");
        stringstream(sInput) >> dblTemp;	
        iLength = sInput.length();				
        
		if ((iLength < 4) || (iLength > 6)) {		//Checks total length allowing 4 being 0 . 0 0
            again = true;							//This allows numbers 0.00 through 999.99
            continue;
        } else if (sInput[iLength - 3] != '.') {	//Checks to max sure sure user entered a decimal
            again = true;
            continue;
        } while (++iN < iLength) {					//Vaildates only numbers are entered
            if (isdigit(sInput[iN])) {
                continue;
            } else if (iN == (iLength - 3) ) {		
                continue;
            } else {
                again = true;
                break;
            }
        } 
    } return dblTemp;
} 

//Validation for user to enter correct format of prices information.
double PriceValidate(int iRow) {
    string sInput;
    int iLength, iN;
    double dblTemp;
    bool again = true;
    
    while (again) {		//Runs until the user enters number that matches conditions listed below
        iN = -1;
        again = false;
        cout << "\n Please enter ticket price for row: " << (iRow + 1) << " in 0.00 format: ";
        getline(cin, sInput);
        system("cls");
        stringstream(sInput) >> dblTemp;
        iLength = sInput.length();
       
		if (iLength < 4) {							//Checks total length allowing 4 being 0 . 0 0
            again = true;							//Allows all numbers
            continue;
        } else if (sInput[iLength - 3] != '.') {	//Checks to max sure sure user entered a decimal
            again = true;
            continue;
        } while (++iN < iLength) {					//Vaildates only numbers are entered
            if (isdigit(sInput[iN])) {
                continue;
            } else if (iN == (iLength - 3) ) {		
                continue;
            } else {
                again = true;
                break;
            }
        } 
    } return dblTemp;
} 

//Cash Validate checks if user entered money in a correct format
double CashValidate(double dblTotal) {
    string sInput;
    int iLength, iN, iCount;
    double dblTemp;
    bool again = true;
    while (again) {
        iN = -1;
        iCount = 0;
        again = false;
        cout << "\n Please enter cash to be tendered in 0.00 format."
			 << "\n If a credit card please enter the exact amount after sale completed \n"
			 << "\n\n  Cash Presented: ";
        getline(cin, sInput);
        system("cls");
        stringstream(sInput) >> dblTemp;
		
		if (dblTemp < dblTotal) {								//Tests of money given is less than amount given
				cout << "\n That is not enough your total is:" << dblTotal;
				again = true;
			}
        iLength = sInput.length();
        while (++iN < iLength) {								//Vaildates only numbers are entered
            if (isdigit(sInput[iN])) {
                continue;
            } else if ( (sInput[iN] == '.') && (iCount < 1) ) {	
                iCount = 1;
                continue;
            } else {
                again = true;
                break;
            }
			
		}
    } return dblTemp;
}

void AdminCreation() {
	bool bError = false; 
	AdminTerm admin; 

	while (!bError) {				//running this function until user accepts their chosen username and password
		bError = admin.setAdmin();	//Calling this function sets up a user chosen username and password
	}
}

//Generates report to the screen and to a file
//Each cout is repeated as a outputfile to save to a document in the same fasion
void GenReport() {

    PosTerm pos;				//Opens Class PosTerm
	pos.setTax();				//Sets tax to active
	double dblTotalHolder = 0;
	int iSeatsLeftTotal = 0;
	int iSeatsLeftRow[15];
	int a,b;

		
	outputFile.open("TodaysReport.doc");		//Opens file for outputting
		cout << "\n\n\n  Row information \n " ;
	outputFile << "\n  Row information \n  ";
	for (a=0; a<38; a++) {						//Loop presents a seprating line ont the screen
		cout << "-";
		outputFile << "-";
	}

	for (a=0; a<15; a++) {						//Loops through each row saving and printing related information
		iSeatsLeftRow[a] = 0;					//Reset of variable
		for (b=1; b<31; b++) {					//Loop increases variable seats left if a seat is found open
			if (dblChart[a][b] == 8) {									
				++iSeatsLeftRow[a];
			} 
		}

		iSeatsLeftTotal += iSeatsLeftRow[a];							//Adds seats left in that row to total seats left
		dblTotalHolder += ((30 - iSeatsLeftRow[a])  * dblChart[a][0]);	//Subtracts amount of seats per row by seats left and times it by row price to find total.
		pos.setSale(1,dblTotalHolder);									//Runs pos class to collect information from sale

		cout << "\n  Row " << setw(2) << a << "| Seats Sold: " << setw(2) << (30 - iSeatsLeftRow[a]) 
			 << "  Seats left: " << setw(2) << iSeatsLeftRow[a];
		outputFile << "\n  Row " << setw(2) << a << "| Seats Sold: " << setw(2) << (30 - iSeatsLeftRow[a])
			 << "  Seats left: " << setw(2) << iSeatsLeftRow[a];
	}

	cout << "\n\n  Total Seats Sold: " << ((30 * 15) - iSeatsLeftTotal)		//Row Length * Width Length - Seatsleft gives you total seats taken
	  	 << "\n  Total Seats Left: " << iSeatsLeftTotal
		 << "\n\n  Tax rate applied %" << (pos.getTax() * 100)				//Times a 100 to account for precentage 
		 << "\n  Net Profit $" << dblTotalHolder
		 << "\n  Profit $" << pos.getTotalSale()
		 << "\n  Total Taxes Collected $" << (pos.getTotalSale() - dblTotalHolder);
	outputFile << "\n\n  Total Seats Sold: " << ((30 * 15) - iSeatsLeftTotal) 
	  	 << "\n  Total Seats Left: " << iSeatsLeftTotal
		 << "\n\n\n  Tax rate applied %" << pos.getTax()
		 << "\n\n  Total Earned Before Tax $" << dblTotalHolder
		 << "\n  Total Earned After Tax $" << pos.getTotalSale()
		 << "\n  Total Taxes Collected $" << (pos.getTotalSale() - dblTotalHolder);
	cout << "\n\n  ~End of Report~ \n\n";
	outputFile << "\n\n  ~End of Report~ \n\n";

	system("pause");
	outputFile.close();
}