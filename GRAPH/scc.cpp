#include <bits/stdc++.h>

#define ci(t) cin>>t
#define co(t) cout<<t
#define LL long long
#define fa(i,a,b) for(int i=a;i<b;++i)
#define ty LL
using namespace std;

const int max_v = 1e5 + 7;
const int INF = 1e7 + 7;

int v, e,cnt,SN,sn[max_v],dfsn[max_v];
bool fin[max_v];
vector <int> adj[max_v];
stack <int> st;
vector < vector <int> > SCC;	

int dfs(int cur)
{
	dfsn[cur] = ++cnt;
	st.push(cur);
	int result = dfsn[cur];
	for (int next : adj[cur])
	{
		if (!dfsn[next]) result = min(result, dfs(next));
		else if (!fin[next]) result = min(result, dfsn[next]);
	}

	if (dfsn[cur] == result)
	{
		while (1) // 반복이 끝날 때 까지 방문하는 모든 노드가 scc를 이룸
		{
			
			int t = st.top();
			st.pop();
			fin[t] = true;
			sn[t] = SN;
			// curScc.push_back(t); //scc를 단위별로 구하고싶다면
			if (t == cur) break;
		}
		/* scc를 단위별로 구하고싶다면 
		sort(curScc.begin(), curScc,end()) // 정렬은 안해도 됨
		SCC.push_back(curScc);
		*/
		
		++SN;
	}
	return result;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tcnt; ci(tcnt);
	while (tcnt--)
	{
		/* init get input v,e,adj */

		ci(v >> e);
		memset(sn, 0, sizeof(sn));
		memset(dfsn, 0, sizeof(dfsn));
		memset(fin, 0, sizeof(fin));
		fa(i, 0, v) adj[i].clear();
		cnt = SN = 0;
	
		fa(i, 0, e)
		{
			int x, y;
			ci(x >> y);
			adj[x - 1].push_back(y - 1);
		}

		/* dfs for each edge */

		fa(i, 0, v)
		{
			if (!dfsn[i]) dfs(i);
		}

		// 구한 scc 정보를 가지고 문제를 푸는 부분 scc 단위로 새로운 노드를 만들었다고 생각
		// 이 예시에서는 scc 단위로 indegree 를 구함
		int sccIndegree[max_v] = { 0, };
		fa(i, 0, v)
		{
			for (int x : adj[i])
			{
				if (sn[i] != sn[x]) ++sccIndegree[sn[x]];
			}
		}
		int ans=0;
		fa(i, 0, SN)	
		{
			if (!sccIndegree[i]) ++ans;
		}
		co(ans << "\n");	
	}
	return 0;
}