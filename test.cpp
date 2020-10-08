#include<bits/stdc++.h>
using namespace std;

#define MAX_INT 0x3f3f3f3f 
#define acc(x) setprecision(x)
#define boost ios_base::sync_with_stdio(false); cin.tie(NULL);
#define mod 1000000007

void pr(vector<long long int> &p)
{
	long long int n = p.size();
	for(int i=0;i<n;i++)
	{
		cout << p[i] << " ";
	}
	cout << "\n";
}

int  query(vector<int> &st, int l, int r, int stl, int str, int i)
{
	if(str<l || stl>r)
	{
		return 0; 
	}
	else if(l<=stl && r>=str)
	{
		return st[i];
	}
	int mid = (stl+str)/2;
	int left = query(st , l, r, stl, mid, 2*i);
	int right = query(st, l, r, mid+1, str, 2*i + 1);
	return left + right;
}

void update(vector<int> &st, int l, int r, int stl, int str, int i, int val)
{
	if(str<l || stl>r)
	{
		return ;
	}
	else if(l<=stl && r>=str)
	{
		st[i]=val;
		return;
	}
	int mid = (stl+str)/2;
	update(st, l, r, stl, mid,2*i, val);
	update(st, l, r, mid+1, str, 2*i+1, val);
	st[i] = st[2*i] + st[2*i+1];
	return ;
}

void ConstructTree(vector<int> &v, vector<int> &st, int l, int r, int i)
{
	if(l==r)
	{
		st[i] = v[l];
		return ;
	}
	int mid = (l+r)/2;
	ConstructTree(v, st, l, mid, 2*i);
	ConstructTree(v, st, mid+1, r, 2*i + 1);
	st[i] = st[2*i]+st[2*i + 1];
}

int main()
{ 
    #ifndef ONLINE_JUDGE 
        freopen("input.txt", "r", stdin);  
        //freopen("output.txt", "w", stdout); 
    #endif
    boost;
	int n;
	cin >> n;
	vector<int> v;
	for(int i=0;i<n;i++)
	{
		int k;
		cin >> k;
		v.push_back(k);
	}
	vector<int> tree(2*n, 0);
	ConstructTree(v, tree, 0, n-1, 1);
	for(int i=1;i<2*n;i++)
	{
		cout << tree[i] << " ";
	}
	cout << query(tree, 0 , 3, 0, n-1, 1) << "\n";
	update(tree, 3, 3, 0, n-1, 1, 3);
	for(int i=1;i<2*n;i++)
	{
		cout << tree[i] << " ";
	}
}
