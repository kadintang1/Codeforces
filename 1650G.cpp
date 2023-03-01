#include <bits/stdc++.h>
using namespace std;

const int M = 1e9+7, INF = 1e9;
void test_case(){
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    int s, t; cin >> s >> t; --s; --t;
    for(int i = 0; i < m; ++i){
        int u, v; cin >> u >> v; --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> d(n, INF), d2(n, INF), vis_count(n); d[s] = 0;
    vector<vector<int>> ways(2, vector<int>(n));
    ways[0][s] = 1;
    queue<tuple<int, int, int>> q;
    q.push(make_tuple(s, 0, 0));
    while(q.size()){
        auto [u, w, x] = q.front(); q.pop();
        for(auto& v : adj[u]){
            if(w <= d[v]){
                d[v] = min(d[v], w+1);
                ways[w-d[v]+1][v] = (ways[w-d[v]+1][v]+ways[x][u])%M;
                if(!vis_count[v]||(vis_count[v]==1&&d[v]==w)){
                    q.push(make_tuple(v, w+1, vis_count[v]++));
                }
            }
        }
    }

    cout << (ways[0][t]+ways[1][t])%M << '\n';
}

int main(){ 
    ios::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while(t--){
        test_case();
    }

    return 0;
}
