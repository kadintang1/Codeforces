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
const int mxN = 2e5;
int p[2*mxN], sz[2*mxN], valid[2*mxN];
priority_queue<int, vector<int>, greater<int>> in[2*mxN];
priority_queue<int> out[2*mxN];
priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> pq;
int find(int u){
    return u==p[u]?u:p[u]=find(p[u]);
}

ll unite(int u, int v){
    if((u=find(u))==(v=find(v))) return 0;
    if(sz[u]<sz[v]) swap(u, v);
    p[v] = u; sz[u] += sz[v]; valid[u] += valid[v];
    ll delta = 0;

    while(sz(out[v])){
        out[u].push(out[v].top()); out[v].pop(); // okay
    }

    while(sz(in[v])){
        out[u].push(in[v].top()); delta -= in[v].top(); in[v].pop(); // okay
    }

    while(sz(in[u]) < valid[u]){
        in[u].push(out[u].top()); delta += out[u].top(); out[u].pop(); // okay
    }

    while(sz(out[u]) && sz(in[u]) && in[u].top() < out[u].top()){ // okay
        int value = in[u].top(); in[u].pop();
        delta += out[u].top() - value;
        in[u].push(out[u].top());
        out[u].pop(); out[u].push(value);
    }
    return delta;
}

void solve(){
    int n, m, q; cin >> n >> m >> q;
    vector<array<int, 2>> a(n+m), c(q);
    ll ans = 0;
    for(int i=0; i<n; ++i){
        p[i] = i; sz[i] = 1; valid[i] = 1;
        cin >> a[i][0]; a[i][1] = i;
        in[i].push(a[i][0]);
        ans += a[i][0];
    }

    for(int i=n; i<n+m; ++i){
        p[i] = i; sz[i] = 1; valid[i] = 0;
        cin >> a[i][0]; a[i][1] = i;
        out[i].push(a[i][0]);
    }

    for(int i=0; i<q; ++i){
        cin >> c[i][0]; c[i][1] = i;
    }

    sort(a.begin(), a.end());
    sort(c.begin(), c.end());
    for(int i=1; i<n+m; ++i){
        pq.push({a[i][0]-a[i-1][0], a[i-1][1], a[i][1]});
    }

    vector<ll> ret(q);
    for(int i=0; i<q; ++i){
        while(sz(pq)&&pq.top()[0] <= c[i][0]){
            array<int, 3> e = pq.top(); pq.pop();
            ans += unite(e[1], e[2]);
        }
        ret[c[i][1]] = ans;
    }

    trav(x, ret){
        cout << x << nl;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
    return 0;
}
