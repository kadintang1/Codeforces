#include <bits/stdc++.h>
using namespace std;

void solve(){
    // At most sqrt(n) distinct cnt values .-.
    // For each bucket j, we perform O(n) operations
    // But there are only sqrt(n) buckets max -> O(nsqrt(n)log(m))

    int n, m; cin >> n >> m;
    map<int, int> freq_mp;
    for(int i=0, x; i<n; ++i){
        cin >> x; freq_mp[x]++;
    }

    vector<pair<int, int>> forbid(m);
    for(auto& x : forbid){
        cin >> x.first >> x.second;
    }

    sort(forbid.begin(), forbid.end());
    map<int, vector<int>> mp;
    for(auto& x : freq_mp){
        mp[x.second].push_back(x.first);
    }

    vector<pair<int, vector<int>>> cnts;
    for(auto& x : mp){
        cnts.push_back(make_pair(x.first, x.second));
    }

    for(int i = 0; i < cnts.size(); ++i){
        sort(cnts[i].second.begin(), cnts[i].second.end());
    }

    long long ans = 0;
    for(int i = 0; i < cnts.size(); ++i){
        for(int j = i; j < cnts.size(); ++j){
            vector<int>& x = cnts[i].second;
            vector<int>& y = cnts[j].second;
            int cnt_i = cnts[i].first, cnt_j = cnts[j].first;
            if(i == j){
                // same bucket
                for(int i1 = x.size() - 1; i1 >= 0; --i1){
                    for(int i2 = i1 - 1; i2 >= 0; --i2){
                        int lo = x[i2], hi = x[i1];
                        auto it = lower_bound(forbid.begin(), forbid.end(), make_pair(lo, hi));
                        if(it != forbid.end() && *it == make_pair(lo, hi)){
                            continue;
                        }
                        ans = max(ans, (cnt_i + cnt_j) * (long long) (lo + hi));
                        break;
                    }
                }
            } else{
                for(int i1 = x.size() - 1; i1 >= 0; --i1){
                    for(int i2 = y.size() - 1; i2 >= 0; --i2){
                        int lo = min(x[i1], y[i2]);
                        int hi = max(x[i1], y[i2]);
                        auto it = lower_bound(forbid.begin(), forbid.end(), make_pair(lo, hi));
                        if(it != forbid.end() && *it == make_pair(lo, hi)){
                            continue;
                        }
                        ans = max(ans, (cnt_i + cnt_j) * (long long) (lo + hi));   
                        break;
                    }
                }
            }
        }
    }

    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while(t--){
        solve();
    }

    return 0;
}
