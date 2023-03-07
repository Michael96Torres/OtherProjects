// Michael Torres
// Programming Assignment 4: Doubly Linked List

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <fstream>

using namespace std;

struct nodeType{ //Creating the nodeType
	int info;
	nodeType *next;
	nodeType *back;
};

class OrderedDoublyLinkedList{
public:
	//This method returns true if the list is empty; otherwise false
	bool isEmpty();
	//Insert x in appropriate place in the list to keep it sorted
	void insertNode(int x);
	//Delete one node (the first occuring one) from the list containing x
	void deleteNode(int x);

	bool searchList(int x);

	OrderedDoublyLinkedList();
	//print the contents of this list
	void print();
	// Makes this list the merged list of two lists in the arguments
	void mergeLists(OrderedDoublyLinkedList &List1, OrderedDoublyLinkedList &List2);
	//This method returns true if items in the list are distinct; otherwise false
	bool distinctItems();
	//Print only those items that are repeated in the list
	void printRepeatedItems();
	//List1 is a copy of the first half of the list
	//List 2 is a copy of the second half
	void splitList(OrderedDoublyLinkedList &List1, OrderedDoublyLinkedList &List2);
	int getCount();

private:
	int count;
	nodeType *first; //The begining of the list
	nodeType *last;  //The end of the list
};

int OrderedDoublyLinkedList::getCount(){ //Used to get length/count of list
	return count;
}

OrderedDoublyLinkedList::OrderedDoublyLinkedList(){ //Creating default constructor
	first=NULL;
	last=NULL;
	count=0;
}

bool OrderedDoublyLinkedList::isEmpty(){ //If the list is empty
	return(first==NULL);
}

void OrderedDoublyLinkedList::print(){ //USed to pring the list
	nodeType *current;

	current=first;

	while(current!=NULL){ //Starts at begining and then traverses
		cout << current ->info << " ";
		current= current->next; //USed to go to next
	}
}

bool OrderedDoublyLinkedList::searchList(int x){
	nodeType *current; //Have to use this to traverse the list
	current=first;
	bool found=false;

	while(current != NULL && !found)
		if(current->info >= x)//If it is found
			found=true;
		else
			current=current->next; //Goes onto the next one
	if(found)
		found =(current->info == x); //This is to see if they are same

	return found;
}

void OrderedDoublyLinkedList::deleteNode(int x){ //Used to delete a node
	nodeType *current;
	nodeType *previous;

	bool found;
	if(first == NULL) // If the List is empty
		cout << "Empty List" << endl;
	else if(first->info == x){ //If we delete the first node
		current=first; //Setting the current to the first of the nodes
		first=first->next;

		if(first!=NULL) //If first node empty
			first->back=NULL;
		else
			last=NULL;
		count--; //Decreasing count since deleted

		delete current;
	}	
	else{
		found=false;
		current=first;
		while(current != NULL && !found) //Searches the list for x
			if(current->info >= x)
				found=true;
			else
				current=current->next;
		if(current == NULL) //If not in the list
			cout << "Item is NOT in the list!" << endl;//If you try to delete an item not in list
		else if(current->info == x){ //
			previous=current->back; //Adjusting the list
			previous->next=current->next;

			if(current->next != NULL) //If the next nide is null
				current->next->back=previous; //Have to adjust list
			if(current == last)
				last=previous;

			count--; //Decresae count becuase deleted node
			delete current;
		}
		else//
			cout << "Item is NOT in the list!" << endl;// If item is not in list
	}
}


void OrderedDoublyLinkedList::insertNode(int x){ //Function used to insert a node
	nodeType *current; //Node for the current 
	nodeType *previous; //the previous link on list
	nodeType *newNode; //creating the next node
	bool found;

	newNode = new nodeType;
	newNode->info = x;
	newNode->next = NULL;
	newNode->back = NULL;

	if(first==NULL){  // For an Empty List
		first=newNode; // Setting it to the new node
		last=newNode;
		count++; //Adds one so we can track length
	}
	else{
		found=false;
		current=first; //Sets the first node to current

		while(current != NULL && !found) //Search the list
			if(current->info >= x) //If x is less than or equal to current value
				found=true; 
			else{
				previous=current; //Changes the previous to the current
				current=current->next; //Then goes to next node
			}
		if(current==first){ // inserts a newNode first
			first->back=newNode;
			newNode->next=first;
			first=newNode;
			count++; //Adds one so we can track length
		}
		else{ //Inserts a newNode between the previous and current
			if(current!=NULL){
				previous->next = newNode; //Used to adjust all the nodes
				newNode->back = previous;
				newNode->next = current;
				current->back = newNode;
			}
			else{
				previous->next =  newNode; //Adusting nodes for new node
				newNode -> back =previous;
				last = newNode;
			}
			count++; //Adds one so we can track length
		}
	}
}

