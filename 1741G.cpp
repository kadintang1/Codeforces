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

ll inv(ll a, ll b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1LL;
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

const int INF = 1e9;
void test_case(){
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int f; cin >> f;
    vector<int> loc(f);
    for(auto& x : loc) {
        cin >> x; x -= 1;
    }

    int k; cin >> k;
    vector<int> no_car(k), get_mask(n);
    for(int i = 0; i < k; ++i) {
        cin >> no_car[i]; no_car[i] -= 1;
        int x = no_car[i];
        get_mask[loc[x]] |= 1 << i;
    }

    queue<int> q; q.push(0);
    vector<set<int>> get_masks(n);
    vector<int> dist(n, INF); dist[0] = 0; 
    get_masks[0].insert(get_mask[0]);

    while(q.size() > 0) {
        auto u = q.front(); q.pop();

        for(auto& v : adj[u]) {
            if(dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1; q.push(v);
            }

            if(dist[v] == dist[u] + 1) {
                for(auto& msk : get_masks[u]) {
                    get_masks[v].insert(msk | get_mask[v]);
                }
            }
        }
    }

    vector<bool> ok(1 << k); ok[0] = 1;
    for(int i = 0, j = 0; i < f; ++i) {
        if(find(no_car.begin(), no_car.end(), i) != no_car.end()) {
            continue;
        }
        vector<bool> nok = ok;
        for(int j = 0; j < 1 << k; ++j) {
            for(auto& msk : get_masks[loc[i]]) {
                if(ok[j]) {
                    nok[j | msk] = 1;
                }
            }
        }
        ok = nok;
    }

    int ans = k;
    for(int i = 0; i < 1 << k; ++i) {
        if(ok[i]) {
            int cans = 0;
            for(int j = 0; j < k; ++j) {
                if(!(i >> j & 1)) {
                    cans += 1;
                }
            }
            ans = min(ans, cans);
        }
    }

    cout << ans << '\n';
}

int main() {
    int t; cin >> t;
    while(t--){
        test_case();
    }
    return 0;
}
