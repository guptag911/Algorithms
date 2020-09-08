// B-Tree Implementation ... Insertion is Easy but Deletion is very HARD to implement.

#include<bits/stdc++.h>
using namespace std;

#define MAX_INT 0x3f3f3f3f 
#define acc(x) setprecision(x)
#define boost ios_base::sync_with_stdio(false); cin.tie(NULL);

class Node
{
	int *keys;	// an array that will keep all the keys
	int n;			// Current count of key	s
	bool leaf;		// a boolean which tells weather the  node is leaf node or not	
	Node **child;	// an array that will keep all connected childeren.Max 2*t
	int t;			// Order
	public:
		Node(int _t, bool _l);		// Initailize a node.
		void inserter(int x);		// insert node when maximun keys are not filled/
		void splitChild(int i, Node *p);	// When we have to split bcz of 2*t-1 keys in a node
		void traversal();	// Inorder Traversal	
		void ptraversal();	// Preorder Traversal
		Node *search(int x);	// will search for a key.
		int key_finder(int x);	//Finds the upper bound of x.
		void remover(int x);	// Main functtion that removes node.
		void removeLeaf(int x);	//removes node at index x which is leaf.
		void removenoleaf(int x); //removes node at index x which is not a leaf.
		int gP(int x);	// gives the predecessor of node at index x
		int gS(int x);	// gives the sucessor of node at index x
		void filler(int x);	// fill child if less than t-1 nodes.
		void borrowP(int x); // borrow from prev child
		void borrowN(int x);	// borrow from next child/
		void merge(int x);	//merge two childeren at x and x+1 pos.
	friend class BTree;
};

class BTree
{
	Node *root;
	int t;
	public:
		BTree(int _t)			// CONSTRUCTOR FOR MAKING TREE ROOT.
		{
			root = NULL;
			t = _t;
		}
		void traversal()
		{
			if(root!=NULL)
			{							//IN ORDERED
				root->traversal();
			}
		}
		void ptraversal()
		{								// pRE ORDER TRAVERSAL
			if(root!=NULL)
			{
				root->ptraversal();
			}
		}
		Node* search(int x)
		{								// SEARCHED
			if(root==NULL)
			{
				return NULL;
			}
			else
			{
				return root->search(x);
			}
		}
		void insert(int x);
		void remover(int x);
};

// Constructor for the Btree node.
Node::Node(int t1, bool lf1)
{
	t = t1;	// assigns the order
	leaf = lf1;	
	keys = new int[2*t-1];		// Max keys that a node can hold is 2*t-1
	child = new Node *[2*t];	// Makes children nodes as 2*t;
	n=0; // Curr count of keys.
}

// Inorder Traversal
void Node::traversal()
{
	int i;
	for(i=0;i<n;i++)
	{
		// If the node is non lead node, then we trarverse its children else we print its keys.
		if(!leaf)
		{
			child[i]->traversal();
		}
		cout << " " << keys[i];
	}
	// print the tree with last child.
	if(!leaf)
	{
		child[i]->traversal();
	}
}

void Node::ptraversal()
{
	int i;
	for(i=0;i<n;i++)
	{
		// If the node is non lead node, then we trarverse its children else we print its keys.
		cout << " " << keys[i];
		if(!leaf)
		{
			child[i]->ptraversal();
		}
	}
	// print tree with last child.
	if(!leaf)
	{
		child[i]->ptraversal();
	}
}

Node* Node::search(int p)
{
	int i=0;
	while(i<n && p>keys[i])	// Increment i till the val to be search is greter than key val.
	{
		i++;
	}
	if(keys[i]==p)	// Found
	{
		return this;
	}
	if(leaf)	// Not found
	{
		return NULL;
	}
	return child[i]->search(p); // recurively check in children if not a leaf and not found.
}

