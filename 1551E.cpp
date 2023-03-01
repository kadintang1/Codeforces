#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <deque>
#include <tgmath.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define f first
#define s second
#define endl "\n"
void solve(){
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(int i = 0; i < n; ++i){
        cin >> v[i];
    }

    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    int res = 2e9;
    for(int i = 1; i <= n; ++i){
        if(v[i-1] <= i){
            int rem = i - v[i-1];
            dp[i][rem] = max(dp[i][rem], dp[i-1][rem] + 1);
            if(dp[i][rem] >= k){
                res = min(res, rem);
            }
        }
        dp[i][0] = max(dp[i][0], dp[i-1][0]);
        for(int j = 1; j <= i; ++j){
            dp[i][j] = max(dp[i][j], max(dp[i-1][j-1], dp[i-1][j]));
            if(dp[i][j] >= k){
                res = min(res, j);
            }
        }
    }

    cout << (res == 2e9 ? -1 : res) << endl;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while(t--){
        solve();
    }    

    return 0;
}
