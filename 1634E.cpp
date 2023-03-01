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

const int N = 2e5;
vector<array<int, 3>> adj[N];
string ans[N];
void dfs(int u){
    while(sz(adj[u])){
        auto& [iu, v, iv] = adj[u].back(); adj[u].pop_back();
        if(ans[u][iu] != '?') continue;
        ans[u][iu] = 'L'; ans[v][iv] = 'R';
        dfs(v);
    }
}
void solve(){
    int m; cin >> m;
    map<int, pi> prev;
    for(int i=0; i<m; ++i){
        int n; cin >> n;
        ans[i] = string(n, '?');
        for(int j=0; j<n; ++j){
            int a; cin >> a;
            if(prev.find(a)!=prev.end()){
                pi p = prev[a];
                adj[i].pb({j, p.ff, p.ss});
                adj[p.ff].pb({p.ss, i, j});
                prev.erase(a);
            } else{
                prev[a] = {i, j};
            }
        }
    }

    if(sz(prev)){
        cout << "NO" << nl; return;
    }

    for(int i=0; i<m; ++i){
        dfs(i);
    }
    cout << "YES" << nl;
    for(int i=0; i<m; ++i){
        cout << ans[i] << nl;
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL);

    // int t; cin >> t;
    // while(t--){
        solve();
    // }

    return 0;
}
