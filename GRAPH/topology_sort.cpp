//Topology Sort
void Topology_Sort(){
    vector<int> build[503];
    queue<int> q;
    int cost[503], wait_time[503], level[503];
    int n; cin >> n;
    for(int i = 1; i <= n; i++){
        int tmp;
        cin >> tmp;
        cost[i] = tmp;
        while(1){
            cin >> tmp;
            if(tmp == -1) break;
            level[i]++;
            build[tmp].push_back(i);
        }
        if(level[i] == 0)
            q.push(i);
    }
    while(!q.empty()){
        int con = q.front();
        q.pop();
        for(auto next : build[con]){
            wait_time[next] = max(wait_time[next], wait_time[con] + cost[con]);
            if(--level[next] == 0)
                q.push(next);
        }
    }
    for(int i = 1; i <= n; i++)
        cout << wait_time[i] + cost[i] << endl;
}