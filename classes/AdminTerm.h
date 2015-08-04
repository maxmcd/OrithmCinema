//See .cpp for Detailed commenting
//See .cpp for Detailed commenting
#ifndef AdminTerm_H
#define AdminTerm_H

//Class AdminTerm Declaration
#include <iostream> //Required for class
#include <String>	//Required for the strings in class
#include <fstream>  //Required for class

using namespace std;
/*************************************************************
The AdminTerm class allows for the creation of one           *
username and password that will be written to a file         *
the class will handle the i&O for getting a username         *
and password. The username and password are stored in        *
a non-secure format ".txt file" There for in no way should   *
it be considered safe. See class for details                 *
**************************************************************/

class AdminTerm {
	private:
		string strUserName;
		string strPassWrd;
	public:
		/*This is the default constructor.
		when a instance of the class is created this constructor automatically runs.
		notice that it initializes both private member variables to "admin". It then
		attempts to open a file named AdminFile.txt if it is successful at doing so
		the constructor will end at this point ,but if the file does not exists it then
		creates the default credentials of admin admin.*/
		AdminTerm() {
			strUserName = "admin";
			strPassWrd = "admin";
			ifstream findFile;
			findFile.open("files/AdminFile.mer");
			
			if (!(findFile)) {
				findFile.close();
				ofstream adminFile;
				adminFile.open("files/AdminFile.mer");
				adminFile << strUserName << endl;
				adminFile << strPassWrd << endl;
				adminFile.close();
			} else {
				findFile.close();
			} //end if else	
		} 	  //End Constructor
		
		//~AdminTerm();//destructor

		/*The setAdmin() and getAdmin functions are large and thus defined outside the class
		see full description at definition.*/
		bool setAdmin(); 							 //prototype
		bool getAdmin(string name, string password); //prototype
			
}; 													 //end class AdminTerm
#endif