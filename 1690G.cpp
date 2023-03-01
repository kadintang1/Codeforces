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

void test_case(){
    // okay, so v[i] = min(prefix, v[i]);
    // always decreasing..
    // only trains to the right are influenced
    // so, if speed decreases, but min(prefix) <= t[i], nothing changes
    // if speed decreases, and min(prefix) > t[i], +1 to our train chain
    // we also have to consider the possible concatenation of trains
    // to our right....
    // reset all values in the range to 0? get closest slowest train to the right
    // so much code...

    int n, m; cin >> n >> m;
    vi c(n);
    FOR(i,0,n){
        cin >> c[i];
    }

    map<int, int> mp;
    auto ins = [&](int i, int x){
        mp[i] = x;
        auto it = mp.find(i);
        if(it != mp.begin() && x >= prev(it)->second){
            mp.erase(it); return;
        }

        while(next(it) != mp.end() && x <= next(it)->second){
            mp.erase(next(it));
        }
    };

    FOR(i,0,n){
        ins(i, c[i]);
    }

    FOR(i,0,m){
        int id, delta; cin >> id >> delta; --id;
        c[id] -= delta;
        ins(id, c[id]);
        cout << sz(mp) << " ";
    }
    cout << nl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    FOR(i,0,t){
        test_case();
    }

    return 0;
}
