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

void solve(){
    // odd n: nk
    // even n: nk + n/2

    int n, M=1e9+7; cin >> n;
    // 6 10 4 4
    // 3 5 2 2

    // 2k+1, 6k+3, 4k+2, 8k+4
    // (5 choose 0) + (5 choose 2) + (5 choose 4) = 1 + 10 + 5 = 16
    // want even binomial sums -> roots unity filter
    // (x+1)^k + (x-1)^k /  2 = 2^k+0^k/2=2^(k-1)

    ll ans = 0, po = 1, pe = 1;
    vector<ll> a(n), p2(200005,1);
    FOR(i,1,200005){
        p2[i]=p2[i-1]*2%M;
    }
    FOR(i,0,n){
        cin >> a[i];
    }

    {
        FOR(i,0,32){
            ll occ = 0, pe = 1;
            FOR(j,0,n){
                if(a[j]%p2[i]){
                    continue;
                }
                ll cur_num = a[j]/p2[i];
                if(cur_num&1){
                    ++occ;
                } else{
                    pe = pe*2%M;
                }
            }
            ans = (ans + pe * ((!i?p2[occ]:(occ-1>=0?p2[occ-1]:1)) - 1))%M;
            if(ans < 0){
                ans += M;
            }
        }
    }

    cout << ans << nl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int t; cin >> t;
    // FOR(i,0,t){
        solve();
    // }
    return 0;
}
