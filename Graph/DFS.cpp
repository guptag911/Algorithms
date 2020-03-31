#include<bits/stdc++.h>
using namespace std;

#define boost ios_base::sync_with_stdio(false); cin.tie(NULL);

int nodes = 0;

int dfs(vector<vector<int> > g,bool v[],int p)
{
    nodes++;
    v[p]=true;
    //cout << p << " ";
    for(auto it=g[p].begin();it!=g[p].end();it++)
    {
        if(!v[*it])
        {
            dfs(g,v,*it);
        }
    }
    return nodes;
}


int main()
{
    boost;
    int n,m;
    cin >> n >> m;
    vector<vector<int> >G(n+1);
    bool vis[n+1];
    memset(vis,false,sizeof(vis));
    for(int i=0;i<m;i++)
    {
        int x,y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    int h;
    cin >> h;
    nodes = dfs(G,vis,h);
    cout << n - nodes << "\n";
}