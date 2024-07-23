#include<bits/stdc++.h>
using namespace  std;

class Node {
    public:
    int val;
    Node* left;
    Node* right;

    Node(int x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};

class Tree {
private:
    Node* root;
public:
    Tree() {
        root = NULL;
    }

    Node* getRoot() {
        return root;
    }

    void insert(int x) {
        Node* temp = new Node(x);
        if (root==NULL) {
            root = temp;
        } else {
            queue<Node*> q;
            q.push(root);
            while(!q.empty()) {
                Node* p = q.front();
                q.pop();
                if (p->val==-1) {
                    continue;;
                }
                if (p->left == NULL) {
                    p->left = temp;
                    break;
                } else {
                    q.push(p->left);
                }
                if (p->right==NULL) {
                    p->right = temp;
                    break;
                } else {
                    q.push(p->right);
                }
            }
        }
    }

    void preOrder(Node* x) {
        if (x==NULL) {
            return ;
        }
        cout << x->val << " ";
        preOrder(x->left);
        preOrder(x->right);
    }

    void postOrder(Node* x) {
        if (x==NULL) {
            return ;
        }
        postOrder(x->left);
        postOrder(x->right);
        cout << x->val << " ";
    }

    void inOrder(Node* x) {
        if (x==NULL) {
            return ;
        }
        inOrder(x->left);
        cout << x->val << " ";
        inOrder(x->right);
    }

    int nodesCount(Node* x) {
        if (x==NULL || x->val==-1) {
            return 0;
        }
        int leftCount = nodesCount(x->left);
        int rightCount = nodesCount(x->right);
        return leftCount + rightCount + 1;
    }

    int nodesSum(Node* x) {
        if (x==NULL || x->val==-1) {
            return 0;
        }
        int leftSum = nodesSum(x->left);
        int rightSum = nodesSum(x->right);
        return leftSum + rightSum + x->val;
    }

    int height(Node* x) {
        queue<Node*> q;
        q.push(x);
        q.push(NULL);
        int level = 1;
        while(q.size()!=1) {
            Node* p = q.front();
            q.pop();
            if (p==NULL) {
                level++;
                q.push(NULL);
            } else if (p->val==-1) {
                continue;
            } else {
                if (p->left!=NULL) {
                    q.push(p->left);
                }
                if (p->right!=NULL) {
                    q.push(p->right);
                }
            }
        }
        return level;
    }

    struct TreeInfo {
        int h;
        int d;
        TreeInfo(int a, int b): h(a), d(b) {};
    };

    TreeInfo* optimizedDiameter(Node* x) {
        if (x==NULL || x->val==-1) {
            return new TreeInfo(0, 0);
        }
        TreeInfo* left = optimizedDiameter(x->left);
        TreeInfo* right = optimizedDiameter(x->right);
        int d = max(left->d, max(right->d, left->h + right->h + 1));
        int h = max(left->h, right->h)+1;
        return new TreeInfo(h, d);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Tree* tree = new Tree();
    tree->insert(5);
    tree->insert(4);
    tree->insert(3);
    tree->insert(2);
    tree->insert(1);
    tree->insert(-1);
    tree->insert(-1);
    tree->insert(4);

    // tree->inOrder(tree->getRoot());
    // cout << endl;
    // tree->preOrder(tree->getRoot());
    // cout << endl;
    // tree->postOrder(tree->getRoot());
    // cout << endl;
    // cout << tree->nodesCount(tree->getRoot()) << "\n";
    // cout << tree->nodesSum(tree->getRoot()) << "\n";
    cout << tree->optimizedDiameter(tree->getRoot())->h << "\n";
}