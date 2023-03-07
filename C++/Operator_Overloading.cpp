`// Michael Torres
// Lab 7: Operator Overloading

#include <iostream>

using namespace std;

//Class Specifications
class FracType{
	friend ostream& operator <<(ostream&, const FracType &f1);

	public:
		FracType();
		FracType(int, int);
		int getNumer();
		int getDenom();
		void setNumer(int);
		void setDemon(int);
		void print();
		void operator=(FracType); 
		FracType operator*(FracType) const;
		FracType operator+(FracType) const;
		FracType operator-(FracType) const;
		bool operator==(FracType) const;
		float FloatEquiv() const; 
	private: //Privat members only accessed within the class
		int numer, denom;

};

//Implementation of FracType methods

FracType::FracType(){ //Default constructor
	numer=1;
	denom=1;
}

FracType::FracType(int n, int d){ //How instances are created
	numer=n;
	denom=d;
}

int FracType::getNumer(){ //Returns the numerator
	return numer;
}

int FracType::getDenom(){//Returns the denom
	return denom; 
}

void FracType::setDemon(int d){ //Sets denom
	denom=d;
}

void FracType::setNumer(int n){ //Sets Num
	numer=n;
}
void FracType::print(){  //Prints fraction
	cout << getNumer() << "/" << getDenom() << endl;
}

void FracType::operator=(FracType rhs){
	numer = rhs.getNumer();
	denom = rhs.getDenom();
}

FracType FracType::operator*(FracType frac2)const{
	int resultNumer = numer * frac2.getNumer();
	int resultDenom = denom * frac2.getDenom();

	FracType resultFrac(resultNumer,resultDenom); //Constructing a frac using function
												  
	return resultFrac;
}

ostream& operator<<(ostream	&os1, const FracType &f1){
	os1 << f1.numer << "/" << f1.denom << endl;
	return os1;
}


float FracType::FloatEquiv() const{
	return float(numer)/float(denom);
}



FracType FracType::operator+(FracType frac2) const{
	int resultNumer;
	int resultDenom;
	if(denom == frac2.getDenom()){  
		resultDenom = denom;
	}
	else{
		resultDenom=(denom * frac2.getDenom());//Have to change Denom different
	}

	if(denom == frac2.getDenom()){
		resultNumer = numer + frac2.getNumer();
	}
	else{ //Have to chane num if denoms are differnet as well
		resultNumer=((numer * frac2.getDenom()) + (frac2.getNumer()*denom));
	}
	

	FracType resultFrac(resultNumer,resultDenom); //Constructing a frac using function
												
	return resultFrac;

}


FracType FracType::operator-(FracType frac2) const{
	int resultNumer;
	int resultDenom;

	if(denom == frac2.getDenom()){  
		resultDenom = denom;
	}
	else{
		resultDenom=(denom * frac2.getDenom());//Have to change Denom different
	}

	if(denom == frac2.getDenom()){
		resultNumer = numer - frac2.getNumer();
	}
	else{ //Have to chane num if denoms are differnet as well
		resultNumer=((numer * frac2.getDenom()) - (frac2.getNumer()*denom));
	}
	

	FracType resultFrac(resultNumer,resultDenom); //Constructing a frac using function
												  
	return resultFrac;

}
/*

bool FracType::operator==(FracType frac2) const{


}
*/

int main(){

	int n1, n2, n3=1, d1, d2, d3=1;
	char op, ch1;

	cin >> n1 >> ch1 >> d1;
	cin >> op;
	cin >> n2 >> ch1 >> d2;

	FracType f1(n1,d1), f2(n2,d2), f3(n3,d3); //Constructing 3 fractions
	switch (op){ //Switch Depending on operator
		case '*':
			f3=f1*f2;
			break;
		case '+':
			f3=f1+f2;
			break;
		case '-':
			f3=f1-f2;
			break;
	}

	cout << "First Fraction: ";
	f1.print();
	cout << endl;
	cout << "Second Fraction: ";
	f2.print();

	cout << "Result of Operation:  " << op << " is: " << endl;
	//Testing Overloading of operator '<<'
	cout << f3 << endl;
	//Outputs the resulting fraction

	return 0;
}


















