#include "AdminTerm.h" 

/*************************************************************
The AdminTerm class allows for the creation of one           *
username and password that will be written to a file         *
the class will handle the i&O for getting a username         *
and password. The username and password are stored in        *
a non-secure format ".txt file" There for in no way should   *
it be considered safe. See class for details                 *
**************************************************************/

/*setAdmin(). Notice this function has a return type of bool. Thus returning true"Any no zero int" 
for success or false for failure "0". First it clears the screen and then asks for input of a
username and password. These values are stored as strings and both the user name and password
are case sensitive. It then echoes to the user to accept or not. If accepted it is written to the
file "files/AdminFile.mer" and then true is returned. If declined nothing is written to the file false is
returned. The return bool in this case should be used to see if the function should be called again.*/
bool AdminTerm::setAdmin() {
			char yOrN = 'n';
			while (!(yOrN == 'y' || yOrN == 'Y')) { //getting username and password from user
				system("cls");
				cout << "\n\n Set Administrator\n\n";
				cout << " Enter a username with no spaces, case sensitive: ";
				cin >> strUserName;
				cout << "\n Enter a password with no spaces, case sensitive: ";
				cin >> strPassWrd;
			
				system("cls");
				cout << "\n Username : " << strUserName
					 << "\n Password : " << strPassWrd
					 << "\n\n Accept? \'y\' for yes \'n\' for no : ";
				cin >> yOrN;	
			}
			
			//write user name and password to file
			if (yOrN == 'y' || yOrN == 'Y') {
				ofstream adminFile;
				adminFile.open("files/AdminFile.mer");
				adminFile << strUserName << endl;
				adminFile << strPassWrd << endl;
				adminFile.close();
				return true; 
			} else {
				return false;
			}
} //End Set Admin

/*Notice the return type of bool. This function requires two arguments these arguments are named "name" and
"password" also notice that they are of type string. Thus they accept a username and password. When called
the function opens the adminFile.Txt reads the contents then compares it to the passed arguments. Returning
true for a match and false upon a non-match.
*/
bool AdminTerm::getAdmin(string name, string password) {
			ifstream adminFile;
			adminFile.open("files/AdminFile.mer");
			getline(adminFile,strUserName);
			getline(adminFile,strPassWrd);
			adminFile.close();
			if (strUserName == name && strPassWrd == password) {
				return true;
			} else {
				return false;
			}
}

