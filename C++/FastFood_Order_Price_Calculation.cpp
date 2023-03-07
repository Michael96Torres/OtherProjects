// Michael Torres
// Section 1004
// Assignment 10: Welcome to the Krusty Krab (Struct Version)

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int CAPACITY = 50;
const double TAX = 0.0725;
//Using these variable for the capacity of the arrays and the Tax applied

struct menuItem
	{
		string itemName;
		double price;
		int quantity;
	};
	
// Creating the struct with the elements of the menu

void getItems(menuItem items[],  int &size, ifstream &infile) // Function used to get items from file
{
	while (!infile.eof()) // Loops until end of file reached 
	{
			infile >> items[size].itemName >> items[size].price >> items[size].quantity; 
			size++;

		if(infile.eof()) // Stops loop if end of file reached
		{
			break;
		}

	}
};

void sortItemsByQuantity(menuItem items[], int size);
// Uses bubble sort algorithem given to us to sort the items
void outputItem(string itemName, int itemLen, double price, int priceLen);
// Outputs the menu using iomanip
int main(){

	menuItem items[CAPACITY]; // Sets the size if the struct array
	int size = 0; // The initial size items entered is set to zero
	int howMany, selectionID; // Variables used for user selection
	string filename; // USed to choose file
	ifstream infile; // For input collection from file
	double tax = 0; // For total tax that will be applied
	double totalPrice = 0; // For Adding up the total price to be paid


	// This is a loop given to us that will reprompt a user until file is opened
	 do
	 	{
	 		cout << "Enter an input file: ";
	 		cin >> filename;
	 		infile.open(filename.c_str());
	 	}
	 while(!infile.is_open());

	cout << "Welcome to the Krusty Krab!" << endl;

	getItems(items, size, infile); // Gathers the data we need
	infile.close(); //Closes the file after all items have been collected

	char orderMore ='n'; // This variable will be used to ask if they would like to continue ordering
	while(orderMore == 'n') // Starting the loop by setting it true
	{
		sortItemsByQuantity(items, size); // Applying bubble sort ro data

		for(int i=0; i < size; i++) //Counter controlled loop
		{
		if(items[i].quantity != 0) // Ouputs the items as long as there is available quantity
		{
			cout << left <<setw(5) << (i+1); // Lists the items
			outputItem(items[i].itemName, 20, items[i].price,6); //Using function to output
		}
		}

		cout << "What would you like to order? " << endl; //Prompt for user
		cin >> selectionID; // User makes a section

		while(cin.fail() || selectionID > size || selectionID < 1 || (items[selectionID-1].quantity == 0))
		{
			cin.clear();
			cin.ignore(100,'\n');
			cout << "What would you like to order? ";
			cin >> selectionID; 
		}
		// Loop that will ensure an appropriate response is input
		// Parameters set to ensure input is valid
		// Makes sure quantity is not zero, subtract due to array due to array size

		cout << endl << "How many orders of this item would you like? ";
		cin >> howMany;
		//Prompt and input for how many of each item ordered

		while (cin.fail() || howMany < 1)
		{
			cin.clear();
			cin.ignore(100,'\n');
			cout << "How many orders of this item would you like? ";
			cin >> howMany;
		}
		// Loop if input fails to repromt user

		if (howMany > items[selectionID - 1].quantity) // Have to subtract 1 from selection due to array
		{
			cout << "Sorry, only " << items[selectionID - 1].quantity << " are available..." << endl;
		}
		// Displays how many are available if too many are ordered
		else
		{
			cout << "Ok, we will bring that right out" << endl;
			items[selectionID - 1].quantity = items[selectionID - 1].quantity - howMany;
			totalPrice = totalPrice + (items[selectionID-1].price * howMany);
		}
		// After the quanity is selected it will subtract that number from the available quantity
		// Then it will add it up to the total price

		cout << "Will this complete your order?(y/n) "; // Prompt if more items are to be ordered

		cin >> orderMore; // user input
		tolower(orderMore); // Uses this to allow both upper or lower case input
		while (cin.fail() || (orderMore != 'n' && orderMore != 'y')) 
		{
			cin.clear();
			cin.ignore(100,'\n');
			cout << " Will this complete your order? ";
			cin >> orderMore;
		}
		// Loop to repromt user if invalid input
	}
	cout << endl << endl;
	cout << "Alriight, time to pay! " << endl;
	tax = (totalPrice * TAX);
	// This will calculate the tax applied using the total price and tax constant

	cout << fixed << setprecision(2); // Sets ouput to 2 decimal places
	cout << left << setw(10) << "Amount" << "$" << right << setw(10) << totalPrice << endl;
	cout << left << setw(10) << "Tax" << "$" << right << setw(10) << tax << endl;
	cout << left << setw(10) << "Total" << "$" << right << setw(10) << (tax + totalPrice) << endl;
	// This is used to format the output of the price and tax


	return 0;
}


void sortItemsByQuantity(menuItem items[], int size){
	// Using bubble sort algorithm given to us
	for (int i = 0; i < size - 1; i ++)
	{
		for (int j = 0; j < size - i - 1; j ++)
		{
			if (items[j].quantity > items[j+1].quantity)
			{
				swap (items[j].quantity,items[j+1].quantity);
				swap(items[j].itemName, items[j+1].itemName);
				swap(items[j].price, items[j+1].price);
				//Swapping each element that is related to the item to make sure they all line up
			}
		}
	}
}

void outputItem(string itemName, int itemLen, double price, int priceLen){
	// Outputs the menu into nice format
	cout << fixed << setprecision(2); // Sets the decimal places to 2
	cout << left << setw(itemLen) << itemName << "$"; 
	cout << right << setw(priceLen) << price << endl;
}






