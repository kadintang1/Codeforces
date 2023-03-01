#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define nl "\n"
#define trav(a, x) for(auto &a : x)
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define ROF(i, b, a) for(int i = b; i >= a; --i)
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

const ll INF = 1e18;
void solve(){
    int n, m, k; cin >> n >> m >> k;
    vector<pair<int, int>> locs;
    vector<ll> x(n);
    FOR(i,0,n){
        cin >> x[i];
    }

    vector<array<int, 5>> ladders(k);
    FOR(i,0,k){
        int a, b, c, d, h; cin >> a >> b >> c >> d >> h;
        locs.push_back(make_pair(a, b));
        locs.push_back(make_pair(c, d));
        ladders[i] = {a, b, c, d, h};
    }   
    locs.push_back(make_pair(1, 1));
    locs.push_back(make_pair(n, m));

    vector<vector<pair<int, ll>>> adj;
    sort(all(locs));
    locs.resize(unique(all(locs))-locs.begin());
    adj.resize(sz(locs));


    vector<vector<int>> floors;
    vector<int> cur_floor;
    FOR(i,0,sz(locs)){
        cur_floor.push_back(i);
        if(i==sz(locs)-1||(locs[i].ff^locs[i+1].ff)){
            floors.push_back(cur_floor);
            cur_floor.clear();
        }
    }

    for(int i=0; i<sz(floors); ++i){
        vector<int>& cur_floor = floors[i];
        for(int j=0; j+1<sz(cur_floor); ++j){
            int u = cur_floor[j], v = cur_floor[j+1];
            assert(u < v);
            ll w = x[locs[v].ff-1] * (locs[v].ss-locs[u].ss);
            assert(w > 0);
            adj[u].push_back(make_pair(v, w));
            adj[v].push_back(make_pair(u, w));
        }
    }

    vector<ll> dist(sz(locs), INF); dist[0] = 0LL;
    for(array<int, 5>& e : ladders){
        int u = lower_bound(all(locs), make_pair(e[0], e[1]))-locs.begin();
        int v = lower_bound(all(locs), make_pair(e[2], e[3]))-locs.begin();
        assert(locs[u] == make_pair(e[0], e[1]));
        assert(locs[v] == make_pair(e[2], e[3]));
        adj[u].push_back(make_pair(v, -e[4]));
    }

    for(int i=0; i<sz(floors); ++i){
        vector<int>& cur_floor = floors[i];
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        for(int j=0; j<sz(cur_floor); ++j){
            if(dist[cur_floor[j]] != INF){
                pq.push({dist[cur_floor[j]], cur_floor[j]});
            }
        }
        while(sz(pq)){
            pair<ll, int> cur_room = pq.top(); pq.pop();
            int u = cur_room.ss;
            ll w = cur_room.ff;
            if(dist[u]^w){
                continue;
            }

            for(pair<int, ll> e : adj[u]){
                int v = e.ff;
                if(dist[v] > w + e.ss){
                    dist[v] = w + e.ss;
                    if(v <= cur_floor.back()){
                        pq.push({dist[v], v});
                    }
                }
            }
        }
    }

    int targ_index = lower_bound(all(locs), make_pair(n, m)) - locs.begin();
    if(dist[targ_index] == INF){
        cout << "NO ESCAPE" << nl;
    } else{
        cout << dist[targ_index] << nl;
    }
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
