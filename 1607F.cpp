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

const int mxN = 2e3;
int nxt[mxN * mxN + 5], vis[mxN * mxN + 5];
int deg[mxN * mxN + 5], p[mxN * mxN + 5];
int path[mxN * mxN + 5], cycleSize[mxN * mxN + 5];
void solve(){
  int n, m; cin >> n >> m;
  FOR(i,0,n){
    FOR(j,0,m){
      vis[i * m + j] = deg[i * m + j] = cycleSize[i * m + j] = 0;
      p[i * m + j] = nxt[i * m + j] = -1;
      path[i * m + j] = 1;
    }
  }

  FOR(i,0,n){
    string s; cin >> s;
    FOR(j,0,m){
      if(s[j] == 'L'){
        if(j - 1 >= 0){
          nxt[m * i + j] = m * i + j - 1;
          deg[m * i + j - 1]++;
        }
      }
      else if(s[j] == 'R'){
        if(j + 1 < m){
          nxt[m * i + j] = m * i + j + 1;
          deg[m * i + j + 1]++;
        }
      }
      else if(s[j] == 'U'){
        if(i - 1 >= 0){
          nxt[m * i + j] = m * (i - 1) + j;
          deg[m * (i - 1) + j]++;
        }
      }
      else if(s[j] == 'D'){
        if(i + 1 < n){
          nxt[m * i + j] = m * (i + 1) + j;
          deg[m * (i + 1) + j]++;
        }
      }
    }
  }

  queue<int> q;
  FOR(i,0,n){
    FOR(j,0,m){
      if(!deg[m * i + j]){
        q.push({m * i + j});
      }
    }
  }

  while(sz(q)){
    int u = q.front(); q.pop();
    if(nxt[u] == -1) continue;
    if(path[nxt[u]] < path[u] + 1){
      path[nxt[u]] = path[u] + 1;
      p[nxt[u]] = u;
    }
    deg[nxt[u]]--;
    if(!deg[nxt[u]]){
      q.push(nxt[u]);
    }
  }

  FOR(i,0,n){
    FOR(j,0,m){
      if(!deg[i * m + j]) continue;
      vector<int> comp;
      int u = i * m + j;
      while(!vis[u]){
        vis[u] = 1;
        comp.pb(u);
        u = nxt[u];
      }
      for(int u : comp){
        cycleSize[u] = sz(comp);
      }
    }
  }

  int maxPath = 0, endNode = 0;
  FOR(i,0,n){
    FOR(j,0,m){
      if(path[i * m + j] + max(cycleSize[i * m + j] - 1, 0) > maxPath){
        maxPath = path[i * m + j] + max(cycleSize[i * m + j] - 1, 0);
        endNode = i * m + j;
      }
    }
  }
  while(p[endNode] ^ -1){
    endNode = p[endNode];
  }

  cout << endNode / m + 1 << " " << endNode % m + 1 << " " << maxPath << nl;
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
