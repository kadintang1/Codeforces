#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define nl "\n"
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define FORd(i, b, a) for(int i = b; i >= a; --i)
#define EACH(x, a) for (auto& x : a)
#define arr array
#define pi pair<int, int>
#define vi vector<int>
#define vpi vector<pair<int, int>>
#define mi map<int, int>
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

const int N = 200005;
int ans[N];
int cnt = 0;
pair<int, int> dp[N][2];
vector<vector<int>> adj;
void dfs(int u=0, int p=-1){
    // first do dfs where we color the current node
    // this means all the children are uncolored!
    int tot_sum = adj[u].size(), tot_color = 1;
    int tot2_sum = 1, tot2_color = 0;
    dp[u][1] = make_pair(tot_sum, tot_color);
    dp[u][0] = make_pair(tot2_sum, tot2_color);
    EACH(v, adj[u]){
        if(v^p){
            dfs(v, u);
            tot_sum += dp[v][0].ff;
            tot_color += dp[v][0].ss;
            if(dp[u][1].ss < tot_color){
                dp[u][1] = make_pair(tot_sum, tot_color);
            } else if(dp[u][1].ff > tot_sum){
                dp[u][1].ff = tot_sum;
            }

            tot2_color += max(dp[v][0].ss, dp[v][1].ss);
            if(dp[v][0].ss > dp[v][1].ss){
                tot2_sum += dp[v][0].ff;
            } else if(dp[v][0].ss == dp[v][1].ss){
                tot2_sum += min(dp[v][0].ff, dp[v][1].ff);
            } else{
                tot2_sum += dp[v][1].ff;
            }

            if(dp[u][0].ss < tot2_color){
                dp[u][0] = make_pair(tot2_sum , tot2_color);
            } else if(dp[u][0].ff > tot2_sum){
                dp[u][0].ff = tot2_sum;
            }
        }
    }
}

void dfs2(int u, int p, bool pc){
    if(pc){
        ans[u] = 1;
        EACH(v, adj[u]){
            if(v^p){
                dfs2(v, u, 0);
            }
        } 
    } else{
        if(dp[u][1].ss > dp[u][0].ss){
            ans[u] = sz(adj[u]);
        } else if(dp[u][1].ss == dp[u][0].ss){
            if(dp[u][0].ff <= dp[u][1].ff){
                ans[u] = 1;
            } else{
                ans[u] = sz(adj[u]);
            }
        } else{
            ans[u] = 1;
        }

        EACH(v, adj[u]){
            if(v^p){
                dfs2(v, u, ans[u] == sz(adj[u]));
            }
        }
    }
}

void solve(){
    int n; cin >> n;
    // dp[i][p] ? p = this node is satisfied (1) or not (0)
    // dp[i][p] = {S, K}, where S is sum of node values, K is # satisfied nodes, 
    adj.resize(n);
    FOR(i,0,n-1){
        int u,v; cin >> u >> v; --u; --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    if(n == 2){
        cout << "2 2\n1 1" << nl; return;
    }

    dfs();
    if(dp[0][0].ss < dp[0][1].ss){
        cout << dp[0][1].ss << " " << dp[0][1].ff << nl;
    } else if(dp[0][0].ss == dp[0][1].ss){
        cout << dp[0][0].ss << " " << min(dp[0][0].ff, dp[0][1].ff) << nl;
    } else{
        cout << dp[0][0].ss << " " << dp[0][0].ff << nl;
    }

    dfs2(0, -1, 0);
    FOR(i,0,n){
        cout << ans[i] << " ";
    }
    cout << nl;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL);
    solve();
    return 0;
}