void OrderedDoublyLinkedList::mergeLists(OrderedDoublyLinkedList &List1,	
 										OrderedDoublyLinkedList &List2){
		
		nodeType *temp = List2.first; //Temp Variables that allow use to traverse
		nodeType *temp2=List2.last;//

		do{
			List1.insertNode(temp2->info); //Used to add add the node to the first
			List2.deleteNode(temp2->info); //Removing the node from list 2
			temp2=temp2->back; //Traversing the list going backwards
		}
		while(temp2!=NULL);
	}


void OrderedDoublyLinkedList::splitList(OrderedDoublyLinkedList &List1, 
										OrderedDoublyLinkedList &List2){
	nodeType *temp=List1.last; //Use this traverse list


	int half=(List1.getCount()/2); //Finds length of list and then splits it in 
									 //Add one so it can be exactly like the output given

	if(List1.getCount()%2==0){
		for(int i=0;i<half;i++){ //Goes until half the list is split
			List2.insertNode(temp->info); //Inserts to list 2
			List1.deleteNode(temp->info); //Removes from List 1
			temp=temp->back; //Continues from last to first
		}
	}
	else{	//Add one so it can be exactly like the output given
		for(int i=0;i<half+1;i++){ //Goes until half the list is split
			List2.insertNode(temp->info); //Inserts to list 2
			List1.deleteNode(temp->info); //Removes from List 1
			temp=temp->back; //Continues from last to first
		}
	}

}

bool OrderedDoublyLinkedList::distinctItems(){ // Used to see if no same elements
	nodeType *temp =first; //temp node

	while(temp->next!=NULL){ //Goes until end of list
		if(temp->info==temp->next->info){ //Checks If two sequential items in sorted list are same 
			return false;
		}
		else{ //If not it continues to next link
			temp=temp->next;
		}
	}
	return true;
}

void OrderedDoublyLinkedList::printRepeatedItems(){ //Used to print repeated items
	nodeType *temp = first; //Temp to traverse the list

	int num=1; //for the number of times the item is present
	if(distinctItems()){
		cout << "No Repeated Items " << endl;
	}
	else{
		cout << "List repeated items in the list: " << endl;
		while(temp->next!=NULL){
			if(temp->info==temp->next->info){ //Comparing to see if sequential items same
				while(temp->info==temp->next->info){ //Then see how many of those in the list
					if(temp->next->info==temp->next->info){
						num++; //Increase for number of times in list 
						temp=temp->next; //Goes onto next item
					}
				}
				cout << "Item " << temp->info << " is repeated " << num << " times"<<endl;

				num=1; //Reset the number back to one for next link
				temp=temp->next; //Goes on to next one
			}
			else{
				temp=temp->next; //Goes on to next link if not repeated
			}
		}
	}
}


int main(){
	OrderedDoublyLinkedList L1, L2, L3; //Creation of new lists
	int x;

		while(cin>>x) //Used to get our data
		{
			if(x==99999) break; //Goes until special integer found
			else L1.insertNode(x); //Inserts to list 1
		}
		while(cin>>x) //Inserts the rest to list 2
		{
			L2.insertNode(x);
		}
	
	cout << "First Ordered List: ";
	L1.print(); //Prints list 1
	cout << endl;
	cout << "Second Ordered List: ";
	L2.print();//Prints list 2
	cout << endl << endl;

	cout << "Merged Ordered List: ";
	L1.mergeLists(L1,L2); //Merges the two lists
	L1.print(); cout << endl; //Then prints out the outcome
	cout << endl << endl;


	cout << "Are Items in the Mergers List Distinct? "<< endl;
	if(L1.distinctItems()){ //Checks if list is distinct
		cout <<"Yes, Distinct Items"<< endl;
	}
	else{
		cout << "No, Not Distinct" << endl;
	}
	cout << endl << endl;

	L1.printRepeatedItems(); //Checks list 1 for repeated items
	cout << endl << endl;


	cout << "Two Lists formed by splitting merged list in the middle are: " << endl;
	L1.splitList(L1,L2); //Splits up the two lists
	L1.print(); //Prints List 1
	cout << endl << "and" << endl;
	L2.print();//Prints list 2
	cout << endl << endl;


	return 0;
}








