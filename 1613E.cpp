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

const int M = 998244353;
ll bpow(ll base, ll pow){
    ll res = 1;
    while(pow > 0){
        if(pow&1) res = res * base % M;
        base = base * base % M;
        pow >>= 1;
    }
    return res;
}
void solve(){
    // 1 1 1 1 1 ....
    // 0 0 0 0 1 1 1 2 2 2 3 3 3 5 5 5 5
    int r, c; cin >> r >> c;
    vector<string> grid(r);
    vector<vector<int>> deg(r, vector<int>(c));
    vector<vector<bool>> ok(r, vector<bool>(c));
    FOR(i,0,r){
        cin >> grid[i];
    }

    queue<array<int, 2>> q;
    FOR(i,0,r){
        FOR(j,0,c){
            if(grid[i][j]=='#') continue;
            if(i-1 >= 0 && grid[i-1][j] == '.') ++deg[i][j];
            if(i+1 < r && grid[i+1][j] == '.') ++deg[i][j];
            if(j-1 >= 0 && grid[i][j-1] == '.') ++deg[i][j];
            if(j+1 < c && grid[i][j+1] == '.') ++deg[i][j];
        }
    }

    FOR(i,0,r){
        FOR(j,0,c){
            if(grid[i][j]=='L'){
                ok[i][j] = 1;
                if(i-1 >= 0 && grid[i-1][j] == '.'){
                    if(deg[i-1][j]<=1){
                        ok[i-1][j] = 1; q.push({i-1, j});
                    }
                }
                if(i+1 < r && grid[i+1][j] == '.'){
                    if(deg[i+1][j]<=1){
                        ok[i+1][j] = 1; q.push({i+1, j});
                    }
                }
                if(j-1 >= 0 && grid[i][j-1] == '.'){
                    if(deg[i][j-1]<=1){
                        ok[i][j-1] = 1; q.push({i, j-1});
                    }
                }
                if(j+1 < c && grid[i][j+1] == '.'){
                    if(deg[i][j+1]<=1){
                        ok[i][j+1] = 1; q.push({i, j+1});
                    }
                }
            }
        }
    }

    while(sz(q)){
        array<int, 2>& pos = q.front(); q.pop();
        int i = pos[0], j = pos[1];
        if(i-1 >= 0 && grid[i-1][j] == '.'){
            --deg[i-1][j];
            if(deg[i-1][j]<=1&&!ok[i-1][j]){
                ok[i-1][j] = 1; q.push({i-1, j});
            }
        }
        if(i+1 < r && grid[i+1][j] == '.'){
            --deg[i+1][j];
            if(deg[i+1][j]<=1&&!ok[i+1][j]){
                ok[i+1][j] = 1; q.push({i+1, j});
            }
        }
        if(j-1 >= 0 && grid[i][j-1] == '.'){
            --deg[i][j-1];
            if(deg[i][j-1]<=1&&!ok[i][j-1]){
                ok[i][j-1] = 1; q.push({i, j-1});
            }
        }
        if(j+1 < c && grid[i][j+1] == '.'){
            --deg[i][j+1];
            if(deg[i][j+1]<=1&&!ok[i][j+1]){
                ok[i][j+1] = 1; q.push({i, j+1});
            }
        }
    }

    FOR(i,0,r){
        FOR(j,0,c){
            if(ok[i][j]&&grid[i][j]^'L'){
                cout << "+";
            } else{
                cout << grid[i][j];
            }
        }
        cout << nl;
    }
}

int main() {
    int t; cin >> t;
    while(t--){
        solve();
    }

    return 0;
}
