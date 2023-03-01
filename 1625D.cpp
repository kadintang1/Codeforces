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

void solve(){
    int n, k; cin >> n >> k;
    // split into prefixes and suffixes
    // for every duo with identical prefixes, check if a pair can be formed :|
    map<int, vector<array<int, 2>>> mp;
    int p2 = 0;
    while((1<<p2)<=k){
        ++p2;
    }
    if(!k){
        cout << n << nl;
        FOR(i,1,n+1){
            cout << i << " ";
        }
        return;
    }

    FOR(i,0,n){
        int x; cin >> x;
        mp[x>>p2].push_back({i+1, x%(1<<p2)});
    }
    // 0100
    // 0111
    // 0001

    vector<int> ans;
    for(auto it = mp.rbegin(); it != mp.rend(); ++it){
        int p = it->first;
        vector<array<int, 2>> v = it->second;
        // dbg(p);
        // dbg(v);
        array<int, 2> c[sz(v)*35][2];
        vector<int> g;
        int t = 0;
        FOR(i,0,sz(v)*35){
            FOR(j,0,2){
                c[i][j] = {0, -1};
            }
        }

        for(auto& [i, x] : v){
            if(sz(g)) break;
            int u = 0, cur = 0;
            ROF(j,31,0){
                int b = x>>j&1;
                if(!c[u][b][0]){
                    c[u][b] = {++t, i};
                }
                u = c[u][b][0];
            }

            u = 0;
            ROF(j,31,0){
                int b = x>>j&1;
                if(c[u][b^1][0]){
                    cur |= 1<<j;
                }

                if(cur >= k){
                    g = {i, c[u][b^1][1]};
                    break;
                }

                if(c[u][b^1][0]){
                    u = c[u][b^1][0];
                } else{
                    u = c[u][b][0];
                }
            }
        }
        if((p||sz(ans))&&!sz(g)){
            ans.push_back(v[0][0]);
        } else{
            copy(all(g), back_inserter(ans));
        }
    }
    if(!sz(ans)){
        cout << -1 << nl; return;
    }
    cout << sz(ans) << nl;
    trav(x, ans){
        cout << x << " ";
    }
}    

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
