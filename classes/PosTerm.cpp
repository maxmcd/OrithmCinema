//Main Definition file of PosTerm.h

#include "PosTerm.h"

/************************************************
The PosTerm "Point of sale Terminal" Class      *
Provides coders with a number of point of Sale  *
members that allows for *semi-rich functionality*
related to sales. It has been written so that   *
it may be reused in other programs. See class   *
comments for additional information             *
regarding use.                                  *
*************************************************/

/*This function is an overloaded constructor. During creation of an object is can accept a tax
rate as an argument and then write to rate to a file for later usage. Example of using this:
PosTerm pos1(TaxRate); << PosTerm is the Class name followed by the instance name with a 
variable/CONST
in side parens holding a tax rate*/
PosTerm::PosTerm(double Trate) {
	dblTaxRate = Trate;
	intNumberSold = 0;
	dblTotalSale = 0.0;
	dblCashPayment = 0.0;
	dblChange = 0.0; 
		 
	//writing tax rate to file called taxrate.txt
	ofstream taxfile;
	taxfile.open("files/taxrate.mer"); //WILL OVERWRITE IF EXISTS!
	taxfile << dblTaxRate;
	taxfile.close();
} //End overloaded Constructor
	

/*This is the default constructor it is used the same way as the overloaded constructor but with
out the passing of arugument Example : PosTerm pos;*/	
PosTerm::PosTerm() {
	dblTaxRate = 0;
	intNumberSold = 0;
	dblTotalSale = 0.0;
	dblCashPayment = 0.0;
	dblChange = 0.0;
} //End Default Constructor
	
/*Notice Return type. This function sets the member variable dblTaxRate to what ever tax rate rate
is stored in the file "files/taxrate.mer" if the file exist if successful it will return true!*/
bool PosTerm::setTax() {
	string strTax; //Will hold rate read from file while in string form
	ifstream taxfile ("files/taxrate.mer");		//Attempting to open file
		
    if (taxfile.is_open()) {
		while (getline(taxfile,strTax)) {   
            stringstream convert(strTax);		//convert string to dbl
			convert >> dblTaxRate;
        } 										//End while
		taxfile.close();						//Closing input file
		return true;
    } else { 									//returning false as flag for function error
				return false;
	} 											//End if else
}

//Rewrites a new value to the tax file
void PosTerm::reassignTax(double Trate) {
	ofstream taxfile;
	taxfile.open("files/taxrate.mer"); 			//WILL OVERWRITE IF EXISTS!
	taxfile << Trate;
	taxfile.close();
}
		
/*Notice Return Type. This function calculates total number sold and total amount due.
*/
bool PosTerm::setSale(int amountSold, double cost) {										 
	if ((amountSold > 0) && (cost >= .0000)) { 					//All sales must be great than zero, cost may be free ($0.0) incase of promotions
		intNumberSold += amountSold; 							//summing intNumberSold
		dblTotalSale = amountSold * cost; 						//calculating sale total
		dblTotalSale += (dblTotalSale * (dblTaxRate / 100)); 	//adding the tax
		return true; 											//Returning true for successful operation
	} else { 													//returning false as flag for function error ie amount sold was 0 or less and cost was a neg num
		return false; 
	}
} //End setSale

/*Notice Return Type. This function sets the amount of change due to a purchaser if any and Sets the amount of cash tendered
Returns true only if amount Tendered is  greater than the cost of purchase*/	
bool PosTerm::setChange(double &cash) {
	if (cash >= dblTotalSale) { 			//allows for exact change
		dblChange = cash - dblTotalSale;
		dblCashPayment = cash;
		return true;
	} else {
		return false; 						//Returns false as flag for function error should **restart payment function upon false return!!
	}
} 											//end setChange

/*Returns the total amount of the sale currently held in the var dblTotalSale ie net total purchase*/
double PosTerm::getTotalSale() {
	return dblTotalSale;
}

/*Returns the amount of cash tendered for payment held by dblCashPayment*/
double PosTerm::getPayment() {
	return dblCashPayment;
}

/*Returns the total number of items sold held by intNumberSold*/
double PosTerm::getNumberSold() {
	return intNumberSold;
}

/*Returns current set Tax rate held by dblTaxRate*/
double PosTerm::getTax() {
	return (dblTaxRate / 100);
}

/*Returns the amount of change due to purchaser held by dblChange*/
double PosTerm::getChange() {
	return dblChange;
}
