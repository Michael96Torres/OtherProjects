// Michael Torres
// Programming Exercise 2

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<sstream>

using namespace std;


string monthNames[12]={"January", "February", "March", "April", "May",
"June", "July", "August", "September", "October", "November", "December"};

/******************class specification for address Type*******************/
class addressType{
public:
	addressType(); // Default constructor that sets the default values
				   // for street address, city, state and zipcode
	addressType(string, string, string, int); // Constructor that sets the street address;
											  // city, state and zipcode
	void setAddressTypeInformation(string, string, string, int);
	void setStreetAddress(string);		// Sets the street address
	string getStreetAddress()const;		// Returns the street address
	void setCity(string);				// sets the city
	string getCity()const;				// Returns the city
	void setState(string);				// sets the state
	string getState()const;				// Returns the state
	void setZipCode(int);				// sets the Zip Code
	int getZipCode() const;				// Returns the Zip Code
	void print() const;					// Prints the street address, city, state, zipcode
private:
	string streetAddress;
	string city;
	string state;
	int zipcode;
};

addressType::addressType(){ //Default constructor
	streetAddress = " ";
	city = " ";
	state = " ";
	zipcode = 0;
}

addressType::addressType(string stAdd, string c, string s, int z){ //Constructor with parameters
	streetAddress = stAdd;
	city = c;
	state = s;
	zipcode = z;
}

void addressType::setAddressTypeInformation(string stAdd, string c, string s, int z){ 
	//Used to set the Address Type information
	streetAddress = stAdd;
	city = c;
	state = s;
	zipcode = z;
}

void addressType::setStreetAddress(string s){ //Sets the street
	streetAddress = s;
}

string addressType::getStreetAddress() const{ // Returns the Street Address
	return streetAddress;
}

void addressType::setCity(string c){ // Sets the city
	city=c;
}

string addressType::getCity() const{ //Returns the city
	return city;
}

void addressType::setState(string s){ //Sets the state
	state=s;
}

string addressType::getState() const{ //Returns the state
	return state;
}

void addressType::setZipCode(int z){ //Sets the zipcode
	zipcode=z;
}

int addressType::getZipCode() const{ //Returns the zipcode
	return zipcode;
}

void addressType::print() const{ //Prints out all that information
	cout << "Street Address: " << streetAddress << endl;
	cout << "City: " << city << endl;
	cout << "State: " << state << endl;
	cout << "Zip Code: " << zipcode << endl;
}

/********************* End of Class adressType*****************/

/*********************Class personType**************************/

class personType{
public:
	void print() const; // Function to outpout first and last name
	void setName(string first, string last); //Sets first and Last name
	string getFirstName() const;  // Returns the First Name
	string getLastName() const;   // Returns the Last Name
	personType();
	personType(string, string);   // Constructor that sets first and Last name
private:
	string firstName;
	string lastName;
};

void personType::print() const{ //Used to print name
	cout  << firstName << " " << lastName << endl;
}

void personType::setName(string first, string last){ //Constructor
	firstName=first;
	lastName=last;
}

string personType::getFirstName() const{ //Gets the First Name
	return firstName;
}

string personType::getLastName() const{ //Gets the Last Name
	return lastName;
}

personType::personType(){ //Default constructor
	firstName=" ";
	lastName=" ";
}

personType::personType(string first, string last){ //Constructor with parameters
	firstName = first;
	lastName = last;
}

/********************* End of Class personType*****************/

/******* Class extPersonType which inherits personType ********/

class extPersonType : public personType{
public:
	string getClassification() const; 		//Returns Classifications
	void setClassification(string);			//Sets Classification
	string getPhoneNumber() const;			//Gets the phone number
	void setPhoneNumber(string);			//Sets the phone number
	void print() const;						//prints the data
	extPersonType();						//Default constructor
	extPersonType(string, string, string, string); 
private:
	string classification;
	string phoneNo;
};

extPersonType::extPersonType() //Defualt constructor
{
	setClassification(" ");
	setPhoneNumber(" ");
}

extPersonType::extPersonType(string fName, string lName, string c, //Constructor with parameters
	string ph) : personType(fName, lName){
	setClassification(c);
	setPhoneNumber(ph);
} 

string extPersonType::getClassification() const{ // Returns Classification
	return classification;
}

void extPersonType::setClassification(string c){ // Sets the classification
	classification=c;
}

string extPersonType::getPhoneNumber() const{ //gets the phone number
	return phoneNo;
}

void extPersonType::setPhoneNumber(string ph){ //sets teh phone number
	phoneNo=ph;
}

void extPersonType::print() const{ //Used to print this information
	personType::print();
	cout << "Classification: " << classification << endl;
	cout << "Phone Number: " << phoneNo << endl;
}

/********************* End of Class extPersonType*****************/

/*************************** Class dateType***********************/

class dateType{
public:
	void setDate(int, int, int);		//Function to set the date
	int getDay() const;					//Function to return the day
	int getMonth() const;				//Function to the return month
	int getYear() const;				//Function to return year
	void printDate() const;				//Function to output the date
	dateType();							//Default constructor
	dateType(int, int, int);			//Constructer to set the date
private:
	int dMonth;
	int dDay;
	int dYear;
};

