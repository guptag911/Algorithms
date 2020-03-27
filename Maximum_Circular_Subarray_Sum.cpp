//Maximum Sum of a circular array by modifying Kladane's Algorithm..

#include<bits/stdc++.h>
using namespace std;

#define boost ios_base::sync_with_stdio(false);	cin.tie(NULL);

int main()
{
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
	int curr_max=v[0],curr_min=v[0],total=v[0],max_sum=v[0],min_sum=v[0];
	for(int i=1;i<n;i++)
	{
		curr_max=max(curr_max+v[i],v[i]);
		max_sum=max(max_sum,curr_max);
		curr_min=min(curr_min+v[i],v[i]);
		min_sum=min(min_sum,curr_min);
		total+=v[i];
	}
	if(max_sum>0)
	{
		cout << max(max_sum,total-min_sum) << "\n";
	}
	else
	{
		cout << max_sum << "\n";
	}
}
