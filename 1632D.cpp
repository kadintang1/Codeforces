#include <bits/stdc++.h>
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

const int N = 2e5+5;
int stLeft[4*N], stRight[4*N], stVal[4*N], a[N];

void build(int l, int r, int i=1){
    stLeft[i] = l; stRight[i] = r;
    if(l == r){
        stVal[i] = a[l]; return;
    }
    build(l, (l+r)/2, 2*i); build((l+r)/2+1, r, 2*i+1);
    stVal[i] = gcd(stVal[2*i], stVal[2*i+1]);
}

int query(int l, int r, int i=1){
    if(stRight[i] < l || r < stLeft[i]){
        return -1;
    }
    if(l <= stLeft[i] && stRight[i] <= r){
        return stVal[i];
    }
    int q_left = query(l,r,2*i);
    int q_right = query(l,r,2*i+1);
    if(q_left == -1){
        return q_right;
    } else if(q_right == -1){
        return q_left;
    }
    assert(q_left > 0 && q_right > 0);
    return gcd(q_left, q_right);
}

void solve(){
    int n, cur_left = -1; cin >> n;
    vector<int> ret(n);
    FOR(i,0,n){
        cin >> a[i];
    }

    build(0, n-1);
    FOR(i,0,n){
        ret[i] = (i-1 >= 0 ? ret[i-1] : 0);
        int l = cur_left + 1, r = i;
        while(l <= r){
            int m = (l + r + 1)/ 2;
            int q = query(m, i);
            if(q == i - m + 1){
                cur_left = i; ++ret[i]; break;
            } else if(q < i - m + 1){
                l = m + 1;
            } else{
                r = m - 1;
            }
        }
    }

    trav(x, ret){
        cout << x << " ";
    }
    cout << nl;
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
