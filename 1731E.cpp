#include <bits/stdc++.h>
using namespace std;
 
#define dbg(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }
 
const int N = 5e5;
int64_t dp[N + 5], p[N + 5], gp[N + 5], cnt[N + 5];
void test_case(){
    int64_t n, m; cin >> n >> m;
    // # pairs where gcd(u, v) = k >= # pairs where gcd(u, v) = k + 1, Vk >= 1
    // we can probably greedily choose? in decreasing order
    // how many pairs (u,v) s.t gcd(u,v)=T?
    // [x, 2*x, 3*x, ...., nx] -> [1, 2, 3, ..., n], x=T
    // and we can determine the # such relatively prime pairs? in transformed array
    // dynamic programming lol
 
    int64_t cost = m;
    for(int i = n; i >= 2; --i) {
        int64_t mf = min(dp[n / i] / (i - 1), m / (i - 1));
        m -= mf * (i - 1), cost += mf;
    }
 
    if(!m) {
        cout << cost << '\n';
    } else{
        cout << -1 << '\n';
    }
}
 
int main() {
    ios::sync_with_stdio(0); cin.tie(NULL);
    for(int i = 1; i < N; ++i) {
        p[i] = 1;
    }
 
    for(int64_t i = 2; i <= N; ++i) {
        if(!p[i]) continue;
        gp[i] = i;
        for(int64_t j = i * i; j <= N; j += i) {
            p[j] = 0, gp[j] = i;
        }
    }
 
    for(int i = 2; i <= N; ++i) {
        // find all prime factors of N
        dp[i] = dp[i - 1] + (i - 1);
        vector<int> pf;
        int ti=i;
        while(ti > 1) {
            pf.push_back(gp[ti]);
            assert(gp[ti] >= 2 && ti % gp[ti] == 0);
            int rf = gp[ti];
            while(ti % rf == 0) {
                ti /= rf;
            }
        }
 
        int n = pf.size();
        for(int j = 1; j < 1 << n; ++j) {
            int sgn = __builtin_popcount(j) & 1 ? -1 : 1, prod = 1;
            for(int k = 0; k < n; ++k) {
                if(j >> k & 1) {
                    prod *= pf[k];
                }
            }
            dp[i] += cnt[prod] * sgn; cnt[prod] += 1;
        }
    }
 
    int t; cin >> t;
    while(t--){
        test_case();
    }
    return 0;
}
