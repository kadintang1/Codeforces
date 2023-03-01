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
#define arr array
#define pi pair<int, int>
#define vi vector<int>
#define vpi vector<pair<int, int>>
#define mi map<int, int>
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

const int N = 200005;
int p[N], nxt[N];
int find(int u){
    return u == p[u] ? u : p[u] = find(p[u]);
}

void unite(int u, int v){
    u = find(u);
    v = find(v);
    if(u == v) return;
    p[u] = v;
    nxt[v] = min(nxt[v], nxt[u]);
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL);
    int n, q; cin >> n >> q;
    for(int i = 0; i <= n + 1; ++i){
        p[i] = i; nxt[i] = N;
    }
    while(q--){
        int t, l, r, x;
        cin >> t;
        if(t){
            cin >> x;
            if(p[x] ^ x){
                cout << "NO" << nl;
            } else{
                if(nxt[x] < find(x+1)){
                    cout << "YES" << nl;
                } else{
                    cout << "N/A" << nl;
                }
            }
        } else{
            cin >> l >> r >> x;
            l = find(l);
            if(x){
                nxt[l] = min(nxt[l], r);
            } else{
                while(l <= r){
                    unite(l, l+1);
                    l = find(l);
                }
            }
        }
    }
    return 0;
}
