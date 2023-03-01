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

const int MAX = 2e7;
ll dp[MAX+5], divCount[MAX+5];
bool isPrime[MAX];
void solve(){
  int n; cin >> n;
  memset(isPrime, 1, sizeof(isPrime));
  isPrime[0]=isPrime[1]=0;
  for(int i=2; i<=MAX; ++i){
    if(isPrime[i]&&i*(ll)i<=MAX){
      for(int j=i*i; j<=MAX; j+=i){
        isPrime[j]=0;
      }
    }
  }
  vector<int> primes;
  for(int i=2; i<=MAX; ++i){
    if(isPrime[i]){
      primes.push_back(i);
    }
  }

  for(int i=0; i<n; ++i){
    int x; cin >> x;
    for(int j=1; j*j<=x; ++j){
      if(x%j==0){
        divCount[j]++;
        if(j^(x/j)){
          divCount[x/j]++;
        }
      }
    }
  }

  ll res = 0;
  for(int i=MAX; i>=1; --i){
    dp[i]=i*divCount[i];
    int j=i;
    trav(x, primes){
      if(j*(ll)x > MAX) break;
      dp[i]=max(dp[i], dp[j*x]+i*(divCount[i]-divCount[j*x]));
    }
    umax(res,dp[i]);
  }
  cout << res << nl;
}

int main() {
  solve();
  return 0;
}
