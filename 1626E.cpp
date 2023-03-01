#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define nl "\n"
#define trav(a, x) for(auto &a : x)
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define ROF(i, b, a) for(int i = b; i >= a; --i)
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

const int N = 3e5;
int c[N], ok[N], sum[N], par[N], vis[N];
vector<vector<int>> adj, adj2;
void dfs2(int u){
    ok[u] = 1; vis[u] = 1;
    for(int v : adj2[u]){
        if(!ok[v]&&!vis[v]){
            dfs2(v);
        }
    }
}

void dfs(int u=0, int p=-1){
    par[u] = p;
    for(int v : adj[u]){
        if(v^p){
            dfs(v,u);
            sum[u] += sum[v];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    FOR(i,0,n){
        cin >> c[i]; sum[i] += c[i];
    }
    adj.resize(n);
    adj2.resize(n);

    FOR(i,0,n-1){
        int u, v; cin >> u >> v; --u; --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs();
    FOR(u,0,n){
        trav(v, adj[u]){
            if(u==par[v]){
                if(c[u]||sum[0]-sum[v]>1){
                    adj2[u].pb(v);
                }
            } else{
                if(c[u]||sum[u]>1){
                    adj2[u].pb(v);
                }
            }
        }
    }

    queue<int> q;
    FOR(i,0,n){
        if(c[i]&&!vis[i]){
            dfs2(i);
        }
    }

    FOR(i,0,n){
        cout << ok[i] << " ";
    }

    return 0;
}
