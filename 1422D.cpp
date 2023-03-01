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
#include <regex>

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
#define ROF(i, b, a) for(int i = b; i >= a; --i)
#define arr array
template<class T> bool umin(T& a, T b){
  return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T b){
  return a<b?a=b,1:0;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m; cin >> n >> m;
  int sx, sy, fx, fy; cin >> sx >> sy >> fx >> fy;
  vector<array<int, 3>> p(m);
  FOR(i,0,m){
    cin >> p[i][0] >> p[i][1];
    p[i][2] = i+1;
  }

  vector<vector<array<int, 2>>> adj(m+2);
  adj[0].push_back({m+1, abs(sx-fx)+abs(sy-fy)});
  FOR(i,0,m){
    adj[0].push_back({p[i][2], min(abs(sx-p[i][0]), abs(sy-p[i][1]))});
    adj[p[i][2]].push_back({m+1, abs(fx-p[i][0])+abs(fy-p[i][1])});
  }

  sort(p.begin(), p.end());
  FOR(i,0,m){
    if(i-1 >= 0){
      adj[p[i][2]].push_back({p[i-1][2], abs(p[i][0]-p[i-1][0])});
    }
    if(i+1 < m){
      adj[p[i][2]].push_back({p[i+1][2], abs(p[i][0]-p[i+1][0])});
    }
  }

  FOR(i,0,m){
    swap(p[i][0], p[i][1]);
  }

  sort(p.begin(), p.end());
  FOR(i,0,m){
    swap(p[i][0], p[i][1]);
  }
  FOR(i,0,m){
    if(i-1 >= 0){
      adj[p[i][2]].push_back({p[i-1][2], abs(p[i][1]-p[i-1][1])});
    }
    if(i+1 < m){
      adj[p[i][2]].push_back({p[i+1][2], abs(p[i][1]-p[i+1][1])});
    }
  }

  vector<ll> dist(m+2, 1e18);
  priority_queue<pair<ll, int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
  pq.push({0, 0});
  dist[0] = 0;
  while(sz(pq)){
    auto top = pq.top(); pq.pop();
    if(dist[top.second] < top.first) continue;
    int u = top.second;
    ll d = top.first;
    for(auto e : adj[u]){
      int v = e[0], w = e[1];
      if(dist[v]>dist[u]+w){
        dist[v]=dist[u]+w;
        pq.push({dist[v], v});
      }
    }
  }

  cout << dist[m+1] << nl;
  return 0;
}
