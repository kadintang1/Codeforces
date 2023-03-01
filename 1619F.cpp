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

void solve(){
    int n, m, k; cin >> n >> m >> k;
    int b = n%m, s = m - n%m, p = 0;
    FOR(i,0,k){
        for(int j=0; j<b; ++j){
            cout << (n/m)+(n%m!=0) << " ";
            for(int k=0; k<(n/m)+(n%m!=0); ++k, p=(p+1)%n){
                cout << p+1 << " ";
            }
            cout << nl;
        }
        int q = p;
        for(int j=0; j<s; ++j){
            cout << (n/m) << " ";
            for(int k=0; k<(n/m); ++k, q=(q+1)%n){
                cout << q+1 << " ";
            }
            cout << nl;
        }
    }
    cout << nl;
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
