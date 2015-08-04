//PosTerm.h
//See .cpp for Detailed commenting
#ifndef PosTerm_H
#define PosTerm_H

#include <iostream> //Required for io
#include <sstream>	//Required for string to num conversion
#include <String>	//Required for the string
#include <fstream>	//Required for file io

using namespace std;

/************************************************
The PosTerm "Point of sale Terminal" Class      *
Provides coders with a number of point of Sale  *
members that allows for *semi-rich functionality*
related to sales. It has been written so that   *
it may be reused in other programs. See class   *
comments for additional information             *
regarding use.                                  *
*************************************************/

class PosTerm {
	private:
		int intNumberSold; 		//Holds the number sold of a particular item
		double dblTaxRate; 		//tax rate for sales that require it
		double dblTotalSale; 	//Total sale
		double dblCashPayment;  //Tendered amount
		double dblChange; 		//Returned tender 
	public:
		PosTerm(double Trate);
		PosTerm();
		void reassignTax(double Trate); 
		bool setTax();
		bool setSale(int amountSold, double cost);
		bool setChange(double &cash);
		double getTotalSale();
		double getPayment();
		double getNumberSold();
		double getTax();
		double getChange();
}; 								//End PosTerm Class declaration
#endif