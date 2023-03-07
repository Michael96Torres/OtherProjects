//Michael Torres
//(Stack)

#include <iostream>
#include<stack>
#include<string>
#include<sstream>
#include <cstdlib>

using namespace std;

int main(){ 
	string s1, s2, s3; //Strings that we will use
	int n, n1, n2, result; // The operands
	char op; //For finding the operator to use

	stack<string> strStack, strStack_save; //USing the stack to go from top to bottom
	string word;
	cin >> n; //Number of times it will collect

	//Read the postfix expression
	for(int i=1; i<=n; i++){
		cin >> word;
		strStack.push(word);
	}

	//Access the top and size
	cout << "Top element: " << strStack.top() << endl
		 << "Size of Stack: " << strStack.size() << endl;

	//Print the stack
	cout << "Stack Content: " << endl; //Prints by popping and couting the top
	while(!strStack.empty()){ //Goes until it is completely empty
		word=strStack.top();  //Stores value
		cout << word << endl; //Outputs the value
		strStack.pop(); //Pops the element
		strStack_save.push(word); //Saves the value into the new one
	}

	ostringstream ost1;

	while(strStack_save.size()>1){ //Goes until the size is greater than one 1 and leaves last one

		s1=strStack_save.top(); //Gets the top 
		strStack_save.pop();	//pops it off
		s2=strStack_save.top();
		strStack_save.pop();
		s3=strStack_save.top();
		strStack_save.pop();

		istringstream(s1) >> n1; //Read operand1
		istringstream(s2) >> n2; //Read operand2

		op= s3.at(0); //Read operator

		switch(op){ //The switch to to decide operation based on operator
			case '+' : result = n1 + n2;
					   break;
			case '-' : result = n1 - n2;
					   break;
			case '*' : result = n1 * n2;
					   break;
			default : ;
						break;
		}

		ost1 << result;
		s3=ost1.str(); //Convert result into string
		ost1.str(""); //Clear the stream
		strStack_save.push(s3);
	}
	cout << "Result of the evaluation of the expression is: "
		 << strStack_save.top() << endl; //Outputs the final value after operation performed


	return 0;
}
