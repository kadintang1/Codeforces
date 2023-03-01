#include <bits/stdc++.h>
#include <vector>
using namespace std;

typedef long long ll;
#define nl "\n"
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define FORd(i, b, a) for(int i = b; i >= a; --i)
#define ROF(i, b, a) for(int i = b; i >= a; --i)
#define trav(a, x) for(auto &a : x)
#define pi pair<int, int>
#define pb push_back
#define ff first
#define ss second

template<class T> bool umin(T& a, T b){
    return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T b){
    return a<b?a=b,1:0;
}

template<class T> T inv(T a, T b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1;
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

void solve(){
    int n; cin >> n;
    vector<int> d(n);
    vector<vector<int>> adj(n);
    for(int i=0; i<n-1; ++i){
        int u, v; cin >> u >> v; --u; --v;
        adj[u].pb(v); adj[v].pb(u);
    }

    function<int(int, int, int)> dfs = [&](int u, int p, int cur_d){
        int h1 = cur_d, h2 = cur_d;
        for(auto& v : adj[u]){
            if(v^p){
                int q = dfs(v,u,cur_d+1);
                if(q > h1){
                    h2 = h1;
                    h1 = q;
                } else if(q > h2){
                    h2 = q;
                }
            }
        }

        int x = min(h1, h2)-1;
        if(x >= 0){
            d[x] = max(d[x], h1+h2-2*cur_d+1);
        }
        return h1;
    };

    int max_h = dfs(0,-1,0);
    for(int i=n-2; ~i; --i){
        d[i] = max(d[i], d[i+1]);
    }

    int ans = 0;
    for(int i=1; i<=n; ++i){
        while(ans < max_h && d[ans]/2 + i > ans){
            ++ans;
        }
        cout << ans << " ";
    }
    cout << nl; 
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    FOR(i,0,t){
        solve();
    }
}
