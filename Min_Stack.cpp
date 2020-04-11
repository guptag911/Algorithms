//Get Minimum Element from stack every time..O(1) time and O(1) space;;
//Idea---> We will be storing elemenents in stack always minimun ..and keeping the current minimum in minElem..Let say an elemt come
//  whcih is less than minELem..i.e now we will push 2*x - minElem in the stack..and update the minElem..As 2*x-minELem is alwasy less tham
// x and whe we are poping elements and we found an elemnent less than minElem we found there is some analomy..So Thats how this
// this logic works..

#include<bits/stdc++.h>
using namespace std;

#define boost ios_base::sync_with_stdio(false); 	cin.tie(NULL);

stack<long long int> stk;
int minElem = INT_MAX;

void _push(long long int x)
{
	if(x>minElem)
	{
		stk.push(x);
	}
	else
	{
		stk.push(2*x - minElem);
		minElem = x;
	}
}

void _pop()
{
	if(stk.empty())
	{
		cout << "Nothing to pop\n";
	}
	else
	{
		if(stk.top()<minElem)
		{
			minElem = 2*minElem - stk.top();
		}
		stk.pop();
	}
}

int _getMin()
{
	if(stk.empty())
	{
		return INT_MIN;
	}
	else
	{
		return minElem;
	}
}

int _seek()
{
	if(stk.empty())
	{
		return 0;
	}
	else
	{
		if(stk.top()>minElem)
		{
			return stk.top();
		}
		else
		{
			return 2*minElem - stk.top();
		}
	}
}

int main()
{
	boost;
	_push(-2);
	_push(0);
	_push(-3);
	cout << _getMin() << "\n";
	_pop();
	cout << _seek() << "\n";
	cout << _getMin() << "\n";
}
