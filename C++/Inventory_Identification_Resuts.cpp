// Michael Torres
// Programming Exercise 1

#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<sstream>

using namespace std;


enum VehicleKind{CAR,PICKUP,TRUCK,BUS,VAN,UNKNOWN}; //Enum for vehicle type 

// Uses the vehicle kind and a switch to return a string
inline const char*ToString(VehicleKind v){
	switch(v){
		case CAR: return "CAR";
		case PICKUP: return "PICKUP";
		case TRUCK: return "TRUCK";
		case BUS: return "BUS";
		case VAN: return "VAN";
		default: return "UNKNOWN";
	}
}

//Uses a switch to 
inline const VehicleKind ToEnum1(string s1){
	if(s1=="CAR") return CAR;
	if(s1=="PICKUP") return PICKUP;
	if(s1=="TRUCK") return TRUCK;
	if(s1=="BUS") return BUS;
	if(s1=="VAN") return VAN;
	return UNKNOWN;
}

// Creating the class that will be used
	class AutoVehicleType
	{
	public:
		AutoVehicleType(); //Default Constructor
		AutoVehicleType(string brand,int year, string country, 
			int hp, string id, VehicleKind vk, 
			string amn[], int num_amn);
		//Constructor with Parameters
		void setAutoInfo(string brand,int year,string country,
			int hp, string id, VehicleKind vk, 
			string amn[], int num_amn);
		//This function is used to store the values of the variables in our class

		void setAutoBrand(string brand); //sets variable for brand
		void setYearMade(int yr);	//sets variable for yrMade
		void setCountryMade(string country); //sets variable fro country made
		void setHorsePower(int hp);	//sets variable for hp
		void setNumPlate(string id); //sets variable for palate number
		void setAutoType(VehicleKind vt); //Sets vehicle type
		string getAutoBrand(); //Used to retrun the brand
		int getYearMade();	//Used to return the year made
		string getCountryMade(); // Used to return the country made
		int getHorsePower(); //Used to return the hp
		string getNumPlate(); //Used to return the Plate Number
		VehicleKind getAutoType(); //Used to return the Auto type

		void printVehicle(); //Used to print the vehicle
		void printVehicleInfo(); //Prints all the info of the vehicles

		bool isMadeByCompany(string companyName); //bool to check and see if cars made by same company
		bool HaveIdenticalAmenities(AutoVehicleType otherVehicles); //bool to check identical amenities

	private: //These are variables used to set and return values of cars
		string autoBrand;
		int yearMade;
		string countryMade;
		int horsePower;
		string numPlate;
		VehicleKind autoType;
		int numOfAmenities;
		string amenities[4]; //Sets the string array for the amenities
		int count;
	};

AutoVehicleType::AutoVehicleType(){ //default constructor
	autoBrand="";
	yearMade=1930;
	countryMade="";
	horsePower=0;
	numPlate="";
	autoType=UNKNOWN;
	numOfAmenities=0;
	for(int i=0;i<4;i++)
		amenities[i]="";
}


AutoVehicleType::AutoVehicleType(string b,int y, string c,
	int hp,string id, VehicleKind k, string am[],
	int amenitiesCount){
		setAutoInfo(b,y,c,hp,id,k,am,amenitiesCount);
}
//An additional constructor with parameters which is assigned using set fuction

void AutoVehicleType::setAutoInfo(string brand,int year,
	string country,int hp,
	string id, VehicleKind kind,string am[],
	int amenitiesCount){
	setAutoBrand(brand);//Set functions that set the values of all such variables
	setYearMade(year);
	setCountryMade(country);
	setHorsePower(hp);
	setNumPlate(id);
	setAutoType(kind);
	count = 1;
	numOfAmenities=amenitiesCount;//Loop that counts the number of amenities
	for(int i=0;i<amenitiesCount;i++){
		amenities[i]=am[i];
	}
}

//Used to assign brand
void AutoVehicleType::setAutoBrand(string brand){
	autoBrand=brand;
}
//Used to assign year made
void AutoVehicleType::setYearMade(int y){
	yearMade=y;
}
// Used to assign country made
void AutoVehicleType::setCountryMade(string c){
	countryMade=c;
}
//Used to assign horse power
void AutoVehicleType::setHorsePower(int h){
	horsePower=h;
}
//Used to assign plate number
void AutoVehicleType::setNumPlate(string id){
	numPlate=id;
}
//Used to assign auto type
void AutoVehicleType::setAutoType(VehicleKind t){
	autoType=t;
}
//Used to return brand 
string AutoVehicleType::getAutoBrand(){
	return autoBrand;
}
//used to return year made
int AutoVehicleType::getYearMade(){
	return yearMade;
}
//Used to return country made
string AutoVehicleType::getCountryMade(){
	return countryMade;
}
//Used to return horse power
int AutoVehicleType::getHorsePower(){
	return horsePower;
}
//Used to return plate number
string AutoVehicleType::getNumPlate(){
	return numPlate;
}
//Usde to return auto type
VehicleKind AutoVehicleType::getAutoType(){
	return autoType;
}

//Prints by outputing all get fuctions
void AutoVehicleType::printVehicle(){
	cout << getAutoBrand() << " , ";
	cout << getYearMade() << " , ";
	cout << getCountryMade() << " , ";
	cout << getHorsePower() << " , ";
	cout << getNumPlate() << " , ";
	cout <<	ToString(getAutoType())<<endl; //Convers to string using switch
}

