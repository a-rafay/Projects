#include <iostream>
#include <vector>

using namespace std;

struct Node  {
	int val; // Value of the node
	Node *next; // Pointer to the next node
};

struct LinkedList  {

	Node *first; // Pointer pointing to the begining of the list
	LinkedList() { first = NULL; }

	void insert(int valueToInsert) {
		Node* newNode = new Node;
		newNode->val = valueToInsert;
		newNode->next = NULL;

		Node* start;
		/* List is empty so first must be initialized as well */
		if (first == NULL || first->val >= newNode->val)
		{
			newNode->next = first;
			first = newNode;
		}
		else
		{
			/* Find the node before the point of insertion */
			start = first;
			while (start->next != NULL && start->next->val < newNode->val)
			{
				start = start->next;
			}
			newNode->next = start->next;
			start->next = newNode;
		}
	}

};

int hash(int value, int elements, int max_array_value){
	int hashVal = (value*elements)/(max_array_value+1);
	return hashVal;
}

void bucketSort (int array[], int size) {
	vector <LinkedList> arrayOfList;
	/* Initializing the list to NULL */
	for (int i = 0; i < size; i++){
		LinkedList A;	// An empty linked list 
		arrayOfList.push_back(A);
	}

	/* Searching for the max of the data */
	int max = array[0];
	for (int i = 1; i < size; i++) if (array[i] > max) max = array[i];

	for (int i = 0; i < size; i++) {
		int index = hash(array[i], size, max);
		arrayOfList[index].insert(array[i]);
	}
	
	int index = -1;
	for (int i = 0; i < size; i++)
		if (arrayOfList[i].first != NULL) {
			Node* start = arrayOfList[i].first;
			while (start) {
				array[++index] = start->val;
				start = start->next;
			}
		}
}

int main () {
	int array[10] = { 60,2,6,2,5,7,22,23,43,56 };
	int size = sizeof(array) / sizeof(array[0]);

	cout<<"Array before bucket sort: ";
	for (int i =0; i < size; i++) cout<<array[i]<<" ";
	bucketSort(array, size);
	cout<<"\nArray after bucker sort: ";
	for (int i =0; i < size; i++) cout<<array[i]<<" ";
	cout<<endl;
	return 0;
}
