#include <bits/stdc++.h>
#include <vector>
using namespace std;

typedef long long ll;
#define nl "\n"
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define FORd(i, b, a) for(int i = b; i >= a; --i)
#define ROF(i, b, a) for(int i = b; i >= a; --i)
#define trav(a, x) for(auto &a : x)
#define pi pair<int, int>
#define pb push_back
#define ff first
#define ss second

template<class T> bool umin(T& a, T b){
    return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T b){
    return a<b?a=b,1:0;
}

template<class T> T inv(T a, T b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1;
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

void solve(){
    // if we pick a1, a2
    // case 1: min(a1, a2) > 0
    // -> then for all ak where k >= 3, we either pick the max or 0
    // --> if we pick the max, then obviously, when we pick the 0
    // --> on our second pass through, then that will be our next best_ans
    // --> correct
    // -> if we pick the 0, then same logic. 
    // --> on our second pass through, we will eventually pick the max
    // --> and then our best_ans will be updated to this index
    // --> return ans_1, ans_2 (indices of max and 0)

    // case 2: min(a1, a2) == 0
    // 
    int n; cin >> n;
    int max_diff_1 = -1, ans_1 = -1, cnt_1 = 0;
    for(int i=3; i<=n; ++i){
        cout << "? 1 2 " << i << nl;
        cout.flush();
        int x; cin >> x;
        assert(x >= 0);
        if(x != max_diff_1){
            ++cnt_1;
        }
        if(x > max_diff_1){
            max_diff_1 = x; ans_1 = i;
        }
    }

    int ans_2 = -1, max_diff_2 = -1, cnt_2 = 0;
    // ans_1 has the max or 0.
    // actually not necessarily true: [0,9,8,8]
    for(int i=2; i<=n; ++i){
        if(i == ans_1){
            continue;
        }

        cout << "? 1 " << ans_1 << " " << i << nl;
        cout.flush();
        int x; cin >> x;
        assert(x >= 0);
        if(x != max_diff_2){
            ++cnt_2;
        }

        if(x > max_diff_2){
            max_diff_2 = x; ans_2 = i;
        }
    }

    // fails on [0,9,8,8] >_>
    // dbg(max_diff_1);
    // dbg(max_diff_2);

    // [1, 9, 2, 0]
    if(max_diff_1 == max_diff_2 && cnt_1 == 1){
        cout << "! " << 1 << " " << 2 << nl; cout.flush(); return;
    }

    if(cnt_2 == 1){
        cout << "! " << 1 << " " << ans_1 << nl; cout.flush();
    } else{
        cout << "! " << ans_1 << " " << ans_2 << nl; cout.flush();
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while(t--){
        solve();
    }

    return 0;
}
