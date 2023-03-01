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
#define FORr(i, b, a); for(int i = b; i >= a; --i)
template<class T> bool umin(T& a, T& b){
  return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T& b){
  return a<b?a=b,1:0;
}

const int M = 1e9+7;
ll dp[60 * 10000 + 5][6];
ll c[60 * 10000+5];
vl color[6];
map<ll, int> label, arr;
vector<vector<int>> adj;

ll solve(int i, int j){
  if(c[i] != -1 && c[i] != j){
    return 0;
  }
  if(dp[i][j] ^ -1){
    return dp[i][j];
  }

  ll ans = 0;
  ll sum[2] = {0};
  for(auto p : color[j]){
    FOR(j,0,sz(adj[i])){
      sum[j] = (sum[j]+solve(adj[i][j],p))%M;
    }
  }

  if(!adj[i].size()){
    sum[0]=sum[1]=1;
  }
  if(adj[i].size()==1){
    sum[1]=1;
  }
  ans = (sum[0] * sum[1])%M;
  return dp[i][j]=ans;
}

ll bp(ll a, ll b){
  ll ret = 1;
  while(b > 0){
    if(b&1){
      ret = (ret * a) % M;
    }
    a = (a * a) % M;
    b >>= 1;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int k; cin >> k;
  ll n; cin >> n;
  int num = 0;
  ll emptyNodes = (1LL<<k) - 1;
  color[0] = {1,2,4,5};
  color[1] = {0,2,3,5};
  color[2] = {0,1,3,4};
  color[3] = {1,2,4,5};
  color[4] = {0,2,3,5};
  color[5] = {0,1,3,4};
  map<string, int> mp;
  mp["white"] = 0;
  mp["blue"] = 1;
  mp["red"] = 2;
  mp["yellow"] = 3;
  mp["green"] = 4;
  mp["orange"] = 5;
  memset(dp, -1, sizeof(dp));
  memset(c, -1, sizeof(c));
  FOR(i,0,n){
    ll v; cin >> v;
    string s; cin >> s;
    arr[v] = mp[s];
    while(v >= 1 && !label.count(v)){
      label[v] = num; ++num;
      --emptyNodes;
      v >>= 1;
    }
  }
  adj.resize(num+1);
  for(auto p : label){
    if(arr.count(p.first)){
      c[p.second] = arr[p.first]; 
    }
    if(label.count(p.first * 2)){
      adj[p.second].pb(label[p.first * 2]);
    }
    if(label.count(p.first * 2 + 1)){
      adj[p.second].pb(label[p.first * 2 + 1]);
    }
  }

  ll ans = bp(4, emptyNodes), sum = 0;
  FOR(i,0,6){
    sum += solve(label[1], i);
    sum %= M;
  }
  ans = (ans * sum)%M;
  cout << ans << nl;
  return 0;
}
