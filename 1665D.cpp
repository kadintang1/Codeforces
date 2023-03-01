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
#define pl pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define vpi vector<pair<int, int>>
#define mi map<int, int>
#define pb push_back
#define ff first
#define ss second
#define al array<ll, 3>

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
    // gcd(x + a, x + b) = gcd(x + a,  b - a)
    // 100
    // 101, 111
    // 110, 1000

    // 7
    // 8 10
    // 8 12
    // 8 16
    // 8 24

    // 111
    // 1, 3: 1000, 1010
    // add: 2 - 1
    // add: 2^2 - 3

    // need to flip all lower bits (add 2 ^ x - sum)
    // 
    ll ret = 0;
    for(int i=0; i<30; ++i){
        ll add = (1 << (i + 1)) - ret - (1 << i);
        cout << "? " << add << " " << add + (1 << (i + 1)) << nl;
        cout.flush();
        ll x; cin >> x;
        if(x % (1 << (i + 1)) == 0){
            ret += (1 << i);
        }
    }
    cout << "! " << ret << nl;
    cout.flush();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    FOR(i,0,t){
        test_case();
    }

    return 0;
}
