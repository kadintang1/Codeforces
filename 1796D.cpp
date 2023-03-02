#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << ": " << x << '\n'
#define ll long long
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

void test_case() {
    int n, k, x; cin >> n >> k >> x;
    vector<long long> a(n), pf(n + 1), sf(n + 1);
    for(auto& x : a) cin >> x;
    for(int i = 0; i < n; ++i) {
        pf[i + 1] = pf[i] + a[i];
    }
    for(int i = n - 1; ~i; --i) {
        sf[i] = sf[i + 1] + a[i];
    }
    long long ans = 0;
    if(k == 0) {
        for(auto& t : a) t -= x;
        long long csum = 0;
        for(auto& t : a) {
            csum = max(csum + t, t);
            ans = max(ans, csum);
        }
        cout << ans << '\n'; return;
    }
    if(x >= 0) {
        vector<vector<long long>> rs(n + 1, vector<long long>(k + 1));
        vector<vector<long long>> ls(n + 1, vector<long long>(k + 1));
        vector<long long> dpR(n + 1), dpL(n + 1);
        for(int i = 0; i < n; ++i) {
            dpL[i + 1] = max({dpL[i + 1], dpL[i] + a[i] - x, a[i] - x});
        }

        for(int i = n - 1; ~i; --i) {
            dpR[i] = max({dpR[i], dpR[i + 1] + a[i] - x, a[i] - x});
        }

        for(int i = 0; i < n; ++i) {
            for(int j = 1; j <= k; ++j) {
                ls[i + 1][j] = pf[i + 1] - pf[max(0, i + 1 - j)] + min(i + 1, j) * (long long) x;
                rs[i][j] = sf[i] - sf[min(n, i + j)] + min(n - i, j) * (long long) x;
            }
        }

        for(int i = 0; i < n; ++i) {
            for(int nl = 0; nl <= k - 1; ++nl) {
                for(int nr = 0; nr + nl <= k - 1; ++nr) {
                    long long L = dpL[max(0, i - nl)];
                    long long l = ls[i][nl];
                    long long R = dpR[min(n, i + 1 + nr)];
                    long long r = rs[i + 1][nr];
                    ans = max(ans, a[i] + x + L + l + R + r);
                }
            }
        }
    } else{
        x *= -1, k = n - k;
        for(int L = 0; L + k - 1 < n; ++L) {
            long long csum = 0;
            for(int i = 0; i < n; ++i) {
                if(L <= i && i <= L + k - 1) {
                    csum = max(csum + a[i] + x, a[i] + x);
                } else{
                    csum = max(csum + a[i] - x, a[i] - x);
                }
                ans = max(ans, csum);
            }
        }
    }
    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int t; cin >> t;
    for(int i = 0; i < t; ++i) {
        test_case();
    }


    return 0;
}
