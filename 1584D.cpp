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
#define ROF(i, b, a) for(int i = b; i >= a; --i)
#define arr array
template<class T> bool umin(T& a, T b){
  return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T b){
  return a<b?a=b,1:0;
}

void solve(){
  ll n; cin >> n;
  ll i = 1, hb = n;
  while(1){
    ll mb = (i+hb+1)/2;
    cout << "? " << 1 << " " << mb << endl;
    cout.flush();
    ll x; cin >> x;
    if(x == 0){
      i = mb;
    }
    else{
      hb = mb-1;
    }

    if(i == hb){
      ll a, b, d, j, k;
      cout << "? " << i << " " << n << endl;
      cout.flush();

      cin >> a;
      cout << "? " << i+1 << " " << n << endl;
      cout.flush();
      cin >> b;

      d = a-b;
      j = i+d+1;

      cout << "? " << j << " " << n << endl;
      cout.flush();

      cin >> a;
      cout << "? " << j+1 << " " << n << endl;
      cout.flush();
      cin >> b;

      d = a-b;
      k = j+d;
      cout << "! " << i << " " << j << " " << k << nl;
      cout.flush();
      return;
    }
  }
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
