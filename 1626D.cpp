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

int p2(int x){
  int res = 1;
  while(res < x){
    res <<= 1;
  }
  return res - x;
}

void solve(){
  int n; cin >> n;
  int ans = p2(n)+2;
  vector<int> a(n);
  trav(x, a) cin >> x;
  sort(all(a));
  for(int i=1; i<=n; i<<=1){
    for(int j=1; j<=n; j<<=1){
      int light_index = lower_bound(all(a), a[i-1])-a.begin()-1;
      int heavy_index = lower_bound(all(a), a[n-j])-a.begin();
      if(light_index < heavy_index){
        umin(ans, p2(light_index+1) + p2(n-heavy_index) + p2(heavy_index - light_index - 1));
      }
      light_index = upper_bound(all(a), a[i-1])-a.begin()-1;
      if(light_index < heavy_index){
        umin(ans, p2(light_index+1) + p2(n-heavy_index) + p2(heavy_index - light_index - 1));
      }
      heavy_index = upper_bound(all(a), a[heavy_index])-a.begin();
      if(light_index < heavy_index){
        umin(ans, p2(light_index+1) + p2(n-heavy_index) + p2(heavy_index - light_index - 1));
      }
      light_index = lower_bound(all(a), a[i-1])-a.begin()-1;
      if(light_index < heavy_index){
        umin(ans, p2(light_index+1) + p2(n-heavy_index) + p2(heavy_index - light_index - 1));
      }
    }
  }

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
