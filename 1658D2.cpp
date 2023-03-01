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
    int l, r; cin >> l >> r;
    int n = r - l + 1;
    vi a(n);
    EACH(x, a) cin >> x;

    // wait we can use a trie .-.
    // see whether max xor is <= r.
    int tr[20 * n][2]; memset(tr, 0, sizeof(tr));
    int t = 0;
    EACH(x, a){
        int u = 0;
        FORd(i,17,0){
            int bit = x >> i & 1;
            if(!tr[u][bit]){
                tr[u][bit] = ++t;
            }
            u = tr[u][bit];
        }
    }

    EACH(x, a){
        x ^= l;
        int mx = 0, mn = 0, u = 0;
        FORd(i,17,0){
            int bit = x >> i & 1;
            if(tr[u][bit ^ 1]){
                mx |= (1 << i);
                u = tr[u][bit ^ 1];
            } else{
                u = tr[u][bit];
            }
        }

        u = 0;
        FORd(i,17,0){
            int bit = x >> i & 1;
            if(tr[u][bit]){
                u = tr[u][bit];
            } else{
                mn |= (1 << i);
                u = tr[u][bit ^ 1];
            }
        }

        if(mx == r && mn == l){
            cout << x << nl; return;
        }
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
