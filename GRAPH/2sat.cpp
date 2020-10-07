
struct two_sat
{
	int cnt, sccn, sz;
	vector<int> dfsn, sn;
	vector<bool> fin;
	vector < vector<int> > adj;
	stack <int> st;

	two_sat(int size)
	{
		sz = size;
		cnt = sccn =0;
		dfsn.resize(2 * sz + 1, 0);
		sn.resize(2 * sz + 1, 0);
		fin.resize(2 * sz + 1, 0);
		adj.resize(2 * sz + 1);
	}

	~two_sat()
	{
		dfsn.clear();
		sn.clear();
		fin.clear();
		fa(i, 0, 2 * sz + 1) adj.clear();
	}

	int toN(int idx) { return idx > sz ? idx - sz : idx + sz; }

	/*
		이어진 cnf 식은 or절이 and로 연결된다.
		cnf 식이 아닌 반대로 나타난식을 cnf식으로 바꾸는 방법은 카르노맵을 그려 maxterm expasion 을 찾아내면 된다.
		xor = (!x || !y) && (x||y)
		xnor = (!x || y) && (x||!y)
	*/

	int sdfs(int cur)
	{
		int ret = dfsn[cur] = ++cnt;
		st.push(cur);

		for (int nxt : adj[cur])
		{
			if (!dfsn[nxt]) ret = min(ret, sdfs(nxt));
			else if (!fin[nxt]) ret = min(ret, dfsn[nxt]);
		}

		if (ret == dfsn[cur])
		{
			++sccn;
			while (!st.empty())
			{
				int t = st.top(); st.pop();
				sn[t] = sccn;
				fin[t] = 1;
				if (t == cur) break;
			}			
		}

		return ret;
	}

	void add(int x, int y)
	{
		adj[toN(x)].push_back(y);
		adj[toN(y)].push_back(x);
	}

	bool is_true()
	{
		fa(i, 1, 2 * sz + 1) if (!dfsn[i]) sdfs(i);
		fa(i, 1, sz+1)
		{
			if (sn[i] == sn[toN(i)]) return false;
		}
		return true;		
	}
};
