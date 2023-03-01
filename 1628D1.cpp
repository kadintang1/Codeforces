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

const int M = 1e9+7;
void solve(){
    int n, m, k; cin >> n >> m >> k;
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
    // -p + dp[i-1][j] = p + dp[i-1][j-1]
    // p = (dp[i-1][j] - dp[i-1][j-1]) / 2 lol
    for(int i = 1; i <= n; ++i){
        dp[i][i] = k * (ll) i;
        for(int j = 1; j < i; ++j){
            dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]) % M * (ll) inv(2, M) % M;
        }
    }
    cout << dp[n][m] % M << '\n';
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL);
    int t; cin >> t;
    FOR(i,0,t){
        solve();
    }
    return 0;
}
