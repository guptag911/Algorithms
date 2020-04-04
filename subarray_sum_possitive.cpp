// Contigious Subarray with a given Sum.....*****ONLY POSSITIVE NUMBERS IN THE ARRAY*********

//IDEA:::->  To keep two pointers l and r and as the array is possitive only so add to curr_sum.If curr_sum is same as required sum
//           return l and r else if greater then jab tak not less remove v[l] and increment l..This changes l and r 
//			 and helps us in  getting the required answer....

// Time Complexity --> O(n);   Space Complexity --> O(1);; 

#include<bits/stdc++.h>
using namespace std;

#define precision(x) setprecision(x)
#define boost ios_base::sync_with_stdio(false);	cin.tie(NULL);

int main()
{
	boost;
	int n,sum;
	cin >> n >> sum;
	vector<int> v;
	for(int i=0;i<n;i++)
	{
		int k;
		cin >> k;
		v.push_back(k);
	}
	int l=0,r=0;
	int curr_sum=0;
	for(int i=0;i<n;i++)
	{
		if(curr_sum>sum)
		{
			while(curr_sum>sum && l<r)
			{
				curr_sum-=v[l];
				l++;
			}
		}
		if(curr_sum==sum && (r-l)>0)
		{
			cout << l+1 << " " << r << "\n";
			return 0;  
		}
		curr_sum+=v[i];
		r++;
	}
	cout << "-1\n";
}