void dateType::setDate(int month, int day, int year){ //Sets the date
	dMonth=month;
	dDay=day;
	dYear=year;
}

int dateType::getDay() const{ //Returns the day
	return dDay;
}

int dateType::getMonth() const{ //Returns the month
	return dMonth;
}

int dateType::getYear() const{ //Returns the year
	return dYear;
}

void dateType::printDate() const{ //Prints out the date
	cout << dMonth << "-" << dDay << "-" << dYear << endl;
}

dateType::dateType(int month, int day, int year){ //Constructor with parameters
	dMonth=month;
	dDay=day;
	dYear=year;
}

dateType::dateType(){ //Default constructor
	dMonth=0;
	dDay=0;
	dYear=0;
}

/*********************** End of Class dateType *******************/

/********************* Class of addressBookType ******************/

class addressBookType : public extPersonType,
						public addressType,
						public dateType{

public: //Sets the personal information
	void setPersonInformation (string firstName, string lastName,
			string classification, string phoneNumber,
			string streetAddress, string city, 
			string state, int zipcode, string dateOfBirth);
	void print() const; //Prints all the information
private:
	void splitAndSetDate(string dateOfBirth);
};

void addressBookType::setPersonInformation(string firstName, string
				lastName, string classification, string phoneNumber,
				string streetAddress, string city, string state,
				int zipcode, string dateOfBirth){
	setName(firstName,lastName);
	setAddressTypeInformation(streetAddress,state,city,zipcode);
	setClassification(classification);
	setPhoneNumber(phoneNumber);
	splitAndSetDate(dateOfBirth);
}

void addressBookType::print() const{ //Prints out the updated information
	extPersonType::print();
	addressType::print();

	cout << "Date of Birth: ";
	dateType::printDate();
	cout << "- - - - - - - - - - - - - - - - - " << endl;
}

void addressBookType::splitAndSetDate(string dateOfBirth){
	//To find the position of the first hyphen (-)
	//in the dateOfBirth string
	int pos = dateOfBirth.find('-');
	//To extract the month from the dateOfBirth string
	string month = dateOfBirth.substr(0,pos);
	//To extract the remaining part of the dateOfBirth
	//except month part and hyphen
	string remainingPart = dateOfBirth.substr(pos+1, dateOfBirth.length());
	//To find the position of the hyphen(-)
	//In the remaining part of the string that is extracted
	int posRemainingPart=remainingPart.find('-');
	//To extract the day part
	string day = remainingPart.substr(0,posRemainingPart);
	//To extract the year part
	string year = remainingPart.substr(posRemainingPart+1, dateOfBirth.length());

	//Conversion of string to int for month, day, and year
	int m = atoi(month.c_str());
	int d = atoi(day.c_str());	
	int y = atoi(year.c_str());

	dateType::setDate(m,d,y);
}



/*********************** End of Class addressBookType *******************/

//Used to get all of the data from the text file
void loadDataFromFile(addressBookType abt[], int& numOfPersons, int& cd){
	string firstName;
	string lastName;
	string classification;
	string streetAddress;			//Variables used to save our information
	string state;
	string city;
	int zipcode;
	string dateOfBirth;
	string phoneNumber;

	ifstream infile;
	int i;
	string temp;

	infile.open("dataset_10.txt"); //opens the txt file by this name

	if (!infile){
			cout << "Cannot open Input file" << endl;
			cout << "Exit the program" << endl;
			return;
	}

	getline(infile, temp);
	numOfPersons = atoi(temp.c_str());
	for(i=0; i < numOfPersons;i++){
		getline(infile, temp); //To get the space that is 
							   //on the first line of each information
		getline(infile, firstName);
		getline(infile, lastName);
		getline(infile, classification);
		getline(infile, streetAddress);
		getline(infile, state);
		getline(infile, city);
		getline(infile, temp);
		zipcode = atoi(temp.c_str());
		getline(infile, dateOfBirth);
		getline(infile, phoneNumber);

		abt[i].setPersonInformation(firstName, lastName,
				classification,phoneNumber,
				streetAddress, city, state, zipcode, dateOfBirth);
		//abt[i].print();
	}

	getline(infile, temp); //Skip a blank line
	getline(infile, temp);
	cd = atoi(temp.c_str());
}

//Sort the Address book by last name in alphabetical order
void sortAddressBookByLastName(addressBookType addressBook[], int numOfAddress){


//******************WRITE OWN CODE**********************//

	//Pretty much used bubble sort to compare and swap 

	for (int i = 0; i < numOfAddress-1; i ++){
		for (int j = 0; j < numOfAddress - i - 1; j ++)	//Nested loop for comparing
		{
			if (addressBook[j].getLastName() > addressBook[j+1].getLastName()){
				swap(addressBook[j],addressBook[j+1]); //Swaps if last name comes after
			}
		}
	}

	//Then it prints out the new list by order of last name
	for(int i=0; i < numOfAddress;i++){
		addressBook[i].print();
	}

}


