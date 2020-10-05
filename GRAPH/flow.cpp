//max flow, min cut
#define INF (1 << 31) - 1
int flow_max(int start, int end){
    vector<int> link[403];
    int c[403][403], f[403][403], d[403];
    int n, p; cin >> n >> p;
    while(p--)
    {
        int a, b;
        cin >> a >> b;
        c[a][b] = 1;
        link[a].push_back(b);
        link[b].push_back(a);
    }
    int ret = 0;
    while(1){
        fill(d + 1, d + n + 1, -1);
        queue<int> q;
        q.push(start);
        while(!q.empty()){
            int x = q.front();
            q.pop();
            for(int next : link[x])
                if(c[x][next] - f[x][next] > 0 && d[next] == -1){
                    q.push(next);
                    d[next] = x;
                    if(next == end) break;
                }
        }
        if(d[end] == -1) return ret;
        int flow = INF;
        for(int i = end; i != start; i = d[i])
            flow = min(flow, f[d[i]][i] - c[d[i]][i]);
        for(int i = end; i != start; i = d[i]){
            f[d[i]][i] += flow;
            f[i][d[i]] -= flow;
        }
        ret += flow;
    }
}