//Used to print more vehicle info by using all the get functions
void AutoVehicleType::printVehicleInfo(){
	int i;
	cout << "Brand= " <<getAutoBrand() << endl;
	cout << "Year= " << getYearMade() << endl;
	cout << "Country Made = " << getCountryMade() << endl;
	cout << "Num of Amenities " << numOfAmenities << endl;
	//cout << 
}


// Function made by me that compares the company name(parameter) to a returned function
	bool AutoVehicleType::isMadeByCompany(string companyName){
		if (companyName.compare(getAutoBrand())==0) //Application of compare function
		return true;
		else return false;
	}

//Function used to check if they have Identical amenities
bool AutoVehicleType::HaveIdenticalAmenities(AutoVehicleType otherVehicles){
	if (numOfAmenities != otherVehicles.numOfAmenities) //First I check the #of amenities
        return false;
    for (int i = 0; i < numOfAmenities; ++i) //Then I check to see if they have the same amenities
        if (amenities[i] != otherVehicles.amenities[i])
            return false;
    return true;
}


// Outputs All vehicles that have identical amenities
void printVehiclesWithIdenticalAmenities(AutoVehicleType vehicles[], int noOfVehicles){
    for (int i = 0; i < noOfVehicles; i++) //Loops through 
	{
    	for (int j = i + 1; j < noOfVehicles; j++) //nested loop for the other vehicle
    	{
        	if (vehicles[i].HaveIdenticalAmenities(vehicles[j]))  //if same amenities its prints the statemnt 
       		{
           		cout<<"Vehicles "<<vehicles[i].getNumPlate()<<" and "<< 
                vehicles[j].getNumPlate()<<" Have Identical set of Amenites" << endl;
        	}
    	}
	}
}

// writes Data about vehicles in a text file named Vehicle Data2
void writeVehicleData(AutoVehicleType vehicles[], int & noOfVehicles){
	ofstream outfile;	//Using ofstream to create an outfile
	outfile.open("VehicleData2.txt");	//Naming my outfile
	outfile << noOfVehicles << endl;

	for(int i=0; i<noOfVehicles; i++){
		outfile << vehicles[i].getAutoBrand() << endl;
		outfile << "\t" << vehicles[i].getYearMade() << endl;
		outfile << "\t \t" << vehicles[i].getCountryMade() << endl;
		outfile << "\t" << vehicles[i].getHorsePower() << endl;
		outfile << "\t \t" << vehicles[i].getNumPlate() << endl;
		outfile << "\t" << "UNKNOWN" << endl;
	}
}

	void getVehicleData(AutoVehicleType vehicles[],int& noOfVehicles)
	{
		string vBrand;	//Making variables to use to get vehicle data
		int vYear;
		string vCountry;
		int vHp;
		string vId;
		VehicleKind vType;
		int vAmenitiesCount;
		string amenities[4]={"AAA","BBB","CCC","DDD"};

		int i,j;
		float f1;
		ifstream infile;
		char ch;
		string temp;
		//Used to open file and read text
		infile.open("VehicleData1.txt");
		if(!infile){
			cout << "Cannot open Input file" << endl;
			cout << "Exit the program" << endl;
			return;
		}

		// Used to get all of the info in the text file
		//
		getline(infile,temp);
		noOfVehicles=atoi(temp.c_str());
		for(int i=0;i<noOfVehicles;i++){
			getline(infile,vBrand);
			getline(infile,temp);
			vYear=atoi(temp.c_str()); //use of asci to integer
			getline(infile,vCountry);
			getline(infile,temp);
			vHp=atoi(temp.c_str()); //use of asci to integer
			getline(infile,vId);
			getline(infile,temp);
			vType=ToEnum1(temp);
			getline(infile,temp);
			vAmenitiesCount=atoi(temp.c_str());//use of asci to integet
			for(int j=0;j<vAmenitiesCount;j++){
				getline(infile,amenities[j]);
			}
			//Loop to count amenities
			vehicles[i].setAutoInfo(vBrand,vYear,vCountry,vHp,
				vId,vType,amenities, vAmenitiesCount);
		}
	}

//Used to print the vehicle data

void printVehicleData(AutoVehicleType vehicles[],int noOfVehicles){
	int i;
	//Loop that prints all the vehicles
	for(i=0;i<noOfVehicles;i++){
		vehicles[i].printVehicleInfo();
		cout << endl << "----------------------" << endl;
	}

}


	void printAllVehiclesMadeBy(AutoVehicleType vehicles[], int noOfVehicles,string brand){	
		for(int i=0; i<noOfVehicles;i++){
			if(vehicles[i].isMadeByCompany(brand)){ //Used compare brand fucntion and then prints
				vehicles[i].printVehicleInfo();
				cout << endl << "---------------------" << endl;
				cout << endl;
			//loop that prints if vehicles made by the same brand
			}
		}
	}



int main(){
	AutoVehicleType AV[100]; //Creates an array with a limit of 100
	int numOfV=0;
	getVehicleData(AV,numOfV); //Gets the vehicle data

	cout << "List of Vehicles in the Inventory: " << endl;
	printVehicleData(AV, numOfV); //Prints the data

	string s1 ="Toyota"; 
	cout << endl << endl << "List of Vehicles Made by " << s1 << " : " << endl;
	printAllVehiclesMadeBy(AV,numOfV,s1); //Prints all the vehicles made by the same brand

	printVehiclesWithIdenticalAmenities(AV,numOfV); //Applying the print statement
	writeVehicleData(AV,numOfV); // Creates the VehicleData2.txt file



	return 0;
}

// Professor Gewali's code does not print all of the vehicles with the same amenities
      