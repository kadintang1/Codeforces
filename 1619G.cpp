#include <bits/stdc++.h>
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

template<class T> T inv(T a, T b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1;
}

template<class R, class S> pair<R, S> operator+(const pair<R, S>& p1, const pair<R, S>& p2){
    return pair<R, S>(p1.first+p2.first, p1.second+p2.second);
}

map<array<int, 2>, int> mp;
const int mxN = 2e5;
int p[mxN], sz[mxN];
int find(int u){
    return u==p[u]?u:p[u]=find(p[u]);
}

void unite(int u, int v){
    if((u=find(u))==(v=find(v))) return;
    if(sz[u]<sz[v]) swap(u,v);
    sz[u]+=sz[v];
    p[v]=p[u];
}

void solve(){
    int n, k; cin >> n >> k;
    vector<array<int, 3>> bombs(n);
    map<int, vector<int>> mpX, mpY;
    FOR(i,0,n){
        p[i] = i; sz[i] = 1;
        cin >> bombs[i][0] >> bombs[i][1] >> bombs[i][2];
        mp[{bombs[i][0], bombs[i][1]}] = i;
        mpX[bombs[i][0]].push_back(bombs[i][1]);
        mpY[bombs[i][1]].push_back(bombs[i][0]);
    }

    for(auto& x : mpX){
        vector<int>& coords = x.second;
        sort(all(coords));
        FOR(i,1,sz(coords)){
            if(coords[i]-coords[i-1]<=k){
                unite(mp[{x.first, coords[i-1]}], mp[{x.first, coords[i]}]);
            }
        }
    }

    for(auto& y : mpY){
        vector<int>& coords = y.second;
        sort(all(coords));
        FOR(i,1,sz(coords)){
            if(coords[i]-coords[i-1]<=k){
                unite(mp[{coords[i-1], y.first}], mp[{coords[i], y.first}]);
            }
        }
    }

    map<int, vector<int>> comps;
    FOR(i,0,n){
        comps[find(i)].push_back(bombs[i][2]);
    }

    vector<int> times; times.reserve(sz(comps));
    for(auto& x : comps){
        times.push_back(*min_element(all(x.second)));
    }
    sort(all(times));

    int i=-1, l=0, r=sz(times)-1;
    while(l<=r){
        ++i; --r;
        while(l<sz(times)&&times[l]<=i){
            ++l;
        }
    }
    cout << i << nl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t; cin >> t;
  while(t--){
      solve();
  }


  return 0;
}
