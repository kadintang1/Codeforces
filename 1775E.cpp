#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define nl "\n"
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define FORd(i, b, a) for(int i = b; i >= a; --i)
#define EACH(x, a) for (auto& x : a)
#define arr array
#define pi pair<int, int>
#define vpi vector<pair<int, int>>
#define vi vector<int>
#define vl vector<ll>
#define pb push_back
#define ff first
#define ss second

ll inv(ll a, ll b){
    assert(a != 0); return 1<a ? b - inv(b%a,a)*b/a : 1LL;
}

#define dbg(x) cerr << #x << ": " << x << nl
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

void test_case(){
    int n; cin >> n;
    vector<int64_t> v, a;
    for(int i=0, x; i<n; ++i){
        cin >> x;
        if(x){
            v.push_back(x);
        }
    }
    for(int64_t i=0, s=0; i<sz(v); ++i){
        s+=v[i];
        if(i==sz(v)-1||(v[i]*v[i+1]<0)){
            a.push_back(abs(s)); s=0;
        }
    }
    if(!sz(a)){
        cout << 0 << '\n'; return;
    }
    int m=sz(a);
    set<pair<int64_t, int64_t>> st;
    for(int i=0; i<m; ++i) {
        st.insert({a[i], i});
    }

    vector<int> gl(m, -1), gr(m, -1);
    for(int i=0; i<m; ++i){
        if(i){
            gl[i]=i-1;
        }
        if(i<m-1){
            gr[i]=i+1;
        }
    }
    int64_t ans=0;
    while(sz(st) > 0){
        int64_t cmin = st.begin() -> first;
        vector<array<int64_t, 2>> tr;
        while(st.size() > 0 && cmin == st.begin() -> first){
            tr.push_back({st.begin() -> first, st.begin() -> second}); st.erase(st.begin());
        }

        for(array<int64_t, 2>& e : tr){
            int li = gl[e[1]], ri = gr[e[1]];
            if(li != -1){
                gr[li] = ri;
            }
            if(ri != -1){
                gl[ri] = li;
            }
            if(li != -1 && a[li] > cmin && ri != -1 && a[ri] > cmin && (ri - li + 1)&1){
                //merge
                st.erase({a[li], li});
                st.erase({a[ri], ri});
                st.insert({a[li]+a[ri]-cmin, li});
                gr[li] = gr[ri];
                if(gr[ri] != -1){
                    gl[gr[ri]] = gl[ri];
                }
                a[li] += a[ri] - cmin;
            }
        }
        ans = cmin;
    }
    cout << ans << '\n';
}

int main() {
    int t; cin >> t;
    while(t--){
        test_case();
    }
    return 0;
}
