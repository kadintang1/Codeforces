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
#include <cassert>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi; 
typedef vector<vector<int>> vii;
typedef pair<int, int> pi;
typedef pair<long, long> pl;
typedef map<int, int> mapi;
typedef map<long, long> mapl;
typedef vector<long> vl;
typedef vector<vector<long>> vll;

#define endl "\n"
#define FOR(i, a) for(int i = 0; i < a; ++i)
#define FORR(i, a) for(int i = a; ~i; --i)
#define pb(i) push_back(i)
#define bitCount(i) __builtin_popcount(i)
const int mxN = 3e5;
struct SegTree{
    int stLeft[8*mxN], stRight[8*mxN], val[8*mxN], delta[8*mxN];
    void prop(int i){
        val[i] += delta[i];
        delta[2*i] += delta[i];
        delta[2*i+1] += delta[i];
        delta[i] = 0;
    }

    void construct(int i, int l, int r){
        stLeft[i] = l;
        stRight[i] = r;
        if(l == r){
            return;
        }
        int m = (l+r)/2;
        construct(2*i, l, m);
        construct(2*i+1, m+1, r);
    }

    int query(int i, int l, int r){
        if(stRight[i] < l || r < stLeft[i]){
            return 2e9;
        }
        if(l <= stLeft[i] && stRight[i] <= r){
            return val[i] + delta[i];
        }
        prop(i);
        return min(query(2*i, l, r), query(2*i+1, l, r));
    }

    void upd(int i, int l, int r, int sign){
        if(stRight[i] < l || r < stLeft[i]){
            return;
        }
        if(l <= stLeft[i] && stRight[i] <= r){
            delta[i] += sign;
            return;
        }
        prop(i);
        upd(2*i, l, r, sign);
        upd(2*i+1, l, r, sign);
        val[i] = min(val[2*i] + delta[2*i], val[2*i+1] + delta[2*i+1]);
    }
};

void solve(){
    int n, m; cin >> n >> m;
    //use a segment tree to check for interval validity
    //sort intervals by their weights
    //do a sliding window over the intervals

    vector<vector<int>> intervals(n);
    for(int i = 0; i < n; ++i){
        int l, r, w; cin >> l >> r >> w;
        intervals[i] = {w, --l, --r};
    }

    sort(intervals.begin(), intervals.end());
    SegTree st;
    st.construct(1, 0, m-1);
    int res = 2e9;
    //[i, j]
    for(int i = 0, j = -1; j < n || st.query(1, 0, m-2); ++j){
        while(st.query(1, 0, m-2)){
            res = min(res, intervals[j][0] - intervals[i][0]);
            st.upd(1, intervals[i][1], intervals[i][2]-1, -1);
            ++i;
        }
        if(j+1 < n){
            st.upd(1, intervals[j+1][1], intervals[j+1][2]-1, 1);
        }
    }

    cout << res << endl;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}
