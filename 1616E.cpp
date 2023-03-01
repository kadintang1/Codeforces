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

const int N = 2e5;
int ft[N], used[N];
void init(int n){
    FOR(i,1,n+1){
        ++ft[i];
        int j=i+(i&-i);
        if(j<=n){
            ft[j]+=ft[i];
        }
    }
}

int query(int x){
    int ret = 0;
    for(++x; x>0; x-=x&-x){
        ret+=ft[x];
    }
    return ret;
}

int rangeSum(int l, int r){
    return query(r)-query(l-1);
}


void upd(int x){
    for(++x; x<N; x+=x&-x){
        --ft[x];
    }
}

void solve(){
    int n; cin >> n;
    string s, t, _s; cin >> s >> t;
    _s = s; sort(all(_s));
    if(_s.compare(t) >= 0){
        cout << -1 << nl; return;
    }

    memset(ft, 0, 4*(n+1)); init(n);
    memset(used, 0, 4*(n+1));
    vector<set<int>> st(26);
    FOR(i,0,n){
        st[s[i]-'a'].insert(i);
    }

    ll ans = 2e15, cur = 0, l = 0;
    FOR(i,0,n){
        while(used[l]) ++l;
        if(s[l] < t[i]){
            umin(ans, cur); break;
        }

        int x = 2e9;
        for(int j=0; j<t[i]-'a'; ++j){
            if(!sz(st[j])) continue;
            if(*st[j].begin()<x){
                x = *st[j].begin();
            }
        }
        if(x < 2e9){
            umin(ans, cur+rangeSum(0,x-1));
        }
        // move same character
        if(!sz(st[t[i]-'a'])){
            break;
        }
        int idx = *st[t[i]-'a'].begin();
        cur += rangeSum(0,idx-1);     
        used[idx] = 1; upd(idx);
        st[t[i]-'a'].erase(st[t[i]-'a'].begin());
        if(s[l]==t[i]){
            ++l;
        }
        // dbg(idx);
        // dbg(ans);
        // dbg(cur);
    }
    cout << ans << nl;
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
