//Floyd Warshall
#define SIZE 10000
#define INF (1 << 31) - 1
void Floyd_Warshall(){
    int dist[SIZE][SIZE];
    int n; cin >> n;
    for(int i = 1; i <= n; i++)
        fill(dist[i] + 1, dist[i] + n + 1, INF);
    
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}