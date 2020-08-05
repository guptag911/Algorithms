#include<bits/stdc++.h>
using namespace std;

#define MAX_INT 0x3f3f3f3f 
#define acc(x) setprecision(x)
#define boost ios_base::sync_with_stdio(false); 	cin.tie(NULL);

struct Trie
{
	Trie* arr[26];
	bool eoc;
	Trie(): eoc(false){};
};

Trie* Node()
{
	Trie* temp = new Trie();
	for(int i=0;i<26;i++)
	{
		temp->arr[i]=NULL;
	}
	return temp;
}

void insert(string p, Trie* r)
{
	Trie* t = r;
	for(int i=0;i<p.length();i++)
	{	
		int q = p[i]-'a';
		if(t->arr[q]==NULL)
		{
			t->arr[q] = Node();
		}
		t = t->arr[q];
	}
	t->eoc = true;
}

bool search(string p, Trie* r)
{
	Trie* temp = r;
	for(int i=0;i<p.length();i++)
	{
		int q = p[i]-'a';
		if(temp->arr[q]==NULL)
		{
			return false;
		}
		else
		{
			temp = temp->arr[q];
		}
	}
	return temp->eoc;
}

int main()
{
	boost;	
	int n;
	cin >> n;
	Trie* root = Node();
	for(int i=0;i<n;i++)
	{
		string s;
		cin >> s;
		insert(s, root);
	}
	if(search("abha", root))
	{
		cout << "Y\n";
	}
	else
	{
		cout << "N\n";
	}
	return 0;
}


