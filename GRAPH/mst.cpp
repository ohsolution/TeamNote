#include <bits/stdc++.h>

#define fa(i,a,b) for(int i=a;i<b;++i)
#define setl pair<int,int>

using namespace std;

const int max_v = 1e4+7;

bool visit[max_v];
vector<setl> adj[max_v];
int v,e;

struct cmp { bool operator()(setl a, setl b) {return a.second > b.second;}};

int prim(int sp)
{
    priority_queue<setl,vector<setl>,cmp > pq;
    
    visit[sp] = true;
    
    for(auto x : adj[sp]) pq.push(x);

    int ret = 0;

    while(!pq.empty())
    {
        setl cur;
        do
        {
            cur = pq.top(); pq.pop();
        }while(!pq.empty() && visit[cur.first]);
        
        if(visit[cur.first]) break;

        visit[cur.first] = true;
        
        ret += cur.second;

        for(auto x : adj[cur.first]) pq.push(x);
    }
    return ret;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> v >> e;

    fa(i,0,e)
    {
        int x,y,cost;
        cin >> x >> y >> cost;
        adj[x].push_back({y,cost});
        adj[y].push_back({x,cost});
    }

    cout << prim(1);

	return 0;
}
