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
    // iterate through all 2^n possible sign permutations of students
    int n, m; cin >> n >> m;
    vector<int> x(n);
    trav(v, x) cin >> v;
    vector<vector<int>> grid(n, vector<int>(m));
    FOR(i,0,n){
        string s; cin >> s;
        FOR(j,0,m){
            grid[i][j] = s[j]-'0';
        }
    }

    ll ans = -1;
    vector<int> perm_ans(m);
    FOR(msk,0,1<<n){
        ll sum_expected = 0;
        // set bits = xi - ri
        // unset bits = ri - xi

        vector<array<int, 2>> p(m);
        FOR(i,0,m){
            p[i][1] = i+1;
        }

        FOR(i,0,n){
            if(msk>>i&1){
                sum_expected += x[i];
                FOR(j,0,m){
                    p[j][0] -= grid[i][j];
                }
            } else{
                sum_expected -= x[i];
                FOR(j,0,m){
                    p[j][0] += grid[i][j];
                }
            }
        }

        sort(rbegin(p), rend(p));
        FOR(i,0,m){
            sum_expected += (m-i) * (ll) p[i][0];
        }
        // dbg(p);
        // dbg(sum_expected);
        // cout << nl;
        if(sum_expected > ans){
            ans = sum_expected;
            FOR(i,0,m){
                perm_ans[p[i][1]-1] = m-i;
            }
        }
    }

    trav(x, perm_ans){
        cout << x << " ";
    }
    cout << nl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    FOR(i,0,t){
        solve();
    }

    return 0;
}
