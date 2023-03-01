#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define nl "\n"
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
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

const int M = 998244353;
ll binom[5005][5005];
void solve(){
    int n, k; cin >> n >> k;
    for(int i=0; i<=n; ++i){
        for(int j=0; j<=i; ++j){
            if(j == 0 || j == i){
                binom[i][j] = 1; continue;
            }
            binom[i][j] = (binom[i-1][j] + binom[i-1][j-1])%M;
        }
    }

    string s; cin >> s;
    int sum = 0;
    trav(x, s) sum += x == '1';
    if(!k||sum<k){
        cout << 1 << nl; return;
    }
    ll res = 0;
    int i = 0, j = -1, cnt = 0;
    while (j<n) {
        while (i<n && cnt>=k) {
            if(s[i]=='1') {
                --cnt;
            }
            ++i;
        }
        int last = 0, prev = j;
        while (j+1<n&&(cnt<k||(cnt==k && s[j+1]== '0'))) {
            ++j;
            if(s[j]=='1'){
                ++cnt;
                if(cnt == k) last = j;
            }
        }
        if(cnt < k) break;
        res = (res + binom[j-i+1][k] - (prev >= 0 ? binom[last-i][k-1] : 0) + M)%M;
        if(res < 0) res += M; 
    }
    cout << res << nl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

//   int t; cin >> t;
//   while(t--){
        solve();
//   }

    return 0;
}
