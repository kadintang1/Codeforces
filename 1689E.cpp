#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define nl "\n"
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define FORd(i, b, a) for(int i = b; i >= a; --i)
#define EACH(x, a) for (auto& x : a)
#define arr array
#define pi pair<int, int>
#define vpi vector<pair<int, int>>
#define vi vector<int>
#define vl vector<ll>
#define pb push_back
#define ff first
#define ss second

template<class T> bool umin(T& a, T b){
    return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T b){
    return a<b?a=b,1:0;
}

ll inv(ll a, ll b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1;
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

int p[2005];
int find(int u){
    return u == p[u] ? u : p[u] = find(p[u]);
}

void unite(int u, int v){
    int U = find(u), V = find(v);
    if(U == V) return;
    p[U] = V;
}

void reset(int n){
    for(int i = 0; i < n; ++i){
        p[i] = i;
    }
}

void test_case(int _t){
    int n, ret = 0; cin >> n;
    vi a(n); reset(n);
    FOR(i,0,n){
        cin >> a[i];
        if(!a[i]){
            ++ret; ++a[i];
        }
    }

    bool done = 1;
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            if(a[i] & a[j]){
                unite(i, j);
            }
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            if(find(i) ^ find(j)){
                done = 0;
            }
        }
    }

    if(done){
        cout << ret << nl;
        for(int i = 0; i < n; ++i){
            cout << a[i] << " ";
        }
        cout << nl; return;
    }

    function<bool(void)> chk = [&](){
        vector<vector<int>> g(32);
        for(int j = 0; j < n; ++j){
            for(int k = 0; k < 32; ++k){
                if(a[j] >> k & 1){
                    g[k].pb(j);
                }
            }
        }

        for(int j = 0; j < 32; ++j){
            for(int k = 0; k < sz(g[j]) - 1; ++k){
                unite(g[j][k], g[j][k + 1]);
            }
        }

        int type = find(0), is_sol = 1;
        for(int j = 0; j < n; ++j){
            if(find(j) ^ type){
                is_sol = 0; break;
            }
        }

        return is_sol;
    };

    function<void(int)> print = [&](int ret){
        cout << ret << nl;
        for(int j = 0; j < n; ++j){
            cout << a[j] << " ";
        }
        cout << nl; return;
    };

    for(int i = 0; i < n; ++i){
        a[i]++; reset(n);
        if(chk()){
            print(ret + 1); return;
        }
        a[i] -= 2; reset(n);
        if(chk()){
            print(ret + 1); return;
        }
        a[i]++;
    }

    vi c;
    int hi = -1;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < 32; ++j){
            if(a[i] >> j & 1){
                if(j > hi){
                    c.clear();
                    hi = j;
                }

                if(j == hi){
                    c.pb(i);
                }
                break;
            }
        }
    }

    a[c[0]]--; ++ret;
    if(sz(c) > 1){
        a[c[1]]++; ++ret;
    }

    print(ret);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    FOR(i,0,n){
        test_case(i + 1);
    }

    return 0;
}
