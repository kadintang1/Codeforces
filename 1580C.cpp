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

template<class R, class S> pair<R, S> operator-(const pair<R, S>& p1, const pair<R, S>& p2){
    return pair<R, S>(p1.first-p2.first, p1.second-p2.second);
}

template<class R, class S> pair<R, S> operator*(const pair<R, S>& p1, const pair<R, S>& p2){
    return pair<R, S>(p1.first*p2.first, p1.second*p2.second);
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

const int N = 200005;
int B = 450, type1[500][500], ans[N], sum[N], p[N];
vector<int> type2[N];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m; cin >> n >> m;
  vector<array<int, 2>> a(n);
  FOR(i,0,n){
    cin >> a[i][0] >> a[i][1];
  }

  FOR(i,1,m+1){
    int op, k; cin >> op >> k; --k;
    if(op == 1){
      int x = a[k][0], y = a[k][1];
      if(x+y <= B){
        p[k] = i;
        FOR(j,i+x,i+x+y){
          type1[j%(x+y)][x+y]++;
        }
      } else{
        type2[k].push_back(i);
      }
    } else{
      int x = a[k][0], y = a[k][1];
      if(x+y <= B){
        FOR(j,p[k]+x,p[k]+x+y){
          type1[j%(x+y)][x+y]--;
        }
      } else{
        type2[k].push_back(i);
      }
    }
    FOR(j,1,B+1){
      ans[i] += type1[i%j][j];
    }
  }

  FOR(i,0,n){
    if(!(sz(type2[i]))) continue;
    for(int j=0; j<sz(type2[i]); j+=2){
      int nxt = j+1<sz(type2[i])?type2[i][j+1]-1:m;
      for(int x=type2[i][j], op=0; x<=nxt; op^=1){
        if(!op){
          x += a[i][0];
        } else{
          sum[x]++;
          sum[min(nxt+1, x+a[i][1])]--;
          x += a[i][1];
        }
      }
    }
  }

  FOR(i,1,m+1){
    sum[i] += sum[i-1];
    cout << ans[i]+sum[i] << nl;
  }


  return 0;
}
