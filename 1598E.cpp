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
template<class T> bool umin(T& a, T& b){
  return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T& b){
  return a<b?a=b,1:0;
}

int dfs(int r, int c, int dir, int delta, vector<vector<int>>& grid){
  if(r < 0 || r >= sz(grid) || c < 0 || c >= sz(grid[0]) || !grid[r][c]){
    return 0;
  } 
  if(dir){
    return dfs(r, c + delta, !dir, delta, grid) + 1;
  }
  else{
    return dfs(r + delta, c, !dir, delta, grid) + 1;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m, q; cin >> n >> m >> q;
  vector<vector<int>> grid(n, vector<int>(m, 1));
  int dp[n][m][2];
  // 0 = vertical, 1 = horizontal
  ll ret = 0;
  FOR(i,0,n){
    FOR(j,0,m){
      dp[i][j][0] = dp[i][j][1] = 1;
      if(i-1 >= 0){
        dp[i][j][0] += dp[i-1][j][1];
      }
      if(j-1 >= 0){
        dp[i][j][1] += dp[i][j-1][0];
      }
      ret += dp[i][j][0] + dp[i][j][1] - 1;
    }
  }

  auto calc = [&](int r, int c){
    ll op1 = (dfs(r-1, c, 1, -1, grid)+1) * (dfs(r, c+1, 0, 1, grid)+1);
    ll op2 = (dfs(r, c-1, 0, -1, grid)+1) * (dfs(r+1, c, 1, 1, grid)+1);
    return op1 + op2 - 1;
  };

  FOR(i,0,q){
    int r, c; cin >> r >> c;
    --r; --c;
    if(grid[r][c]){
      //block off obstacle
      grid[r][c] = 0;
      ret -= calc(r, c);
    }
    else{
      //rejoin obstacle
      grid[r][c] = 1;
      ret += calc(r, c);
    }
    cout << ret << nl;
  }
  return 0;
}
