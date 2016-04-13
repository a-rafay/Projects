#include <iostream>

using namespace std;

struct Node  {
	int val; // Value of the node
	Node *next; // Pointer to the next node
};

class LinkedList  {
	// Private Functions/Variables
	private:
	Node *first; // Pointer pointing to the begining of the list
	Node *last; // Pointer pointing to the end of the list

	public:

	LinkedList() {
		first = NULL;
		last = NULL;
	}

	~LinkedList() {}


	void print() {
		Node* node = first;
		cout<<"[";
		while(node != NULL) {
			cout << node->val;
			if (node != last) cout << ", ";
			node = node->next;
		}
		cout<<"]\n";
	}

	bool isEmpty(){
		return size() == 0;
	}

	int size() {
		int size = 0;
		if (first == NULL) return size;
		Node* node = first;

		while (node != NULL) {
			size++;
			node = node->next;
		}
		return size;
	}

	int occurance(int value) {
		if (first == NULL) return -1;
		Node* node = first;
		int count = 0;
		while (node != NULL) {
			if (node -> val == value) count++;
			node = node -> next;
		}
		return count;
	}

	bool compare(LinkedList& withMe) {
		if (first == NULL) return false;
		if (size() == withMe.size()) {
			Node* A = first;
			Node* B = withMe.first;
			while (A != NULL) {
				if (A->val != B->val) return false;
				A = A -> next;
				B = B -> next;
			}
			return true;
		}
		return false;
	}

	void duplicate (LinkedList& here) {
		if (first == NULL) return;
		Node* node = first;
		while (node != NULL) {
			here.insert(node->val);
			here.insert(node->val);
			node = node -> next;
		}
	}

	void duplicate () {
		if (first == NULL) return;
		Node* node = first;
		while (node != last) {
			Node* newNode = new Node;
			newNode->val = node->val;
			newNode->next = node->next;
			node->next = newNode;
			node = node -> next->next;
		}
		insert(node->val);
	}

	void rotate() {
		if (first == NULL || first == last) return;
		Node* second = first->next;
		first -> next = NULL;
		last -> next = first;
		last = first;
		first = second;
	}

	void split(LinkedList& A, LinkedList& B, int position) {
		if (position > size()) {
			cout<<"Error, position beyond the size of list\n";
			return;
		}
		int count = 0;
		Node* node = first;
		while (count != position) {
			count++;
			A.insert(node->val);
			node = node->next;
		}
		while (node != NULL) {
			B.insert(node->val);
			node = node->next;
		}
	}

	void merge(LinkedList& A, LinkedList& B) {
		int n = A.size() + B.size();
		int array[n];
		Node* node = A.first;
		int i = 0;
		while (node != NULL) {
			array[i++] = node->val;
			node = node->next;
		}
		node = B.first;
		while (node != NULL) {
			array[i++] = node->val;
			node = node->next;
		}
	
		// sorting now

		for (int c = 0 ; c < ( n - 1 ); c++) {
			for (int d = 0 ; d < n - c - 1; d++) {
				if (array[d] > array[d+1]) {
					int swap = array[d];
					array[d] = array[d+1];
					array[d+1] = swap;
				}
			}
		}

		for (int k = 0; k < n; k++) insert(array[k]);
	}

	void common (LinkedList& A, LinkedList& B) {
		Node* node1 = A.first;
		while (node1 != NULL) {
			Node* node2 = B.first;
			while (node2 != NULL) {
				if (node1 -> val == node2 -> val) insert(node1 -> val);
				node2 = node2 -> next;
			}
			node1 = node1 -> next;
		}
	}

	void insert(int valueToInsert) {
		Node* newNode = new Node;
		newNode->val = valueToInsert;
		newNode->next = NULL;

		if (last != NULL) {
			last->next = newNode;	
		}
		else {
		// List is empty
		// So first must be initialized as well
			first = newNode;
		}
		last = newNode;
	}
};

int main ()
{
	LinkedList ListA;
	ListA.insert(1);
	ListA.insert(2);
	ListA.insert(3);
	ListA.insert(4);
	ListA.insert(5);
	ListA.insert(-5);
	ListA.insert(0);
	ListA.insert(5);
	ListA.insert(10);

	cout<<"ListA: ";
	ListA.print();

	LinkedList ListB;
	ListB.insert(1);
	ListB.insert(2);
	ListB.insert(3);
	ListB.insert(4);
	ListB.insert(5);
	ListB.insert(-5);
	ListB.insert(0);
	ListB.insert(5);
	ListB.insert(10);

	cout<<"ListB: ";
	ListB.print();

	if (ListA.compare(ListB)) cout<<"Lists are same\n";
	else cout<<"Lists are not same\n";

	LinkedList ListC;
	ListC.insert(1);
	ListC.insert(2);
	ListC.insert(3);

	LinkedList ListD;
	ListC.duplicate (ListD);

	cout<<"ListC: ";
	ListC.print();
	cout<<"ListD with duplicate elements of ListC: ";
	ListD.print();

	ListA.duplicate();
	cout<<"ListA with duplicate elements of itself: ";
	ListA.print();

	cout<<"5 is occuring "<<ListA.occurance(5)<<" times in ListA\n";
	
	ListB.rotate();
	cout<<"Rotated ListB: ";
	ListB.print();

	LinkedList split1, split2;

	ListA.split (split1, split2, 6);

	cout<<"Splits of ListA: ";
	split1.print();
	split2.print();

	LinkedList merge1, merge2, out;

	merge1.insert(1); merge1.insert(3); merge1.insert(5);
	merge2.insert(2); merge2.insert(4); merge2.insert(6);

	cout<<"Merging 2 lists now: \n";
	merge1.print(); merge2.print();
	out.merge(merge1, merge2);
	cout<<"Merge result: ";
	out.print();
	
	LinkedList common1, common2, commonOut;

	common1.insert(1); common1.insert(3); common1.insert(5); common1.insert(7); common1.insert(9);
	common2.insert(1); common2.insert(5); common2.insert(6);

	cout<<"Intersection of 2 lists now: \n";
	common1.print(); common2.print();
	commonOut.common(common1, common2);
	cout<<"Intersection result: ";
	commonOut.print();

	return 0;
}


