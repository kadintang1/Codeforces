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

const int N = 2005;
bool dp[N][N];
void test_case(){
    int n, k; cin >> n >> k;
    vector<array<int, 5>> loc;
    FOR(i,0,n){
        FOR(j,0,n){
            int x; cin >> x;
            loc.pb({x, i, j, i+j, i-j});
        }
    }

    sort(all(loc), greater<array<int, 5>>());
    int q1_min = loc[0][3], q1_max = loc[0][3], q2_min = loc[0][4], q2_max = loc[0][4];
    auto chk = [&](int i, int j){
        return abs(i - q1_min) <= k && abs(i - q1_max) <= k && abs(j - q2_min) <= k && abs(j - q2_max) <= k;
    };

    for(array<int, 5>& pos : loc){
        if(chk(pos[3], pos[4])){
            dp[pos[1]][pos[2]] = 1;
            umin(q1_min, pos[3]);
            umax(q1_max, pos[3]);
            umin(q2_min, pos[4]);
            umax(q2_max, pos[4]);
        }
    }


    FOR(i,0,n){
        FOR(j,0,n){
            if(dp[i][j]){
                cout << "M";
            } else{
                cout << "G";
            }
        }
        cout << nl;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    // int t; cin >> t;
    // FOR(i,0,t){
        test_case();
    // }

    return 0;
}
