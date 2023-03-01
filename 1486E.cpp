#include <bits/stdc++.h>
using namespace std;

const int N = 1e5, INF = 1e9;
int dp[N][51][2], vis[N][51][2];
int main(){
    int n, m; cin >> n >> m;
    memset(dp, 0x3f3f3f3f, sizeof(dp));
    vector<vector<array<int, 2>>> adj(n);
    for(int i=0; i<m; ++i){
        int u, v, w; cin >> u >> v >> w; --u; --v;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    priority_queue<array<int, 4>, vector<array<int, 4>>, greater<array<int, 4>>> pq;
    // {distance, cur_node, prev_weight, parity}
    pq.push({0, 0, 0, 0}); dp[0][0][0] = 0;
    while(pq.size() > 0){
        array<int, 4> s = pq.top(); pq.pop();
        if(vis[s[1]][s[2]][s[3]]){
            continue;
        }
        vis[s[1]][s[2]][s[3]] = 1;
        int par = s[3], pre_w = s[2];
        for(auto& [v, w] : adj[s[1]]){
            if(par == 1){
                if(dp[v][w][par ^ 1] > s[0] + w * w + 2 * w * pre_w){
                    dp[v][w][par ^ 1] = s[0] + w * w + 2 * w * pre_w;
                    pq.push({dp[v][w][par ^ 1], v, w, par ^ 1});
                }
            } else{
                if(dp[v][w][par ^ 1] > s[0] + w * w){
                    dp[v][w][par ^ 1] = s[0] + w * w;
                    pq.push({dp[v][w][par ^ 1], v, w, par ^ 1});
                }
            }
        }
    }

    for(int i=0; i<n; ++i){
        int min_ans = INF;
        for(int j=0; j<=50; ++j){
            min_ans = min(min_ans, dp[i][j][0]);
        }
        if(min_ans ^ INF){
            cout << min_ans << " ";
        } else{
            cout << "-1 ";
        }
    }

    return 0;
}
