#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <tgmath.h>
#include <cassert>
#include <time.h>
#include <random>
#include <array>
#include <numeric>

using namespace std;
typedef long long ll;
#define nl "\n"
#define vi vector<int>
#define vl vector<long>
#define vb vector<bool>
#define vii vector<vector<int>>
#define mi map<int, int>    
#define pi pair<int, int>
#define trav(a, x) for(auto &a : x)
#define pb push_back
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define bitCount(i) __builtin_popcount(i)
#define rev(v) reverse(all(v))
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define ROF(i, b, a); for(int i = b; i >= a; --i)
template<class T> bool umin(T& a, T b){
  return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T b){
  return a<b?a=b,1:0;
}

void solve(){
  int n; cin >> n;
  vector<long long> a(n);
  trav(x, a) cin >> x;
  vector<long long> pref(n + 1), suff(n + 1);
  for(int i = 0; i < n; ++i){
    if(pref[i] == -1 || a[i] < pref[i]){
      pref[i + 1] = -1;
    }
    else{
      pref[i + 1] = a[i] - pref[i];
    }
  }

  for(int i = n-1; i >= 0; --i){
    if(suff[i+1] == -1 || a[i] < suff[i+1]){
      suff[i] = -1;
    }
    else{
      suff[i] = a[i] - suff[i+1];
    }
  }

  bool ok = (pref[n] == 0);
  for(int i = 0; i < n - 1; ++i){
    ok |= (pref[i] >= 0 && suff[i + 2] >= 0 && a[i + 1] - pref[i] == a[i] - suff[i + 2] && a[i + 1] >= pref[i] && a[i] >= suff[i + 2]);
  }

  if(ok){
    cout << "YES" << nl;
  }
  else{
    cout << "NO" << nl;
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int t; cin >> t;
  while(t--){
    solve();
  }

  return 0;
}
