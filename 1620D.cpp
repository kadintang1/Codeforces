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

const int INF = 1e9;
void solve(){
    int n; cin >> n;
    vector<int> a(n);
    trav(x, a) cin >> x;
    int ans = INF;
    for(int i=0; i<2; ++i){
        for(int j=0; j<3; ++j){
            int rem = 0;
            for(auto& v : a){
                int cur = INF;
                for(int x=0; x<=i; ++x){
                    for(int y=0; y<=j; ++y){
                        if(v-x-2*y>=0&&(v-x-2*y)%3==0){
                            cur = min(cur, (v-x-2*y)/3);
                        }
                    }
                }
                rem = max(rem, cur);
            }
            ans = min(ans, rem+i+j);
        }
    }
    cout << ans << nl;
}

int main() {
    int t; cin >> t;
    while(t--){
        solve();
    }

    return 0;
}
