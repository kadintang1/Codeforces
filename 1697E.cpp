#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define nl "\n"
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define FORd(i, b, a) for(int i = b; i >= a; --i)
#define EACH(x, a) for (auto& x : a)
#define arr array
#define pi pair<int, int>
#define vpi vector<pair<int, int>>
#define vi vector<int>
#define vl vector<ll>
#define pb push_back
#define ff first
#define ss second

template<class T> bool umin(T& a, T b){
    return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T b){
    return a<b?a=b,1:0;
}

ll inv(ll a, ll b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1LL;
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

const int N = 105, M = 998244353, INF = 2e9;
ll d[N][N], dp[N][N], c[N], fact[N], rfact[N];
void test_case(){
    int n; cin >> n;
    vector<arr<int, 2>> pts(n);
    for(int i = 0; i < n; ++i){
        cin >> pts[i][0] >> pts[i][1];
    }

    fact[0] = 1, rfact[0] = 1;
    for(int i = 1; i <= n; ++i){
        fact[i] = fact[i - 1] * i % M;
        rfact[i] = rfact[i - 1] * inv(i, M) % M;
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(i == j){
                d[i][j] = INF; continue;
            }
            d[i][j] = abs(pts[i][0] - pts[j][0]) + abs(pts[i][1] - pts[j][1]);
        }
    }

    vector<vector<int>> adj(n);
    for(int i = 0; i < n; ++i){
        int min_dist = *min_element(d[i], d[i] + n);
        for(int j = 0; j < n; ++j){
            if(min_dist == d[i][j]){
                adj[i].pb(j);
            }
        }
    }

    vector<int> t, comp_sz, vis(n);
    function<void(int)> dfs1 = [&](int u){
        vis[u] = 1; t.pb(u);
        for(auto& v : adj[u]){
            if(!vis[v]){
                dfs1(v);
            }
        }
    };

    function<void(int, int)> dfs2 = [&](int u, int id){
        c[u] = id;
        for(auto& v : adj[u]){
            if(!c[v]){
                dfs2(v, id);
            }
        }
    };

    for(int i = 0, id = 1; i < n; ++i, ++id){
        if(c[i]) continue;
        t.clear(); dfs1(i);
        fill(all(vis), 0);
        int min_dist = *min_element(d[i], d[i] + n);
        bool bad = 0;
        for(int x = 0; x < sz(t); ++x){
            for(int y = x + 1; y < sz(t); ++y){
                int u = t[x], v = t[y];
                if(d[u][v] != min_dist){
                    bad = 1;
                }
            }
        }

        if(bad){
            c[i] = id;
            comp_sz.pb(1);
        } else{
            dfs2(i, id);
            comp_sz.pb(sz(t));
        }
    }

    dp[0][0] = 1;
    int m = sz(comp_sz);
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            if(!dp[i][j]) continue;
            dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % M;
            if(comp_sz[i] > 1){
                dp[i + 1][j + comp_sz[i]] = (dp[i + 1][j + comp_sz[i]] + dp[i][j]) % M;
            }
        }
    }

    ll ans = 0;
    for(int i = 1; i <= n; ++i){
        ans = (ans + dp[m][i] * fact[n] % M * rfact[n - i] % M) % M;
    }

    cout << ans << nl;
}

int main() {
    // int t; cin >> t;
    // FOR(i,0,t){
        test_case();
    // }
    return 0;
}
