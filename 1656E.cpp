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
#define pl pair<ll, ll>
#define vi vector<int>
#define vpi vector<pair<int, int>>
#define mi map<int, int>
#define pb push_back
#define ff first
#define ss second
#define al array<ll, 3>

template<class T> bool umin(T& a, T b){
    return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T b){
    return a<b?a=b,1:0;
}

ll inv(ll a, ll b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1;
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

void test_case(){
    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<int> deg(n), val(n);
    FOR(i,0,n-1){
        int u, v; cin >> u >> v; --u; --v;
        adj[u].pb(v);
        adj[v].pb(u);
        deg[u]++; deg[v]++;
    }

    function<void(int, int, int)> dfs = [&](int u, int p, int c){
        val[u] = deg[u] * c;
        for(auto& v : adj[u]){
            if(v ^ p){
                dfs(v, u, c * -1);
            }
        }
    };

    dfs(0, -1, 1);
    FOR(i,0,n){
        cout << val[i] << " ";
    }
    cout << nl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    FOR(i,0,t){
        test_case();
    }

    return 0;
}
