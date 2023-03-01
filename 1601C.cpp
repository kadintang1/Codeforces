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

const int N = 2e6+5;
int ft[N+5], cnt[N+5];
int query(int i){
    int res = 0;
    for(++i; i>0; i-=i&-i){
        res += ft[i];
    }
    return res;
}

int rangeSum(int l, int r){
    return query(r)-query(l-1);
}

void upd(int i, int d){
    for(++i; i<=N; i+=i&-i){
        ft[i]+=d;
    }
}

void solve(){
    // Sort array b. In the sorted array b, pos(bi) denotes the position of bi in the combined array c.
    // Lemma 1: The optimal solution must have, pos(b1) < pos(b2) < .. < pos(bn-1) < pos(bm)
    // Proof: Assume for the sake of contradiction that there exists two indices s.t b1 <= b2 but pos(b1) > pos(b2)
    // Then consider what happens when we swap elements b1 and b2.
    // -> For all elements that exist to the left of pos(b2) and to the right of pos(b1), the # inversions remains the same
    // -> For all inversions created by the elements between b1 and b2, the # inversions changes by 
    // the # elements between pos(b1), pos(b2) with values in the range [b1, b2], + 1 for the swap between b1 & b2.
    // Since swapping leads to a lower inversion count, q.e.d

    // Lemma 2: Suppose we've inserted the element b(m/2) into its leftmost position w/minimal inversions. Then, an optimal answer
    // exists where we insert some bj > b(m/2) in a spot with minimal insertions, too.
    // Proof: Suppose for the sake of contradiction that this leads to a suboptimal solution.
    // Then, this means that exists some other configuration where b(m/2) is to the left of its position
    // w/minimal inversions. Notice that
    // 1) Moving b(m/2) past an element less than it will only increase the inversion count
    // 2) The # elements that b(m/2) moves to the left of that are less than b(m/2) MUST be 
    // greater than the # elements that b(m/2) moves to the right of that are greater than it.
    // As a consequence, if bj moves past these elements, the net gain will always be nonnegative.
    // Because the net gain is nonnegative, a better answer cannot exist. q.e.d

    // Divide and conquer, gg
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m), p(m), c;
    trav(x, a){
        cin >> x; c.push_back(x);
    }
    trav(x, b){
        cin >> x; c.push_back(x);
    }
    sort(all(b));
    sort(all(c));
    c.resize(unique(all(c))-c.begin());
    trav(x, a){
        x = lower_bound(all(c), x) - c.begin();
    }

    trav(x, b){
        x = lower_bound(all(c), x) - c.begin();
    }


    function<void(int, int, int, int)> solve = [&](int l, int r, int pl, int pr){
        int mb = (l+r)/2, occ=0;
        FOR(i,pl,pr+1){
            cnt[i] = occ;
            if(i < n && a[i]>b[mb]){
                ++occ;
            }
        }
        occ=0;
        ROF(i,min(pr,n-1),pl){
            if(i<n && a[i]<b[mb]){
                ++occ;
            }
            cnt[i] += occ;
        }
        p[mb] = pl;
        FOR(i,pl,pr+1){
            if(cnt[p[mb]]>cnt[i]){
                p[mb] = i;
            }
        }

        if(l<mb){
            solve(l, mb-1, pl, p[mb]);
        }
        if(mb<r){
            solve(mb+1, r, p[mb], pr);
        }
    };
    solve(0, m-1, 0, n);
    int j = 0;
    vector<int> ans;
    FOR(i,0,n){
        for(;j<m && p[j]<=i; ++j){
            ans.push_back(b[j]);
        }
        ans.push_back(a[i]);
    }

    for(;j<m; ++j){
        ans.push_back(b[j]);
    }

    // dbg(ans);
    ll res = 0;
    trav(x, ans){
        res += rangeSum(x+1, N);
        // assert(rangeSum(x+1,n) >= 0);
        upd(x, 1);
    }
    trav(x, ans){
        upd(x, -1);
    }
    cout << res << nl;
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
