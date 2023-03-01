#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define nl "\n"
#define vi vector<int>
#define trav(a, x) for(auto &a : x)
#define pb push_back
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define ROF(i, b, a) for(int i = b; i >= a; --i)
#define arr array

template<class T> bool umin(T& a, T b){
    return b<a?a=b,1:0;
}

template<class T> bool umax(T& a, T b){
    return a<b?a=b,1:0;
}

template<class T> T inv(T a, T b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1;
}

template<class R, class S> pair<R, S> operator+(const pair<R, S>& p1, const pair<R, S>& p2){
    return pair<R, S>(p1.first+p2.first, p1.second+p2.second);
}

template<class R, class S> pair<R, S> operator-(const pair<R, S>& p1, const pair<R, S>& p2){
    return pair<R, S>(p1.first-p2.first, p1.second-p2.second);
}

template<class R, class S> pair<R, S> operator*(const pair<R, S>& p1, const pair<R, S>& p2){
    return pair<R, S>(p1.first*p2.first, p1.second*p2.second);
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

void solve(){
    int n, m; cin >> n >> m;
    vector<string> nums(n);
    trav(x, nums) cin >> x;
    string s; cin >> s;
    map<string, array<int ,3>> mp;

    {
        for(int k=0; k<n; ++k){
            for(int i=0; i<m; ++i){
                for(int j=2; j<=3 && i+j<=m; ++j){
                    if(mp.find(nums[k].substr(i,j))!=mp.end()) continue;
                    mp[nums[k].substr(i,j)] = {i+1, i+1+j-1, k+1};
                }
            }
        }
    }

    // just break the number into segments of len 2, 3
    bool dp[m+1]; memset(dp, 0, sizeof(dp)); dp[0] = 1;
    FOR(i,0,m){
        for(int j=2; j<=3 && i+j<=m; ++j){
            string cur_num = s.substr(i,j);
            if(mp.find(cur_num)==mp.end()||!dp[i]){
                continue;
            }
            dp[i+j] |= dp[i];
        }
    }

    int cur_index = m;
    vector<array<int, 3>> ans;
    while(cur_index > 0){
        bool found = 0;
        for(int j=2; j<=3; ++j){
            if(cur_index-j >= 0 && dp[cur_index-j] && mp.find(s.substr(cur_index-j,j))!=mp.end()){
                found = 1;
                ans.push_back(mp[s.substr(cur_index-j, j)]);
                cur_index -= j;
                break;
            }
        }
        if(!found){
            cout << -1 << nl; return;
        }
    }
    cout << sz(ans) << nl;
    reverse(ans.begin(), ans.end());
    trav(x, ans){
        cout << x[0] << " " << x[1] << " " << x[2] << nl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    FOR(i,0,t){
        solve();
    }

    return 0;
}
