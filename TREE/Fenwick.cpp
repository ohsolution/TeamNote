#include <bits/stdc++.h>
#define LL long long
#define ty LL
#define fa(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class Fenwick
{
public:
    vector<ty> node;
	vector<ty> arr;
	int size;

	Fenwick(int sz,int d=0)
	{
		size = sz+1;
        node.resize(size,d);
        arr.resize(size,d);
		fa(i, 1, size)
		{
			int x; cin >> x;
			arr[i] = x;
			update(i, x);
		}
	}

	~Fenwick()
	{
        node.clear();
        arr.clear();
	}

	void update(int idx, int diff)
	{
		for(;idx<size;idx+=(idx&-idx)) node[idx]+=diff;
	}

	ty sum(int idx)
	{
		ty ret = 0;
		for (; idx; idx -= (idx & -idx)) ret += node[idx];
		return ret;
	}
	void query(int tp, int x, int y)
	{
		if (tp & 1)
		{
			update(x, y - arr[x]);
			arr[x] = y;
		}
		else cout << sum(y) - sum(x - 1)<<"\n";		
	}
};

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m, k; cin >> n >> m >> k;
	m += k;
	Fenwick* fen = new Fenwick(n);
	fa(i, 0, m)
	{
		int tp, x, y; cin>>tp >> x >> y;
		fen->query(tp, x, y);	
	}

	delete fen;

	return 0;
}
