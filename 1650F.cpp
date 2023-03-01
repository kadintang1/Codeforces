#include <bits/stdc++.h>
using namespace std;

const long long INF = 2e15;
void test_case(){
    int n, m; cin >> n >> m;
    vector<int> a(n), ans;
    for(int i = 0; i < n; ++i) cin >> a[i];
    vector<vector<array<int, 3>>> options(n);
    for(int i = 0; i < m; ++i){
        int e, t, p; cin >> e >> t >> p; --e;
        options[e].push_back({t, p, i});
    }

    vector<long long> min_time(n, INF);
    for(int i = 0; i < n; ++i){
        int m = options[i].size();
        vector<long long> dp(201, INF); dp[0] = 0LL;
        vector<vector<int>> get_best(201, vector<int>(m, -1));
        for(int j = 0; j < m; ++j){
            const auto [t, p, id] = options[i][j];
            for(int k = 200; k >= 0; --k){
                get_best[k][j] = (j - 1 >= 0 ? get_best[k][j-1] : -1);
                if(k >= p){
                    long long time = dp[k - p] + t;
                    if(time < dp[k]){
                        dp[k] = time;
                        get_best[k][j] = j;
                    }
                }
            }
        }

        int best_perc = -1;
        for(int j = 100; j <= 200; ++j){
            if(min_time[i] > dp[j]){
                min_time[i] = dp[j];
                best_perc = j;
            }
        }

        for(int cur_it = m - 1; best_perc > 0; --cur_it){
            if(!cur_it || get_best[best_perc][cur_it] != get_best[best_perc][cur_it - 1]){
                ans.push_back(options[i][get_best[best_perc][cur_it]][2]);
                best_perc -= options[i][get_best[best_perc][cur_it]][1];
            }
        }
    }

    long long cur_time = 0;
    for(int i = 0; i < n; ++i){
        cur_time += min_time[i];
        if(cur_time > a[i]){
            cout << "-1\n"; return;
        }
    }

    cout << ans.size() << '\n';
    for(auto& x : ans){
        cout << x + 1 << " ";
    }
    cout << '\n';
}

int main(){ 
    ios::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while(t--){
        test_case();
    }

    return 0;
}
