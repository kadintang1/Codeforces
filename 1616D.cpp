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
#define rev(v) reverse(all(v))
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
    int n; cin >> n;
    vector<int> a(n), dp(n+1, 1);
    trav(x, a) cin >> x;
    int x; cin >> x;
    // need 2 conditions to be true
    // every 2 adjacent elements are fine
    // every 3 elements are fine
    set<int> st;
    dp[0] = 0;
    for(int i=0; i<n; ++i){
        dp[i+1] = max(dp[i+1], dp[i]);
        if(i-2 >= 0 && a[i-2]+a[i-1]+a[i] < 3 * x) st.insert(i-1);
        if(i-1 >= 0 && a[i-1]+a[i] < 2 * x) st.insert(i);
        auto it = st.lower_bound(i+1);
        if(it != st.begin()){
            it = prev(it);
            //i+1-(it+1)+1==i-it+1
            dp[i+1] = max(dp[i+1], (*it >= 1? dp[*it-1] : 0) + (i-*it+1));
        } else{
            dp[i+1] = i+1;
        }
    }

    cout << max((n+1)/2, dp.back()) << nl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t--){
        solve();
    }

    return 0;
}
