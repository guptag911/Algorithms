#include<bits/stdc++.h>
using namespace std;

class NestedList {
    private:
    bool isInt;
    int val;
    vector<NestedList> list;
    
    public:
    
    NestedList(int v) {
        val = v;
        isInt = true;
    }
    
    NestedList(vector<NestedList> l) {
        list = l;
        isInt = false;
    }
    
    bool isNumber() {
        return isInt;
    }
    
    int getInteger() {
        return val;
    }
    
    vector<NestedList> getList() {
        return list;
    }
    
    int getListSize() {
        return list.size();
    }
};


void printer(vector<NestedList> l) {
    for(auto i: l) {
        if (i.isNumber()) {
            cout << i.getInteger() << " ";
        } else {
            cout << "[ ";
            printer(i.getList());   
            cout <<"] ";
        }        
    }
}

int weightSumibfs(vector<NestedList> l) {
    queue<NestedList> q;
    int d = 1;
    for(auto i: l) {
        q.push(i);
    }
    int sum = 0;
    while(!q.empty()) {
        int s = q.size();
        while(s--) {
            NestedList p = q.front();
            q.pop();
            if (p.isNumber()) {
                sum += p.getInteger()*d;
            } else {
                for(auto j: p.getList()) {
                    q.push(j);
                }
            }
        }
        d++;
    }
    return sum;
} 

int weightSumidfs(vector<NestedList> l, int d) {
    int sum = 0;
    for(auto p: l) {
        if (p.isNumber()) {
            sum+=p.getInteger()*d;
        } else {
            sum+=weightSumidfs(p.getList(), d+1);
        }
    }
    return sum;
}

int weightSumii(vector<NestedList> l) {
    queue<NestedList> q;
    for(auto &i: l) {
        q.push(i);
    }
    
    int ans = 0;
    int curr_sum = 0;
    while(!q.empty()) {
        int size = q.size();
        while(size--) {
            auto p = q.front();
            q.pop();
            if (p.isNumber()) {
                curr_sum += p.getInteger();
            } else {
                for(auto &r: p.getList()) {
                    q.push(r);
                }
            }
        }
        ans += curr_sum;
    }
    return ans;
}


int main() {
    
    NestedList n1 = NestedList(1);
    NestedList n2 = NestedList(2);
    NestedList n3 = NestedList(3);
    NestedList n4 = NestedList(4);
    NestedList n5 = NestedList({n2,n3});
    
    vector<NestedList> f = {n1, n5, n3, n4, n5};
    printer(f);
    
    cout << weightSumidfs(f, 1) << "\n";
    cout << weightSumibfs(f) << "\n";
    
    cout << weightSumii(f) << "\n";
    
}
