// AVL Tree Implementation Insertion and Deletion! C++

#include<bits/stdc++.h>
using namespace std;

#define boost ios_base::sync_with_stdio(false); cin.tie(NULL);

struct Node
{
    int val;
    Node *left, *right;
    int height;
    Node(int x): val(x), left(NULL), right(NULL), height(1) {};
};

int ht(Node* t)
{
    if(t==NULL)
    {
        return 0;
    }
    else
    {
        return t->height;
    }
}

Node* left_rotation(Node* p)
{
    Node* b = p->right;
    Node* c = b->left;
    b->left = p;
    p->right = c;

    p->height = max(ht(p->left),ht(p->right)) + 1;
    b->height = max(ht(b->left),ht(b->right)) + 1;

    return b;
}

Node* right_rotation(Node *p)
{
    Node* b = p->left;
    Node* c = b->right;
    b->right = p;
    p->left = c;

    p->height = max(ht(p->left),ht(p->right)) + 1;
    b->height = max(ht(b->left),ht(b->right)) + 1;

    return b;
}

Node* insert(Node* r,int x)
{
    Node* temp = new Node(x);
    if(r==NULL)
    {
        return temp;
    }
    else
    {
        if(x>r->val)
        {
            r->right = insert(r->right,x);
        }
        else
        {
            r->left  = insert(r->left, x);
        }
        r->height = max(ht(r->left), ht(r->right)) + 1;
        int bal = ht(r->left) - ht(r->right);
        // LL
        if(bal>1 && x<r->left->val)
        {
            return right_rotation(r);
        }
        // LR
        if(bal>1 && x>r->left->val)
        {
            r->left = left_rotation(r->left);
            return right_rotation(r);
        }
        // RR
        if(bal<-1 && x>r->right->val)
        {
            return left_rotation(r);
        }
        // RL
        if(bal<-1 && x<r->right->val)
        {
            r->right = right_rotation(r->right);
            return left_rotation(r);
        }
        return r;
    }
}

Node* getMin(Node* r)
{
    Node* p = NULL;
    while(r!=NULL)
    {
        p = r;
        r = r->left;
    }
    return p;
}

int getBal(Node* p)
{
    if(p==NULL)
    {
        return 0;
    }
    else
    {
        return ht(p->left)-ht(p->right);
    }
}

Node* deleteNode(Node* r, int x)
{
    if(r==NULL)
    {
        //delete r;
        return r;
    }
    else
    {
        if(x>r->val)
        {
            r->right = deleteNode(r->right, x);
        }
        else if(x<r->val)
        {
            r->left = deleteNode(r->left, x);
        }
        else
        {
            if(r->left==NULL || r->right==NULL)
            {
                Node* temp = r->left?r->left:r->right;
                if(temp==NULL)
                {
                    temp = r;
                    r = NULL;
                }
                else
                {
                    r = temp;
                }
                //delete temp;
            }
            else
            {
                Node* q = getMin(r->right);
                r->val = q->val;
                r->right = deleteNode(r->right, q->val);
            }
        }
        if(r==NULL)
        {
            return r;
        }
        r->height = max(ht(r->left),ht(r->right)) + 1;
        int bal = ht(r->left) - ht(r->right);
        // LL
        if(bal>1 && getBal(r->left)>=0)
        {
            return right_rotation(r);
        }
        // LR
        if(bal>1 && getBal(r->left)<0)
        {
            r->left = left_rotation(r->left);
            return right_rotation(r);
        }
        // RR
        if(bal<-1 && getBal(r->right)<=0)
        {
            return left_rotation(r);
        }
        // RL
        if(bal<-1 && getBal(r->right)>0)
        {
            r->right = right_rotation(r->right);
            return left_rotation(r);
        }
        return r;
    }
}

void preorder(Node* r)
{
    if(r==NULL)
    {
        return ;
    }
    else
    {
        cout << r->val << " ";
        preorder(r->left);
        preorder(r->right);
    }
}

void inorder(Node* r)
{
    if(r==NULL)
    {
        return ;
    }
    else
    {
        inorder(r->left);
        cout << r->val << " ";
        inorder(r->right);
    }
}
int main()
{
    //boost;
    Node* root = NULL;
    cout << "Enter the number of Nodes: ";
    int n;
    cin >> n;
    for(int i=0;i<n;i++)
    {
        int k;
        cin >> k;
        root = insert(root, k);
    }
    cout << "\n Pre-order Traversal of AVL tree is -> ";

    preorder(root);
    cout << "\n In-order Traversal of AVL tree is -> ";
    inorder(root);

    root = deleteNode(root, 30);
    cout << "\n AVL Tree after deleting 30 is -> ";
    preorder(root);
}