//Search the person by last name
void searchPersonByLastName(addressBookType addressBook[], int numOfAddress, string lName){

//Did not have to use this function but I really enjoyed typing it out :)
	int i=0;
	bool found = false;
	cout << "List of Address for Last Name: " << lName << endl;
	for(i=0; i<numOfAddress; i++){
		if(addressBook[i].getLastName()==lName){
			addressBook[i].print();
			//To indicate atleast one record found
			found = true;
		}
	}
	if(!found){			//Used if no one by that name is found
		cout << "No Records found!" << endl;
		cout << "- - - - - - - - - - - - - - - - - -" <<  endl;
	}




/*

	for(i=0; i<numOfAddress; i++){
		if(addressBook[i].getLastName()==lName){
			addressBook[i].print();
			//To indicate atleast one record found
			found = true;
		}
	}

*/

}





// Print the names of all the people whose Birthdays are in a given month

void printBirthdaysOfPeople(addressBookType addressBook[], int numOfAddress, int month){
	//Also did not have to use this function but loved typing it out :)
	int i=0;
	bool found = false;
	cout << "list of Names who have birthdays on month: " <<
	monthNames[month-1] << endl;

	for(i=0; i< numOfAddress;i++){
		if(addressBook[i].getMonth() == month){
			addressBook[i].print();
			//To indicate atelast one record found.
			found = true;
		}
	}
	if(!found){ //If no record found of that birthday
		cout << "No Records found!" << endl;
		cout << "- - - - - - - - - - - - - - - - - -" <<  endl;
	}
}

//Print the names of all the people between two last names
void printLastNamesOfPeople(addressBookType addressBook[],
	int numOfAddress, string lastName1, string lastName2){

	//Maybe you know what im gonna say :)
	int i=0;
	bool found=false;
	cout << "List of Names in between two last names: "
		 << lastName1 << " and " << lastName2 << endl;
	for(i=0;i<numOfAddress;i++){
		if(lastName1.compare(addressBook[i].getLastName())<0 && 
			lastName2.compare(addressBook[i].getLastName())>0){
			addressBook[i].print();
			//To indicate atleast one record found.
			found=true;
		} 
	}

	if(!found){  //If no record found of that birthday
		cout << "No Records found!"<< endl;
		cout << "- - - - - - - - - - - - - - - - - -" << endl;
	}
}

void writeSortedAddressBookByLastName(addressBookType addressBookType[], int numOfAddress){
	ofstream outfile;	//Using ofstream to create an outfile
	outfile.open("SortedAddressBook.txt");	//Naming my outfile
	
	for(int i=0;i<numOfAddress;i++){
		outfile << addressBookType[i].getFirstName() << " " << addressBookType[i].getLastName() << endl;
		outfile << "Classification: " << addressBookType[i].getClassification() << endl;
		outfile << "Phone Number: " << addressBookType[i].getPhoneNumber() << endl;
		outfile << "Street Address: " << addressBookType[i].getStreetAddress() << endl;
		outfile << "City: " << addressBookType[i].getCity() << endl;
		outfile << "State: " << addressBookType[i].getState() << endl;
		outfile << "Zip Code: " << addressBookType[i].getZipCode() << endl;
		outfile << "Date of Birth: " << addressBookType[i].getMonth() << "-"<< addressBookType[i].getDay() << "-" << addressBookType[i].getYear() << endl;
		outfile << "- - - - - - - - - - - - - - - - - " << endl;
		}
}

//Used to output all of this into a new txtfile



//Print the names of all the people having same area code of their phone number


void printPersonsHavingSameAreaCodePhoneNum(addressBookType addressBook[], 
	int numOfAddress, int areaCode){



cout << "List of Names who have phone number with area code: " << areaCode << endl;

	bool found = false;

	int phoneNumberInt;


	for(int i=0;i<numOfAddress;i++){
		istringstream iss(addressBook[i].getPhoneNumber());	//Turn phone number string to int
		iss >> phoneNumberInt; 
	 	
	 	if(areaCode==phoneNumberInt){ //Then I can check if the area code is within the number
	 		addressBook[i].print(); //Prints out if true
	 		found=true;
	 	}
	 }


	 if(!found){ //If noone is found with that area code
		cout << "No Records found!" << endl;
		cout << "- - - - - - - - - - - - - - - - - -" <<  endl;
	}
}


int main(){
	addressBookType abt[500]; //Creates this array for addressBokType
	int numOfPersons = 0;
	int code;
	loadDataFromFile(abt, numOfPersons, code);
	cout << "Persons Record with phone area code: " << code << endl;
	//For people with the same area code

	printPersonsHavingSameAreaCodePhoneNum(abt, numOfPersons, code);

	cout << endl << endl << "Address Record Sorted by Last Name: " << endl;
	sortAddressBookByLastName(abt,numOfPersons); //Sorts by last name
	writeSortedAddressBookByLastName(abt,numOfPersons); // Creation of new txt file and output

	cout << endl;

	return 0;  
}































