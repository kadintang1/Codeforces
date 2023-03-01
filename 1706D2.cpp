#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { 
    return os << '(' << p.first << ", " << p.second << ')'; 
}

template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { 
    os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; 
}

const long long INF = 1e5;
int main(){ 
    ios::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    for(int z = 0; z < t; ++z) {
        int n, k; cin >> n >> k;
        vector<int> a(n);
        for(auto& x : a) {
            cin >> x;
        }

        vector<vector<int>> g(a.back() + 1);
        for(int i = 0; i < n; ++i) {
            g[a[i]].push_back(i);
        }

        // How about we consider a greedy approach?
        // Each number a[i] has at most O(sqrt(a[i])) decreases
        // We decrease the largest number, and take the local answer
        // O(nsqrt(n)) ....

        // How to get the next pivot in linear time?
        // Well, if we have N / x = y, and we want the smallest p s.t
        // N / p < y, how do we find it? Well, we know that N / y < p
        // Or N / (N / x) < p, or N / (N / x) <= p - 1, or N / (N / x) + 1 <= p.
        // So, by equality, p = N / (N / x) + 1.
        vector<int> cpivot(n, 1);

        int ans = INF, cur_min = a[0];
        for(int i = a[n - 1]; ~i; --i) {
            for(auto& ind : g[i]) {
                ans = min(ans, i - cur_min);
                cpivot[ind] = a[ind] / (a[ind] / cpivot[ind]) + 1;
                if(cpivot[ind] > min(a[ind], k)) {
                    goto end;
                }
                cur_min = min(cur_min, a[ind] / cpivot[ind]);
                g[a[ind] / cpivot[ind]].push_back(ind);
            }
            g.pop_back();
        }

        end:

        cout << ans << '\n';
    }
    return 0;
}
