//********************************//
//	 	   SEGMENT TREE			  //
//********************************// 

#include<bits/stdc++.h>
using namespace std;

void buildTree(vector<int> &a, vector<int> &t, int i, int s, int e) {
	if (s>e) {
		return ;
	} else if (s==e) {
		t[i] = a[s];
		return ;
	} else {
		int mid = (s+e)/2;
		buildTree(a, t, 2*i, s, mid);
		buildTree(a, t, 2*i+1, mid+1, e);
		t[i] = min(t[2*i], t[2*i+1]);
		return ;
	}
}

int query(vector<int> &t, int i, int s, int e, int qs, int qe) {
	//No Overlap
	if (qe<s || qs > e) {
		return INT_MAX;
	} 
	//Complete Overlap
	if (qs<=s && qe>=e) {
		return t[i];
	}
	//Partial Overlap
	int mid = (s+e)/2;
	int l = query(t, 2*i, s, mid, qs, qe);
	int r = query(t, 2*i+1, mid+1, e, qs, qe);
	return min(l, r);
}

void update(vector<int> &t, int i, int s, int e, int p, int val) {
	if (p<s || p>e) {
		return ;
	} else  if (p==s && p==e) {
		t[i] = val;
		return ;
	} else {
		int mid = (s+e)/2;
		update(t, 2*i, s, mid, p, val);
		update(t, 2*i+1, mid+1, e, p, val);
		t[i] = min(t[2*i], t[2*i+1]);
		return ;
	}
}

void updateRange(vector<int> &t, int i, int s, int e, int qs, int qe, int val) {
	// No Overlap
	if (qs>e || qe<s) {
		return ;
	} else if (s == e) {
		t[i]+=val;
		return ;
	} else {
		int mid = (s+e)/2;
		updateRange(t, 2*i, s, mid, qs ,qe, val);
		updateRange(t, 2*i+1, mid+1, e, qs ,qe, val);
		t[i] = min(t[2*i], t[2*i+1]);
		return ;
	}
}

int main()
{
	#ifndef ONLINE_JUDGE
	    freopen("input.txt", "r", stdin);
	#endif

	int n;
	cin >> n;
	vector<int> v;
	for(int i=0;i<n;i++)
	{
		int k;
		cin >> k;
		v.push_back(k);
	}
	vector<int> sTree(4*n + 1, INT_MAX);
	buildTree(v, sTree, 1, 0, n-1);
	updateRange(sTree, 1, 0, n-1, 4, 5, 2);
	int q;
	cin >> q;
	while(q--) {
		int x, y;
		cin >> x >> y;
		cout << query(sTree, 1, 0, n-1, x, y) << "\n";
	}
}