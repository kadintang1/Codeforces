#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define nl "\n"
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define FORd(i, b, a) for(int i = b; i >= a; --i)
#define ROF(i, b, a) for(int i = b; i >= a; --i)
#define trav(a, x) for(auto &a : x)
#define pi pair<int, int>
#define pb push_back
#define ff first
#define ss second

template<class T> bool umin(T& a, T b){
    return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T b){
    return a<b?a=b,1:0;
}

template<class T> T inv(T a, T b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1;
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m)), dpTop(n, vector<int>(m)), dpBot(n, vector<int>(m));
    FOR(i,0,n){
        string s; cin >> s;
        FOR(j,0,m){
            g[i][j] = s[j]-'a';
        }
    }

    FOR(i,0,n){
        vector<int> l(m), r(m);
        FOR(j,0,m){
            if(j-1 >= 0 && g[i][j-1] == g[i][j]){
                l[j] = l[j-1];
            } else{
                l[j] = j;
            }
        }

        FORd(j,m-1,0){
            if(j+1<m && g[i][j] == g[i][j+1]){
                r[j] = r[j+1]; 
            } else{
                r[j] = j;
            }
            dpTop[i][j] = min({i-1 >= 0 && g[i-1][j] == g[i][j] ? dpTop[i-1][j] : 0, j - l[j], r[j] - j}) + 1;
        }
    }

    int ans = 0;
    FORd(i,n-1,0){
        vector<int> l(m), r(m);
        FOR(j,0,m){
            if(j-1>=0 && g[i][j-1] == g[i][j]){
                l[j] = l[j-1];
            } else{
                l[j] = j;
            }
        }

        FORd(j,m-1,0){
            if(j+1<m && g[i][j] == g[i][j+1]){
                r[j] = r[j+1]; 
            } else{
                r[j] = j;
            }
            dpBot[i][j] = min({i+1 < n && g[i+1][j] == g[i][j] ? dpBot[i+1][j] : 0, j - l[j], r[j] - j}) + 1;
            ans += min(dpBot[i][j], dpTop[i][j]);
        }
    }

    cout << ans << nl;
    return 0;
}
