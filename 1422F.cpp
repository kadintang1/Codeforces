#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <tgmath.h>
#include <cassert>
#include <time.h>
#include <random>
#include <array>
#include <numeric>
#include <regex>
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
#define fi first
#define se second
#define p_b push_back
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

ll gcd(ll a, ll b){
    if(a == 0) return b;
    return gcd(b%a, a);
}

struct node{
    ll _time, ans;
    node *l, *r;
    node(): l(r=nullptr), _time(0), ans(1){}
};

const int N = 1e6+200, M = 1e6, mod = 1e9+7;
int a[N], last[N], Local_time;
vector <int> step[N];
node *root[N];
vector <pair<int, int>> p[N];

void build(node *v, int tl, int tr){
    if(tl != tr){
        v -> l = new node();
        v -> r = new node();
        int tm = (tl + tr) >> 1;
        build(v -> l, tl, tm);
        build(v -> r, tm + 1, tr);
    }
}

void modify(node *v, int tl, int tr, int pos, pair<int, int> fraction){
    if(tl == tr){
        v -> ans *= fraction.fi;
        v -> ans /= fraction.se;
    }else{
        int tm = (tl + tr) >> 1;
        if(pos <= tm){
            if((v -> l) -> _time != Local_time){
                node *old = v -> l;
                v -> l = new node();
                (v -> l) -> ans = old -> ans;
                (v -> l) -> l = old -> l;
                (v -> l) -> r = old -> r;
                (v -> l) -> _time = Local_time;
            }
            modify(v -> l, tl, tm, pos, fraction);
        }else{
            if((v -> r) -> _time != Local_time){
                node *old = v -> r;
                v -> r = new node();
                (v -> r) -> ans = old -> ans;
                (v -> r) -> l = old -> l;
                (v -> r) -> r = old -> r;
                (v -> r) -> _time = Local_time;
            }
            modify(v -> r, tm + 1, tr, pos, fraction);
        }
        v -> ans = ((v -> l) -> ans) * ((v -> r) -> ans)%mod;
    }
}

ll get(node *v,  int tl, int tr, int l, int r){
    if(l > r)return 1;
    if(tl == l && tr == r)return v -> ans;
    int tm = (tl + tr) >> 1;
    return get(v -> l, tl, tm, l, min(r, tm)) * get(v -> r, tm + 1, tr, max(l, tm + 1), r)%mod;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    FOR(i,1,n+1){
        cin >> a[i];
    }

    for(int i = 2; i <= M; i++)if(!last[i]){
        last[i] = i;
        if(ll(i) * ll(i) <= M){
            for(int j = i * i; j <= M; j += i)last[j] = i;
        }
    }

    for(int i = 2; i <= M; i++){
        ll t = 1;
        while(t <= M){
            step[i].push_back(t);
            t *= (ll)i;
        }
    }

    root[0] = new node();

    build(root[0], 1, n);

    for(int i = 1; i <= n; i++){
        Local_time++;
        root[i] = new node();
        root[i] -> ans = root[i - 1] -> ans;
        root[i] -> l = root[i - 1] -> l;
        root[i] -> r = root[i - 1] -> r;
        root[i] -> _time = Local_time;
        int x = a[i];
        while(x != 1){
            int divider = last[x], st = 0;
            while(x % divider == 0){
                st++;
                x /= divider;
            }
            int _last = 0;
            while(!p[divider].empty() && p[divider].back().fi <= st){
                modify(root[i], 1, n, p[divider].back().se, {1, step[divider][p[divider].back().fi - _last]});
                _last = p[divider].back().fi;
                p[divider].pop_back();
            }
            modify(root[i], 1, n, i, {step[divider][st], 1});
            if(sz(p[divider])){
                modify(root[i], 1, n, p[divider].back().se, {1, step[divider][p[divider].back().fi - _last]});
                _last = st;
                modify(root[i], 1, n, p[divider].back().se, {step[divider][p[divider].back().fi - _last], 1});
            }
            p[divider].p_b({st, i});
        }
    }

    int q; cin >> q;
    ll prev_ans = 0;
    FOR(i,0,q){
        int x, y, l, r; cin >> x >> y;
        l = (x + prev_ans)%n + 1;
        r = (y + prev_ans)%n + 1;
        if(l > r) swap(l, r);
        prev_ans = get(root[r], 1, n, l, r);
        cout << prev_ans << nl;
    }

    return 0;
}
