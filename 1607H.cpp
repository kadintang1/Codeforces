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
#define idx(i, x) get<i>(x)
template<class T> bool umin(T& a, T b){
  return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T b){
  return a<b?a=b,1:0;
}

void solve(){
  map<int, vector<array<int, 3>>> mp;
  int n; cin >> n;
  vector<pi> ans(n);
  vector<array<int, 3>> dishes(n);
  FOR(i,0,n){
    int a, b, m; cin >> a >> b >> m;
    dishes[i] = {a, b, m};
    mp[a + b - m].push_back({a - min(a, m), a - (m - min(m, b)), i});
  }

  int ret = 0;
  for(auto& x : mp){
    set<int> st;
    vector<array<int, 3>>& v = x.second;
    sort(all(v), [&](array<int, 3>& a, array<int, 3>& b){
      return a[1] < b[1];
    });
    trav(a, v){
      auto it = st.upper_bound(a[0]-1);
      if(!sz(st) || it == st.end()){
        st.insert(a[1]);
        ans[a[2]] = make_pair(dishes[a[2]][0] - a[1], dishes[a[2]][2] - (dishes[a[2]][0] - a[1]));
        continue;
      }
      ans[a[2]] = make_pair(dishes[a[2]][0] - *it, dishes[a[2]][2] - (dishes[a[2]][0] - *it));
    }
    ret += sz(st);
  }
  cout << ret << nl;
  for(auto& x : ans){
    cout << x.first << " " << x.second << nl;
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
