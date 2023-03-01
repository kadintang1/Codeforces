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

void test_case(){
    int n, C; cin >> n >> C;
    vector<ll> b(C + 1), a(C + 1);
    FOR(i,0,n){
        ll x, y, z; cin >> x >> y >> z;
        umax(b[x], y * z);
    }

    for(int i=1; i<=C; ++i){
        if(i>=sz(b)) continue;
        for(int j=1; j*i<=C; ++j){
            umax(a[i*j], b[i] * j);
        }
    }

    FOR(i,1,C+1){
        umax(a[i], a[i-1]);
    }

    int m; cin >> m;
    while(m--){
        ll d, h; cin >> d >> h;
        d *= h;
        int i = upper_bound(all(a), d)-a.begin();
        if(i<=C){
            cout << i << " ";
        } else{
            cout << -1 << " ";
        }
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL);

    // int t; cin >> t;
    // FOR(i,0,t){
        test_case();
    // }

    return 0;
}
