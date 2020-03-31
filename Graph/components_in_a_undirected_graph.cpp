//Print Components of  A graph

#include<bits/stdc++.h>
using namespace std;

vector<int> p;

vector<int> dfs(vector<vector<int> > g,bool arr[],int i)
{
    arr[i]=true;
    p.push_back(i);
    for(auto it=g[i].begin();it!=g[i].end();it++)
    {
        if(!arr[*it])
        {
            p=dfs(g,arr,(*it));
        }
    }
    return p;
}

int main()
{
    int n,m;
    cin >> n >> m;
    vector<vector<int> > G(n+1);
    for(int i=0;i<m;i++)
    {
        int x,y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    bool vis[n+1];
    vector<vector<int> > comp;
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;i++)
    {
        vector<int> temp;
        if(!vis[i])
        {
            temp=dfs(G,vis,i);
            comp.push_back(temp);
            p.clear();
        }
    }
    for(int i=0;i<comp.size();i++)
    {
        for(int j=0;j<comp[i].size();j++)
        {
            cout << comp[i][j] << " ";
        }
        cout << "\n";
    }
}