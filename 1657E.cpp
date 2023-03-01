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

const int M = 998244353, N = 251;
ll dp[N][N], binom[N][N], pw[N][N*N];
int main(){
    ios::sync_with_stdio(0); cin.tie(NULL);
    // STAR MST <-> w(u,v) >= max(w(1,u), w(1,v))
    // dp the rest
    int n, K; cin >> n >> K;
    for(int i=0; i<=n; ++i){
        for(int j=binom[i][0]=1; j<=i; ++j){
            binom[i][j]=(binom[i-1][j]+binom[i-1][j-1])%M;
        }
    }

    for(int i=0; i<=K; ++i){
        for(int j=pw[i][0]=1; j<=n*n; ++j){
            pw[i][j]=i*pw[i][j-1] % M;
        }
    }

    dp[0][1] = 1;
    for(int i=0; i<K; ++i){
        for(int j=0; j<=n; ++j){
            for(int k=0; j+k<=n; ++k){
                int exp = k*(k-1)/2 + k*(j-1);
                dp[i+1][j+k]+=dp[i][j]*binom[n-j][k]%M * pw[K-i][exp]%M;

                // this is b/c of rocket3989 >:|
                dp[i+1][j+k]%=M;
            }
        }
    }

    cout << dp[K][n] << nl;
    return 0;
}
