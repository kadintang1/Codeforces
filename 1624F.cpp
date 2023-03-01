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
    int n; cin >> n;
    // cout << "+ 1" << nl;
    // x = 4, n = 10
    // 5, 13, 19, 21, 30
    // WRONG

    // x = 6, n = 10
    // 7, 15, 21, 29, 30

    // x = 9, n = 10
    // 10, 18, 22, 30, 39
    // 6 -> 14 (10)
    // -4 (mod 10) = 10 - 4 (mod 10) = 6 (mod 10)

    // x = 2, n = 3
    // 3, 5, 6
    // good

    // x = 4, n = 7
    // 5, 9, 14, 20
    // good

    // x = 1, n = 3
    // 2, 4, 6
    // good

    // x = 10, n = 32
    // 11, 43, 59, 67, 95, 97, 128

    // x = 7, n = 8
    // 8, 16, 20, 22, 23
    // good

    // x = 2, n = 5
    // 3, 7, 10, 14

    // x = 1, n = 4
    // 3, 4
    cout.flush();
    int s = 0, prev = 0, p2 = 1, sign = 1;
    while(p2*2<n){
        p2 <<= 1;
    }
    while(p2){
        if(sign){
            cout << "+ " << p2 << nl;
            s += p2;
        } else{
            cout << "+ " << n-p2 << nl;
            s += n-p2;
        }
        cout.flush();
        int k; cin >> k;
        // dbg(prev);
        // dbg(k);
        // cout << nl;
        if(k == prev){
            sign = 1;
        } else{
            sign = 0;
        }
        prev = k;
        p2 >>= 1;
    }
    if(sign == 1){
        ++prev;
    }
    cout << "! " << prev * n - sign << nl;
    cout.flush();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // int t; cin >> t;
    // FOR(i,0,t){
        solve();
    // }

    return 0;
}
