#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { 
    return os << '(' << p.first << ", " << p.second << ')'; 
}

template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { 
    os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; 
}

const int N = 2e5 + 5;
int up[N][19], tin[N], tout[N], h[N];
int main(){ 
    ios::sync_with_stdio(0); cin.tie(NULL);

    int n, t = 0; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; ++i){
        int u, v; cin >> u >> v; --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    function<void(int, int)> dfs = [&](int u, int p) {
        tin[u] = ++t;
        up[u][0] = p;
        for(int i = 1; i <= 18; ++i){
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        h[u] = (p == -1 ? 0 : h[p] + 1);
        for(int v : adj[u]){
            if(v != p){
                dfs(v, u);
            }
        }
        tout[u] = ++t;
    };

    function<bool(int, int)> is_ancestor = [&](int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    };

    function<int(int, int)> lca = [&](int u, int v){
        if(is_ancestor(u, v)){
            return u;
        }
        if(is_ancestor(v, u)){
            return v;
        }
        int j = u;
        for(int i = 18; ~i; --i){
            if(!is_ancestor(up[j][i], v)){
                j = up[j][i];
            }
        }
        return up[j][0];
    };

    dfs(0, 0);

    int q; cin >> q;
    for(int z = 0; z < q; ++z) {
        int k; cin >> k;
        vector<int> v(k);
        for(int i = 0; i < k; ++i) {
            cin >> v[i]; --v[i];
        }

        if(k == 1){
            cout << "YES\n"; continue;
        }

        vector<array<int, 2>> ord(k);
        for(int i = 0; i < k; ++i) {
            ord[i] = {h[v[i]], v[i]};
        }

        sort(ord.begin(), ord.end());
        int U = ord[k - 1][1], V = -1;
        for(int i = k - 2; ~i; --i){
            int W = ord[i][1];
            if(!is_ancestor(W, U)) {
                V = W; break;
            }
        }

        if(V == -1){
            V = ord[0][1];
        }

        int ANC = lca(U, V);
        bool path_exists = true;
        for(int i = 0; i < k; ++i){
            int W = v[i];
            if(W == U || W == V) {
                continue;
            }
            if(!is_ancestor(ANC, W) || (!is_ancestor(W, U) && !is_ancestor(W, V))){
                path_exists = false; break;
            }    
        }

        if(path_exists) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
