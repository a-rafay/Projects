#include<iostream>
using namespace std;

struct treenode
{
	int value;
	treenode *left;
	treenode *right;
};

class BT
{
	private:		
		treenode *root;	
	public:

	BT() {root=NULL;}

	BT(BT& anotherTree){
		root = NULL;
		treenode* node;
		anotherTree.getRoot(node);
		preorder(node);
	}

	void getRoot(treenode* &nodeptr) { nodeptr = root; }

	void insert_node(int num) {
	
		treenode *newnode;
		treenode *nodeptr;
	
		newnode=new treenode;
		newnode->value=num;
		newnode->left = newnode->right = NULL;
		if (!root)
			root = newnode;	

		else {
			nodeptr=root;
		
			while (nodeptr != NULL)
			{
				if (num < nodeptr->value)
				{
					if (nodeptr->left)
						nodeptr = nodeptr->left;
					else
					{
						nodeptr->left = newnode;
						break;
					}
				}
					
				else if (num > nodeptr->value)
				{
					if (nodeptr->right)
						nodeptr = nodeptr->right;
					else
					{
						nodeptr->right = newnode;
						break;
					}
				}
			
				else { cout<<"DUPLICATE ! "<<endl;	break;}			
			}
		}		
	}

	void print_desc()
	{
		treenode *nodeptr = root;
		print_desc(nodeptr);
	}

	void print_desc(treenode *nodeptr)
	{
		if (nodeptr == NULL) return;
		if (nodeptr -> right == NULL) {
			cout<<nodeptr -> value<<endl;
			print_desc (nodeptr -> left);
			return;
		}
		print_desc (nodeptr -> right);
		cout<<nodeptr -> value<<endl;
		print_desc (nodeptr -> left);
	}

	bool isBST(treenode *node) 
	{ 
		if (node->left != NULL && node->right != NULL) {
			if (node->value > node->left->value &&
				node->value < node->right->value) {
				bool left = isBST(node->left);
				bool right = isBST(node->right);
				return (left & right);
			}
			return false;
		}
		if (node-> left == NULL && node-> right == NULL) return true;
		if (node -> left == NULL)
			if (node->value < node->right->value) return isBST(node->right);
		if (node -> right == NULL)
			if (node->value > node->left->value) return isBST(node->left);
	} 

	void printLessThan(int key, treenode * node)
	{
		if (node == NULL) return;
		if (node->value < key) cout<<node->value<<endl;
		printLessThan(key, node->right);
		printLessThan(key, node->left);
	}

	void preorder(treenode* node)
	{
		if (node == NULL) return;
		insert_node(node->value);
		preorder(node->left);  
		preorder(node->right);
	} 
};

		
int main()
{
	BT tree;
	
	cout<<"INSERTING NODES !\n"<<endl;
	tree.insert_node(78);
	tree.insert_node(13);
	tree.insert_node(99);
	tree.insert_node(4);
	tree.insert_node(10);
	tree.insert_node(80);
	tree.insert_node(100);
	
	treenode *nodeptr;
	cout<<"Printing in descending order\n";
	tree.print_desc();

	cout<<"Values less than 81 in this tree are\n";
	tree.getRoot(nodeptr);
	tree.printLessThan(81, nodeptr);

	cout<<"Creating a new tree by sending another tree as an argument to the constructor\n";
	BT tree2(tree);
	cout<<"This new tree is the same and the old tree\n";
	tree2.print_desc();

	tree.getRoot(nodeptr);
	cout<<"Checking if our tree is binary or not\n";
	if (tree.isBST(nodeptr)) cout<<"This tree is binary tree\n";
	else cout<<"This tree is not binary tree\n";

	tree.getRoot(nodeptr);
	cout<<"Now root->right child has value: "<<nodeptr->right->value;
	cout<<"\nWe will change this value to a lower value to prove that this will not be a binary tree anymore\n";
	nodeptr->right->value = 12;
	if (tree.isBST(nodeptr)) cout<<"This tree is binary tree\n";
	else cout<<"This tree is not binary tree\n";

	return 1;	
}

