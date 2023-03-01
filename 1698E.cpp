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

ll inv(ll a, ll b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1LL;
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

const int M = 998244353;
void test_case(){
    int n, s; cin >> n >> s;
    vector<arr<int, 2>> v(n);
    vector<bool> vis(n);
    for(int i = 0; i < n; ++i){
        cin >> v[i][0]; --v[i][0];
    }

    for(int i = 0; i < n; ++i){
        cin >> v[i][1]; --v[i][1];
        if(v[i][1] >= 0){
            vis[v[i][1]] = 1;
        }
    }

    vector<int> m;
    for(int i = 0; i < n; ++i){
        if(!vis[i]){
            m.pb(i);
        }
    }

    int max_gap = 0;
    for(int i = 0; i < n; ++i){
        if(v[i][1] == -2) continue;
        max_gap = max(max_gap, v[i][0] - v[i][1]);
    }

    if(max_gap > s){
        cout << 0 << nl; return;
    }

    vector<int> c;
    for(int i = 0; i < n; ++i){
        if(v[i][1] == -2){
            c.push_back(m.end() - lower_bound(all(m), v[i][0] - s));
        }
    }

    sort(all(c));
    ll ans = 1;
    for(int i = 0; i < sz(c); ++i){
        ans = (ans * (c[i] - i)) % M;
    }
    cout << ans << nl;
}

int main() {
    int t; cin >> t;
    FOR(i,0,t){
        test_case();
    }
    return 0;
}
