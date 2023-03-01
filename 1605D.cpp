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

vector<vector<int>> adj(200005);
int ret[200005], color[2], assign[200005];
void dfs(int u, int p, int c){
  color[c]++; assign[u] = c;
  for(int v : adj[u]){
    if(v ^ p){
      dfs(v, u, c ^ 1);
    }
  }
}
void solve(){
  int n; cin >> n;
  color[0] = color[1] = 0;
  for(int i = 0; i < n; ++i){
    adj[i].clear();
  }

  for(int i = 0; i < n-1; ++i){
    int u, v; cin >> u >> v; --u; --v;
    adj[u].pb(v);
    adj[v].pb(u);
  }

  dfs(0, -1, 0);
  vector<int> b, w;
  if(color[0] > color[1]){
    swap(color[1], color[0]);
    for(int i = 0; i < n; ++i){
      assign[i] ^= 1;
    }
  }

  for(int i = 0; i < n; ++i){
    if(!assign[i]){
      w.push_back(i);
    }
    else{
      b.push_back(i);
    }
  }

  for(int i = 1; i <= n; ++i){
    for(int j = 18; j >= 0; --j){
      if((color[0]>>j)%2 == 1 && (i>>j)%2 == 1){
        ret[w.back()] = i;
        w.pop_back();
        break;
      }
      else if((i>>j)%2 == 1){
        ret[b.back()] = i;
        b.pop_back();
        break;
      }
    }

  }

  for(int i = 0; i < n; ++i){
    cout << ret[i] << " ";
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