void BTree::insert(int p)
{
	// If root is null, make the first node. Simple
	if(root==NULL)
	{
		root = new Node(t, true);
		root->keys[0] = p;
		root->n = 1;
	}
	else
	{
		if(root->n == 2*t-1)	// IF ALL KEYS ARE FILLED
		{
			Node* q = new Node(t, false);	// THIS WILL BE THE NEW ROOT.
			q->child[0] = root;
			q->splitChild(0,root);	// BCZ NOW WE HAVE TO SPLIT A NODE AND MOVE ITS VALUE UP.
			int i = 0;
			if(q->keys[0]<p)	// FIND THE POS OF INSERTION 
			{
				i++;
			}
			q->child[i]->inserter(p);	// INSERT HERE.
			root = q;	// NEW ROOT ASSIGNED.
		}
		else
		{
			root->inserter(p);	// AS SPACE IS LEFT SO RECURSIVE FIND THE POSITION OF INSERTION
		}
	}
}
// IF THE NODE IS NOT FULL THIS IS CALLED.
void Node::inserter(int p)
{
	int i = n-1;
	if(leaf)
	{
		while(i>=0 && keys[i]>p)
		{
			keys[i+1] = keys[i];		//FIND POS OF INSERTION
			i--;
		}
		keys[i+1] = p;
		n = n+1;	// INSERT
	}
	else
	{
		while(i>=0 && keys[i]>p)
		{
			i--;				// FIND POS OF INSERTION IS NOT A LEAF
		}
		if(child[i+1]->n == 2*t-1)
		{
			splitChild(i+1, child[i+1]);	// WE NEED TO SPLIT AS NOW A KEY IS INSERTED IN A NON LEAF.
			if(keys[i+1]<p)
			{
				i++;
			}
		}
		child[i+1]->inserter(p);
	}
}

// Split a node into two child.
void Node::splitChild(int i, Node* h)
{
	Node* z = new Node(h->t, h->leaf);	// This will have keys greater than cutting point.
	z->n = t-1;
	for(int j=0;j<t-1;j++)
	{
		z->keys[j] = h->keys[j+t];
	}
	if(h->leaf==false)
	{
		for(int j=0;j<t;j++)
		{		
			z->child[j] = h->child[j+t];		// Copy last t elements/
		}
	}
	h->n = t-1;
	for(int j=n;j>=i+1;j--)
	{
		child[j+1] = child[j];
	}
	child[i+1] = z;
	for(int j=n-1;j>=i;j--)
	{
		keys[j+1] = keys[j];	// Finding pos of key and shift ahead by 1 pos.
	}
	keys[i] = h->keys[t-1];
	n = n+1;				// change curr no. of keys.
}

// Finds upper bound of x.
int Node::key_finder(int x)
{
	int i = 0;
	while(i<n && keys[i]<x)
	{
		++i;
	}
	return i;
}

// Main function that handles key removal/
void Node::remover(int x)
{
	int i = key_finder(x);
	if(i<n && keys[i]==x)	// Only remove if present
	{
		if(leaf)
		{
			removeLeaf(i);	// is a leaf.so leaf reomver called
		}
		else
		{						
			removenoleaf(i);	// not a leaf, so non leaf remover called/
		}
	}
	else
	{
		if(leaf)
		{
			cout << "Does not exist!\n";
			return ;			// Not found/
		}
		bool flag;
		if(i==n)		// This flag is true when key is present./
		{
			flag = true;
		}
		else
		{
			flag = false;
		}
		if(child[i]->n<t)
		{						// If we remove and have less tahn t keys..so fill it.
			filler(i);
		}
		if(flag && i>n)
		{
			child[i-1]->remover(x);		// IT CAN BE EITHER MERGED WITH PREV CHILD.SO IF IT DOES WE CHECK FOR I-1 CHILD..ELSE WE CHECK ON THE ITH CHILD ITSELF.
		}
		else
		{
			child[i]->remover(x);
		}
	}
	return ;
}

void Node::removeLeaf(int x)
{
									// SHIFT LEFT BY 1 PLACE.
	for(int i=x+1;i<n;i++)
	{
		keys[i-1] = keys[i];
	}
	n--;						// REDUCE COUNT
	return ;
}

void Node::removenoleaf(int x)
{
	int q = keys[x];
	if(child[x]->n >= t)
	{
		int p = gP(x);
		keys[x] = p;				// IF CHILD HAS ATLEAST T KEYS, FIND ITS PRED/
		child[x]->remover(p);
	}
	else if(child[x+1]->n >=t)
	{
		int s = gS(x);
		keys[x] = s;
		child[x+1]->remover(s);		// IF CHILD HAS LESS THAN T KEYS
	}
	else
	{
		merge(x);
		child[x]->remover(q); 		//IF BOTH CHILD AND NEXT CHILD HAS LESS THAN T KEYS.
	}
	return ;
}

int Node::gP(int x)
{
	Node *curr = child[x];
	while(!curr->leaf)	// MOVE RIGHT TILL LEAF.
	{
		curr = curr->child[curr->n];
	}
	return curr->keys[curr->n - 1];	// RETURN LAST
}

