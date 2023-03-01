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
#define EACH(x, a) for (auto& x : a)
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

ll inv(ll a, ll b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1;
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

const int MAXK = 31, INF = 1 << 30;
vector<pi> t;
pi get(int v, int vl, int vr, int l, int r) {
    if(vl >= l && vr <= r){
        return t[v];
    }

    if(r <= vl || l >= vr){
        return make_pair(INF, INF);
    }
    int vm = (vl + vr) >> 1;
    return min(get(v << 1, vl, vm, l, r), get((v << 1) + 1, vm, vr, l, r));
}

void upd(int v, int vl, int vr, int id, int val) {
    if (vr - vl == 1) {
        t[v] = make_pair(val, id);
        return;
    }
    int vm = (vl + vr) >> 1;
    if(id < vm){
        upd(2 * v, vl, vm, id, val);
    } else{
        upd(2 * v + 1, vm, vr, id, val);
    }
    t[v] = min(t[v << 1], t[(v << 1)+ 1]);
}

void test_case() {
    int n; cin >> n;
    vi a(n);
    FOR(i,0,n){
        cin >> a[i];
    }
    t.resize(4 * n);

    FOR(i,0,n){
        upd(1, 0, n, i, a[i]);
    }

    int q; cin >> q;
    while (q--){
        int l, r;
        cin >> l >> r;
        l--;
        vector<pair<int, int>> b;
        FOR(i,0,min(r-l, MAXK)){
            auto it = get(1, 0, n, l, r);
            b.pb(it);
            upd(1, 0, n, it.second, INF);
        }

        int ans = (1LL << 31) - 1;
        FOR(i,0,sz(b)){
            FOR(j,i+1,sz(b)){
                umin(ans, b[i].first | b[j].first);
            }
        }

        EACH(x, b){
            upd(1, 0, n, x.second, x.first);
        }
        cout << ans << nl;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    FOR(i,0,t){
        test_case();
    }

    return 0;
}
