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

ll inv(ll a, ll b){
 return 1<a ? b - inv(b%a,a)*b/a : 1;
}

ll gcd(ll a, ll b){
  if(a == 0) return b;
  return gcd(b%a, a);
}

int a[200005][25];
int main() {
  // After m messages, let expected value of each message be 
  // e1, e2, .. , em. It suffices to calculate the expected value
  // For choosing exactly m messages.

  // Let kmax be the max k. At this k, we choose exactly k messages
  // let the expected values for choosing each message be
  // e1 >= e2 >= .... >= ek
  // then, it's easy to see that
  // E(kmax) = e1 + e2 + .. + ek

  // Furthermore, at k = kmax + 1, notice that the ordering
  // e1 >= e2 >= ... >= ek 
  // stays in the same ordered fashion, because each is simply
  // only having kmax/(kmax+1) multiplied to each ev.
  // so, our new ordering with k = kmax+1 messages is
  // e1 >= e2 >= .. >= ek >= e_(k+1)

  // So, if we compare the two, is there any point where
  // e1 + e2 + .. + ek < k * (e1 + e2 + .. + e_(k+1)) / (k+1)?
  // Obviously, an ordering that makes this most likely to happen is when
  // e1 = e2 = .... = ek = ek+1. 
  // Since e1, e2, .., ek were ordered in a strictly non-increasing manner
  // Then it must follow that ek >= e_(k+1).

  // At this equality, note that
  // e1 + e2 + .. + ek = e1 * (k)
  // e1 + e2 + .. + ek + e_(k+1) = e1 * (k+1)

  // Hence, e1 * (k+1) < k * (e1 * (k+1)) / (k+1)
  // e1 * (k+1) < k * e1 -> k+1 < k
  // Which is false. Hence, we only have to check up to k = 20.

  int n; cin >> n;
  for(int i=0; i<n; ++i){
    int m, k; cin >> m >> k;
    a[m][k]++;
  }

  map<int, vector<double>> mp;
  for(int i=0; i<=200000; ++i){
    vector<int> suff(22);
    for(int j=20; ~j; --j){
      suff[j] = suff[j+1]+a[i][j];
    }

    vector<double> ev(21);
    double sum = 0;
    for(int j=1; j<=20; ++j){
      ev[j] = (sum/j) + suff[j];
      sum += j*a[i][j];
    }
    if(sum > 0){
      mp[i] = ev;
    }
  }

  double bst = 0;
  vector<int> ret;
  for(int i=1; i<=20; ++i){
    vector<pair<double, int>> values;
    for(auto x : mp){
      values.push_back({x.second[i], x.first});
    }
    sort(values.begin(), values.end(), [&](pair<double, int>& a, pair<double, int>& b){
      return a.first > b.first;
    });

    double cur = 0;
    vector<int> ans(i);
    for(int j=0; j<min(i,sz(values)); ++j){
      cur += values[j].first;
      ans[j] = values[j].second;
    }
    if(cur > bst){
      bst = cur;
      ret = ans;
    }
  }

  cout << sz(ret) << nl;
  for(auto x : ret){
    cout << x << " ";
  }
  return 0;
}
