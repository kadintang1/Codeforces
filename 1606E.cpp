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

const int mxN = 505, M = 998244353;
ll dp[mxN][mxN], comb[mxN][mxN], power[mxN][mxN];

void solve(){
  int n, x; cin >> n >> x;
  for(int i = 0; i <= 501; ++i){
    power[i][0] = 1;
    for(int j = 1; j <= 501; ++j){
      power[i][j] = (power[i][j-1] * i)%M;
    }
  }

  for(int i = 1; i <= 501; ++i){
    for(int j = 0; j <= 501; ++j){
      if(j > i) continue;
      if(j == 0 || j == i){
        comb[i][j] = 1; continue;
      }
      comb[i][j] = (comb[i-1][j-1] + comb[i-1][j])%M;
    }
  }

  for(int i = 0; i <= x; ++i){
    dp[0][i] = 1;
  }

  for(int i = 2; i <= n; ++i){
    for(int j = 1; j <= x; ++j){
      if(j <= i-1){
        dp[i][j] = power[j][i];
      }
      else{
        for(int k = 0; k <= i; ++k){
          dp[i][j] = (dp[i][j] + power[i-1][k]*comb[i][k]%M*dp[i-k][j-i+1]%M)%M;
        }
      }
    }
  }
  cout << dp[n][x] << nl;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  // int t; cin >> t;
  // while(t--){
    solve();
  // }

  return 0;
}
