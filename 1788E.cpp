#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

const int MAX = 2e5;
long long stLeft[4 * MAX], stRight[4 * MAX], val[4 * MAX];
void build(int l, int r, int i = 1){
    stLeft[i] = l; stRight[i] = r;
    if(l == r){
        val[i] = -MAX; return;
    }
    int m = (l + r) >> 1;
    build(l, m, 2 * i); build(m + 1, r, 2 * i + 1);
    val[i] = max(val[2 * i], val[2 * i + 1]);
}

long long rangeMax(int l, int r, int i = 1){
    if(stLeft[i] > r || stRight[i] < l){
        return -MAX;
    }
    if(l <= stLeft[i] && stRight[i] <= r){
        return val[i];
    }
    return max(rangeMax(l, r, 2 * i), rangeMax(l, r, 2 * i + 1));
}

void update(int l, int r, int upd_val, int i = 1){
    if(stLeft[i] > r || stRight[i] < l){
        return;
    }
    if(l <= stLeft[i] && stRight[i] <= r){
        val[i] = max(val[i], (long long) upd_val); return;
    }
    update(l, r, upd_val, i << 1); update(l, r, upd_val, (i << 1) + 1);
    val[i] = max(val[2 * i], val[2 * i + 1]);
}

void test_case() {
    int n; cin >> n;
    vector<int64_t> A(n), dp(n + 1), ps(n + 1), t{0};
    for(auto& x : A) cin >> x;
    for(int i = 0; i < n; ++i) {
        ps[i + 1] = ps[i] + A[i]; t.push_back(ps[i + 1]);
    }

    build(0, n - 1);
    sort(t.begin(), t.end());
    t.resize(unique(t.begin(), t.end()) - t.begin());
    function<int(int64_t)> get_index = [&](int64_t x) {
        int j = lower_bound(t.begin(), t.end(), x) - t.begin();
        assert(j >= 0 && j < t.size());
        return j;
    };
    update(get_index(ps[0]), get_index(ps[0]), 1);
    int64_t ans = 0;
    for(int i = 0; i < n; ++i) {
        int j = get_index(ps[i + 1]);
        dp[i + 1] = max(dp[i], rangeMax(0, j) + i);
        update(j, j, dp[i + 1] - i);
        ans = max(ans, dp[i + 1]);
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
