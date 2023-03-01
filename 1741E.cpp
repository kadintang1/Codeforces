#include <bits/stdc++.h>
using namespace std;

const int INF = 2e5 + 5;

struct RMQ{
    vector<int> val, stLeft, stRight;
    RMQ(int n){
        val = vector<int>(4 * n, -INF);
        stLeft = vector<int>(4 * n);
        stRight = vector<int>(4 * n);
        build(0, n - 1);
    };

    void build(int l, int r, int i=1){
        stLeft[i] = l; stRight[i] = r;
        if(l == r){
            return;
        }
        int m = (l + r) >> 1;
        build(l, m, 2*i), build(m+1, r, 2*i+1);
    }

    int rangeMax(int l, int r, int i=1){
        if(stRight[i] < l || r < stLeft[i]){
            return -INF;
        }
        if(l <= stLeft[i] && stRight[i] <= r){
            return val[i];
        }
        return max(rangeMax(l, r, 2*i), rangeMax(l, r, 2*i+1));
    }

    void upd(int l, int r, int upd_value, int i=1){
        if(stRight[i] < l || r < stLeft[i]){
            return;
        }
        if(l <= stLeft[i] && stRight[i] <= r){
            val[i] = upd_value;
            return;
        }
        upd(l, r, upd_value, 2*i);
        upd(l, r, upd_value, 2*i+1);
        val[i] = max(val[2*i], val[2*i+1]);
    }
};

void test_case(){
    int n; cin >> n;
    vector<array<int, 3>> s(n);
    vector<vector<array<int, 3>>> c(n);
    vector<int> get_val;
    for(int i = 0; i < n; ++i) {
        cin >> s[i][0] >> s[i][1] >> s[i][2]; s[i][2] -= 1;
        get_val.push_back(s[i][0]); get_val.push_back(s[i][1]);    
    }

    sort(get_val.begin(), get_val.end());
    get_val.resize(unique(get_val.begin(), get_val.end()) - get_val.begin());

    for(int i = 0; i < n; ++i) {
        array<int, 3> seg = s[i];
        int L = lower_bound(get_val.begin(), get_val.end(), seg[0]) - get_val.begin();
        int R = lower_bound(get_val.begin(), get_val.end(), seg[1]) - get_val.begin();
        c[seg[2]].push_back({L, R, i});
    }

    vector<multiset<int>> gr(2 * n);
    multiset<array<int, 2>> st;
    for(int i = 0; i < n; ++i) {
        for(array<int, 3>& seg : c[i]) {
            gr[seg[0]].insert(seg[1]);
            st.insert({seg[0], seg[1]});
        }
    }

    RMQ mx_right(2 * n + 5);
    for(int i = 0; i < 2 * n; ++i) {
        if(gr[i].size() > 0) {
            int X = *gr[i].rbegin();
            mx_right.upd(i, i, X);
        }
    }

    function<int(int)> conv = [&](int x) {
        if(x < 0) return x;
        return get_val[x];
    };

    vector<int> ans(n, INT_MAX);
    for(int i = 0; i < n; ++i){
        for(array<int, 3>& seg : c[i]) {
            int L = seg[0], R = seg[1];
            gr[L].erase(gr[L].find(R));
            int rmax = gr[L].size() > 0 ? *gr[L].rbegin() : -INF;
            mx_right.upd(L, L, rmax);
            st.erase(st.find({L, R}));
        }

        for(array<int, 3>& seg : c[i]) {
            int L = seg[0], R = seg[1], mR = mx_right.rangeMax(0, R);
            if(mR >= L) {
                ans[seg[2]] = 0;
            } else{
                if(mR >= 0) {
                    ans[seg[2]] = conv(L) - conv(mR);
                }
                auto it = st.lower_bound({R, R});
                if(it != st.end()) {
                    ans[seg[2]] = min(ans[seg[2]], conv((*it)[0]) - conv(R));
                }
                assert(ans[seg[2]] > 0);
            }
        }

        for(array<int, 3>& seg : c[i]) {
            int L = seg[0], R = seg[1];
            gr[L].insert(R);
            int rmax = *gr[L].rbegin();
            mx_right.upd(L, L, rmax);
            st.insert({L, R});
        }
    }

    for(auto& x : ans) {
        cout << x << " ";
    }
    cout << '\n';
}

int main() {
    int t; cin >> t;
    while(t--){
        test_case();
    }
    return 0;
}
