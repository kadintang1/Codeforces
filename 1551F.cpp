#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <deque>
#include <tgmath.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define f first
#define s second
#define endl "\n"
const int M = 1e9+7, mxN = 105;
ll dp[mxN][mxN][mxN];
vector<int> adj[mxN];
int depth[mxN];
void dfs1(int u, int par, int d){
    depth[d]++;
    for(int v : adj[u]){
        if(v != par){
            dfs1(v, u, d+1);
        }
    }
}
void dfs0(int u, int k){
    for(int v : adj[u]){
        memset(depth, 0, sizeof(depth));
        //dfs down each branch, compute size of depths
        dfs1(v, u, 1);
        for(int i = 1; i < 101; ++i){
            dp[u][i][0] = 1;
            if(depth[i] == 0){
                break;
            }
            for(int j = k; j > 0; --j){
                dp[u][i][j] = (dp[u][i][j] + dp[u][i][j-1] * depth[i])%M;
            }
        }
    }
}
void solve(){
    int n, k; cin >> n >> k;
    for(int i = 0; i < 101; ++i){
        adj[i].clear();
    }

    for(int i = 0; i < n-1; ++i){
        int u, v; cin >> u >> v; --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if(k == 2){
        cout << n*(n-1)/2 << endl;;
        return;
    }

    memset(dp, 0, sizeof(dp));
    for(int i = 0; i < n; ++i){
        dfs0(i, k);
    }

    ll res = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            res = (res + dp[i][j][k])%M;
        }
    }

    cout << res << endl;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while(t--){
        solve();
    }    

    return 0;
}
