#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define nl "\n"
#define vi vector<int>
#define trav(a, x) for(auto &a : x)
#define pb push_back
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define ROF(i, b, a) for(int i = b; i >= a; --i)
#define arr array

template<class T> bool umin(T& a, T b){
    return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T b){
    return a<b?a=b,1:0;
}

template<class T> T inv(T a, T b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1;
}

template<class R, class S> pair<R, S> operator+(const pair<R, S>& p1, const pair<R, S>& p2){
    return pair<R, S>(p1.first+p2.first, p1.second+p2.second);
}

template<class R, class S> pair<R, S> operator-(const pair<R, S>& p1, const pair<R, S>& p2){
    return pair<R, S>(p1.first-p2.first, p1.second-p2.second);
}

template<class R, class S> pair<R, S> operator*(const pair<R, S>& p1, const pair<R, S>& p2){
    return pair<R, S>(p1.first*p2.first, p1.second*p2.second);
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

const int N = 2e6+5;
int ft[N+5], cnt[N+5];
int query(int i){
    int res = 0;
    for(++i; i>0; i-=i&-i){
        res += ft[i];
    }
    return res;
}

int rangeSum(int l, int r){
    return query(r)-query(l-1);
}

void upd(int i, int d){
    for(++i; i<=N; i+=i&-i){
        ft[i]+=d;
    }
}

void solve(){
    int n; cin >> n;
    int c[2*n][2*n];
    ll ans = 0;
    FOR(i,0,2*n){
        FOR(j,0,2*n){
            cin >> c[i][j];
            if(i>=n&&j>=n){
                ans += c[i][j];
            }
        }
    }
    ans += min({c[0][n], c[0][2*n-1], c[n-1][n], c[n-1][2*n-1], c[n][0], c[n][n-1], c[2*n-1][0], c[2*n-1][n-1]});
    cout << ans << nl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    FOR(i,0,t){
        solve();
    }

    return 0;
}
