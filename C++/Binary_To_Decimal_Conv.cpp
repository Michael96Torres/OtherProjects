// Michael Torres
// Programming Exercise 3: Binary to Decimal

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

void binToDec(int bn, int &d, int &w){ //Function to convert a binary number to Decimal
	if(bn%2==0 && bn/2==0) //Base case that ends the recursion
		return;
	else if(bn%2==1){ //If the last digit of the binary is a one
		bn=bn/10; //Moves on to next digit
		d=d+pow(2,w); //Adds the decimal
		w++; //Increases the binary weight 1
		return binToDec(bn,d,w); // Recursion to continue along the integer
	}
	else
		bn=bn/10; //If the last digit is not a 1
		w++; //Still increases weight by one for next digit 
		return binToDec(bn,d,w);

}

int main(){

	int decimalNum; //The decimal number that gets added up
	int binaryNum; // The number that will get converted
	int bitWeight; //The weight of the binary digit
	decimalNum=0; //Initialized decimal number that gets added
	bitWeight=0; //The weight that continues across teh binary number
	binaryNum=1001101; //The number that will be converted
	binToDec(binaryNum, decimalNum,bitWeight); //Use of the function
	cout << decimalNum << endl; //Outputs the added decimal number


	return 0;
}
