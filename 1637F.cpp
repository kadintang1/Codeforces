#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL);
    // root tree at the max height
    // then just dp rest of the subtrees
    int n; cin >> n;
    vector<int> h(n);
    for(int i = 0; i < n; ++i){
        cin >> h[i];
    }

    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; ++i){
        int u, v; cin >> u >> v; --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int s = 0;
    for(int i = 0; i < n; ++i){
        if(h[i] > h[s]){
            s = i;
        }
    }

    long long ans = 0;
    function<int(int, int)> dfs = [&](int u, int p){
        int mx1 = 0, mx2 = 0;
        for(int v : adj[u]){
            if(v ^ p){
                int q = dfs(v, u);
                if(q > mx1){
                    swap(q, mx1);
                }
                if(q > mx2){
                    swap(q, mx2);
                }
            }
        }

        if(p == -1){
            ans += max(0, h[u] - mx1) + max(0, h[u] - mx2);
        } else{
            ans += max(0, h[u] - mx1);
            mx1 += max(0, h[u] - mx1);
        }

        return mx1;
    };

    dfs(s, -1);
    cout << ans << '\n';
    return 0;
}
