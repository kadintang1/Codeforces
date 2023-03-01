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

const int N = 1e5, INF = 1e9;
int stLeft[4*N], stRight[4*N], stVal[4*N];
void build(int l, int r, int i=1){
    stLeft[i] = l; stRight[i] = r;
    if(l == r){
        stVal[i] = -INF; return;
    }
    int m = (l + r) >> 1;
    build(l, m, 2*i), build(m+1, r, 2*i+1);
    stVal[i] = min(stVal[2*i], stVal[2*i+1]);
}

void upd(int idx, int val, int i=1){
    if(stRight[i] < idx || idx < stLeft[i]){
        return;
    }
    if(idx <= stLeft[i] && stRight[i] <= idx){
        stVal[i] = val; return;
    }
    upd(idx, val, 2*i), upd(idx, val, 2*i+1);
    stVal[i] = min(stVal[2*i], stVal[2*i+1]);
}

int min_query(int l, int r, int i=1){
    if(stRight[i] < l || r < stLeft[i]){
        return INF;
    }
    if(l <= stLeft[i] && stRight[i] <= r){
        return stVal[i];
    }
    int l_query = min_query(l, r, 2*i), r_query = min_query(l, r, 2*i+1);
    return min(l_query, r_query);
}

int main(){
    ios::sync_with_stdio(0); cin.tie(NULL);
    // hmm, so to see if xor = q is possible
    // ignore all positions where a[i] = q, and greedily check MEX of each subarray
    // -> clearly O(n^2)
    // So, how to reduce to O(n) or O(nlogn)? 
    // OH!!! let a[i] = most recent occurrence of number i
    // Then, as long as min(a[1], a[2], .., a[q-1]) > prev(a[q]), MEX = q is possible!

    int n; cin >> n;
    vector<int> a(n), ok(n+10), p(n+10, -1);
    trav(x, a) cin >> x;

    build(0, n+10);
    for(int i=0; i<n; ++i){
        int x = a[i];
        if(x > 1){
            ok[x] |= min_query(1, x-1) > p[x];
        }
        p[x] = i;
        upd(x, i);
        ok[1] |= (x != 1);
        ok[2] |= (x == 1);
    }

    int tot_mex = 1;
    while(p[tot_mex] >= 0){
        ++tot_mex;
    }
    ok[tot_mex] = 1;

    build(0, n+10);
    fill(all(p), -1);
    reverse(all(a));
    for(int i=0; i<n; ++i){
        int x = a[i];
        if(x > 1){
            ok[x] |= min_query(1, x-1) > p[x];
        }
        p[x] = i;
        upd(x, i);
    }

    for(int i=1; i<=n+5; ++i){
        if(!ok[i]){
            if(min_query(i, i) < 0 && min_query(1, i-1) >= 0){
                continue;
            }
            cout << i << nl; break;
        }
    }

    return 0;
}
