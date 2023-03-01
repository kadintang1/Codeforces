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

int p[55], sz[55], n, m;
int find(int u){
    return u==p[u]?u:p[u]=find(p[u]);
}

bool unite(int u, int v){
    if((u=find(u))==(v=find(v))) return 0;
    if(sz[u]<sz[v]) swap(u, v);
    sz[u]+=sz[v];
    p[v] = u;
    return 1;
}

vector<int> calc_mst(int x, vector<array<int, 3>>& edges){
    vector<int> ret;
    FOR(i,0,n){
        p[i] = i, sz[i] = 1;
    }

    vector<array<int, 4>> cur_edges(m);
    FOR(i,0,m){
        cur_edges[i] = {abs(edges[i][2]-x), edges[i][0], edges[i][1], edges[i][2]};
    }

    sort(all(cur_edges));
    for(array<int, 4>& e : cur_edges){
        int u = e[1], v = e[2];
        if(unite(u, v)){
            ret.pb(e[3]);
        }
    }

    sort(all(ret));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // At most O(m^2) distinct MST
    // To prove, let e1, e2,.. , en be a particular ordering
    // For w = k, then, notice if we increase w -> k + 1
    // This can shift can change the ordering
    // * For every two edges, there is a pivot that entails a swap
    // * There are (m choose 2) = O(m^2) pivots

    cin >> n >> m;
    vector<array<int, 3>> edges(m);
    FOR(i,0,m){
        int u, v, w; cin >> u >> v >> w; --u; --v;
        edges[i] = {min(u, v), max(u, v), w};
    }

    map<int, vector<int>> mst_edges;
    const int INF = 1e8;
    int cur_pivot = 0;
    while(cur_pivot <= INF){
        int l = cur_pivot, r = INF;
        vector<int> base_mst = calc_mst(cur_pivot, edges);
        while(l < r){
            int mid = (l+r+1)/2;
            if(calc_mst(mid, edges) == base_mst){
                l = mid;
            } else{
                r = mid - 1;
            }
        }
        mst_edges[l] = base_mst;
        cur_pivot = l + 1;
    }

    ll p, k, a, b, c; cin >> p >> k >> a >> b >> c;
    ll sum_xor = 0;
    for(int i=0, q; i<k; ++i){
        if(i < p){
            cin >> q;
        } else{
            q = (q * a + b) % c;
        }
        auto it = mst_edges.lower_bound(q);
        ll cost = 0;
        for(auto& x : it->second){
            cost += abs(x - q);
        }
        sum_xor ^= cost;
    }

    cout << sum_xor << nl;
    return 0;
}
