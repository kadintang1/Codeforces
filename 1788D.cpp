#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

const int M = 1e9 + 7;
void test_case() {
    int n; cin >> n;
    vector<int> A(n);
    for(auto& x : A) cin >> x;

    int64_t ans = 0;
    vector<int64_t> bpow(n + 5, 1);
    for(int i = 1; i <= n; ++i) {
        bpow[i] = (bpow[i - 1] * 2) % M;
    }
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            int ll = 0, lr = i - 1;
            int rl = j + 1, rr = n - 1;
            while(ll < lr) {
                int m = (ll + lr + 1) >> 1;
                if(A[i] - A[m] > A[j] - A[i]) {
                    ll = m;
                } else{
                    lr = m - 1;
                }
            }
            while(rl < rr) {
                int m = (rl + rr) >> 1;
                if(A[m] - A[j] >= A[j] - A[i]) {
                    rr = m;
                } else{
                    rl = m + 1;
                }
            }
            int64_t cans = 1;
            if(A[i] - A[ll] > A[j] - A[i]) {
                cans = (cans * bpow[ll + 1]);
            }
            if(A[rl] - A[j] >= A[j] - A[i]) {
                cans = (cans * bpow[n - rl]);
            }

            ans = (ans + cans) % M;
        }
    }
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(0); cin.tie(NULL);

    // int t; cin >> t;
    // for(int i = 0; i < t; ++i) {
        test_case();
    // }

    return 0;
}
