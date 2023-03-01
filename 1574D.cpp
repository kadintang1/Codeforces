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

  int n; cin >> n;
  vector<vector<int>> items(n);
  FOR(i,0,n){
    int c; cin >> c;
    items[i].resize(c);
    FOR(j,0,c){
      cin >> items[i][j];
    }
  }

  int m; cin >> m;
  set<vector<int>> banned;
  FOR(i,0,m){
    vector<int> build(n);
    FOR(j,0,n){
      cin >> build[j]; --build[j];
    }
    banned.insert(build);
  }

  vector<int> mxBuild(n);
  FOR(i,0,n){
    mxBuild[i] = sz(items[i])-1;
  }

  if(banned.find(mxBuild) == banned.end()){
    trav(x, mxBuild){
      cout << x+1 << " ";
    }
    return 0;
  }

  vector<int> ret;
  ll maxPower = 0;
  for(auto bannedBuild : banned){
    ll curPower = 0;
    FOR(i,0,n){
      curPower += items[i][bannedBuild[i]];
    }

    FOR(i,0,n){
      if(bannedBuild[i]-1 >= 0){
        bannedBuild[i]--;
        if(banned.find(bannedBuild) == banned.end()){
          if(maxPower < curPower - items[i][bannedBuild[i]+1]+items[i][bannedBuild[i]]){
            maxPower = curPower - items[i][bannedBuild[i]+1]+items[i][bannedBuild[i]];
            ret = bannedBuild;
          }
        }
        bannedBuild[i]++;
      }
    }
  }

  trav(x, ret){
    cout << x+1 << " ";
  }

  return 0;
}
