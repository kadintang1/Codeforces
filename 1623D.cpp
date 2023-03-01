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
#define rev(v) reverse(all(v))
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

#define defop(type, op) \
    inline friend type operator op (type u, const type& v) { return u op ##= v; } \
    type& operator op##=(const type& o)
template<int mod>
struct ModularInt{
    int x;
    ModularInt(int _x = 0): x(_x) {}
    ModularInt(ll _x): x(int(_x % mod)) {}
    defop(ModularInt, +) {
        if ((x += o.x) >= mod) x -= mod;
        return *this;
    }

    defop(ModularInt, -) {
        if ((x -= o.x) < 0) x += mod;
        return *this;
    }

    defop(ModularInt, *) { 
        return *this = ModularInt(1ll * x * o.x); 

    }
    ModularInt pow(ll exp) const {
        ModularInt ans = 1, base = *this;
        for (; exp > 0; exp >>= 1, base *= base){
            if(exp&1) ans *= base;
        }
        return ans;
    }

    defop(ModularInt, /) { return *this *= o.pow(mod - 2); }
};
const int M = 1e9+7;
using mint = ModularInt<M>;
void solve(){
    int n, m, rb, cb, rd, cd; cin >> n >> m >> rb >> cb >> rd >> cd;
    mint p; cin >> p.x; p = 1-(p/100);
    int dr = -1, dc = -1;
    mint u=0, v=1;
    for (int i=0; i<4*(n - 1)*(m - 1); ++i) {
        if (1>rb+dr||rb+dr>n) dr = -dr;
        if (1>cb+dc||cb+dc>m) dc = -dc;
        rb += dr; cb += dc; u += 1;
        if (rb==rd||cb==cd) {
            u *= p;
            v *= p;
        }
    }
    cout << (u/(1 - v)).x << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t; cin >> t;
  while(t--){
      solve();
  }

  return 0;
}
