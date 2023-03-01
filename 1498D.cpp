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
#include <stack>
#include <deque>
#include <tgmath.h>
#define ll long long
#define ull unsigned long long
#define f first
#define s second
#define endl "\n"

using namespace std;
const ll mult = 1e5;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m; cin >> n >> m;
    vector<int> dp(m+1, 10000), prev(m+1, false);
    prev[0] = true;
    for(int i = 1; i <= n; ++i){
        ll t, x, y; cin >> t >> x >> y;
        for(int j = m; ~j; --j){
            if(prev[j]){
                for(ll nextIdx = t==1?(j+(x+mult-1)/mult):(j*x+mult-1)/mult, it = 0; nextIdx <= m && it < y; nextIdx=(t==1?nextIdx+(x+mult-1)/mult:(nextIdx*x+mult-1)/mult), ++it){
                    if(prev[nextIdx]){
                        break;
                    }
                    prev[nextIdx] = true;
                    dp[nextIdx] = min(dp[nextIdx], i);
                }
            }
        }
    }


    for(int i = 1; i <= m; ++i){
        cout << (dp[i]==10000?-1:dp[i]) << " ";
    }

    return 0;
}
