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
  int n, m; cin >> n >> m;
  vector<pi> dishes(n);
  vector<int> diff(n);
  ll lb = 0, hb = 0, delta = 0;
  FOR(i,0,n){
    int a, b; cin >> a >> b;
    dishes[i] = make_pair(a, b);
    delta += b - a;
    lb -= 2 * min(a, m) - m;
    hb += 2 * min(b, m) - m;
    // cout << "[" << -(2*min(a,m) - m) << ", " << 2*min(b,m)-m << "] " << nl;
    diff[i] = 2 * min(b, m) + 2 * min(a, m) - 2 * m;
  }
  ll targSum;
  if(lb <= delta && delta <= hb){
    if((delta&1) ^ (lb&1)){
      cout << 1 << nl;
    }
    else{
      cout << 0 << nl;
    }
    targSum = delta - lb;
  }
  else if(delta < lb){
    cout << lb - delta << nl;
  }
  else if(hb < delta){
    cout << delta - hb << nl;
  }

  // [lb, hb] delta change possible
  // we want a solution as close to delta as possible
  // suffices to greedily pick deltas
  // cout << "delta: " << delta << nl;
  // cout << "targ: " << targSum << nl;
  // cout << "[" << lb << ", " << hb << "]" << nl;
  FOR(i,0,n){
    // cout << "diff[" << i << "]: " << diff[i] << ", " << targSum << endl;
    int a = dishes[i].first, b = dishes[i].second;
    if(delta < lb){
      cout << min(a, m) << " " << m - min(a, m) << nl;
    }
    else if(hb < delta){
      cout << m - min(b, m) << " " << min(b, m) << nl;
    }
    else{
      if(targSum <= 1){
        cout << min(a, m) << " " << m - min(a, m) << nl;
        continue;
      }
      if(diff[i] <= targSum){
        cout << m - min(b, m) << " " << min(b, m) << nl;
        targSum -= diff[i];
      }
      else{
        cout << min(a,m) - targSum/2 << " " << m - (min(a,m) - targSum/2) << " " << nl;
        targSum = 0;
      }
    }
  }
  cout << nl;
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