int Node::gS(int x)
{
	Node *curr = child[x+1];	// MOVE LEAF TILL LEAF
	while(!curr->leaf)
	{
		curr = curr->child[0];
	}
	return curr->keys[0];
}

void Node::filler(int x)
{
	if(x!=0 && child[x-1]->n >= t)	// IF PREV CHILD HAS MORE THAN T-1 KEYS BORROW FROM PRED
	{
		borrowP(x);
	}
	else if(x!=n && child[x+1]->n >= t) // ELSE FROM NEXT CHILD/
	{
		borrowN(x);
	}
	else
	{					// MERGE CHILD WITH ITS SIBILINGS.	
		if(x!=n)
		{
			merge(x);
		}
		else
		{
			merge(x-1);
		}
	}
	return ;
}

void Node::borrowP(int x)
{
	Node *c = child[x];
	Node *s = child[x-1];

	for(int i = c->n - 1;i>=0;i--)	// RIGHT SHIFT KEYS
	{
		c->keys[i+1] = c->keys[i];
	}

	if(!c->leaf)
	{
		for(int i=c->n;i>=0;i--)
		{
			c->child[i+1] = c->child[i];		 // RIGHT SHIFT CHILD
		}
	}

	c->keys[0] = keys[x-1];
	if(!c->leaf)			// MOVING CHILD CHILDREN AS SIB CHILDERN.
	{
		c->child[0] = s->child[s->n];
	}
	keys[x-1] = s->keys[s->n - 1];		// UPDATING COUNT
	c->n = c->n + 1;
	s->n = s->n - 1;
	return ;
}

void Node::borrowN(int x)
{
	Node *c = child[x];
	Node *s = child[x+1];

	c->keys[c->n] = keys[x];		//KEY AT X IS INSERTED TO CHILD

	if(!c->leaf)
	{
		c->child[(c->n)+1] = s->child[0];
	}
	keys[x] = s->keys[0];

	for(int i=1;i<s->n;i++)	// LEFT SHIFT KEYS
	{
		s->keys[i-1] = s->keys[i];
	}
	if(!s->leaf)			//LEFT SHIFT CHILDREN
	{
		for(int i=1;i<=s->n;i++)
		{
			s->child[i-1] =  s->child[i];
		}
	}
	c->n = c->n + 1;			// UPDATING THE COUNT
	s->n = s->n - 1;
	return ;
}

void Node::merge(int x)
{
	Node *c = child[x];
	Node *s = child[x+1];
	c->keys[t-1] = keys[x];		// PLACING CURR TO T-1 NODE

	for(int i=0;i<s->n;i++)
	{
		c->keys[i+t] = s->keys[i];		/// SHIFTING RIGHT
	}
	if(!c->leaf)
	{
		for(int i=0;i<s->n;i++)
		{
			c->child[i+t] = s->child[i];	//	CHANGING CONSECUTIVE CHILDREN	
		}
	}
	for(int i=x+2;i<=n;i++)
	{
		child[i-1] = child[i]; //SHIFTING LEFT
	}
	c->n = c->n + s->n + 1;
	n--;					// uPDATING COUNT
	return ;
}

void BTree::remover(int x)
{
	if(!root)					// eMPTY TREE
	{
		cout << "Empty Tree\n";
		return ;
	}
	else
	{
		root->remover(x);			//  REMOVE X
		if(root->n==0)
		{
			Node *temp = root;
			if(root->leaf)
			{
				root = NULL;			// IF LEAF THEN AFTER REMOVAL, null 
			}
			else
			{
				root = root->child[0]; // ELSE IT HAS CHILD.
			}
		}
		return ;
	}
}

int main()
{
	BTree r(3);		// Making B TREE of order 3.
	cout << "\nEnter the number of values to be entered: ";
	int n;
	cin >> n;
	for(int i=0;i<n;i++)
	{
		cout << "\nEnter Value: ";
		int x;
		cin >> x;
		r.insert(x);
	}
	cout << "In-Order Traversal is: ";
	r.traversal();
	cout << "\nPre-order Traversal is: ";
	r.ptraversal();
	int de;
	cout << "\nEnter the value to delete: ";
	cin >> de;
	r.remover(de);
	cout << "In-Order Traversal is: ";
	r.traversal();
	cout << "\nPre-order Traversal is: ";
	r.ptraversal();
	int h;
	cout << "\nEnter value to be searched: ";
	cin >> h;
	if(r.search(h)!=NULL)
	{
		cout << "FOUND\n";
	}
	else
	{
		cout << "NOT FOUND\n";
	}
}