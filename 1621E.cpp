#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define nl "\n"
#define sz(v) (int)((v).size())
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define bitCount(i) __builtin_popcount(i)
#define FOR(i, a, b) for(int i = a; i < b; ++i)
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
void solve(){
    int n, m; cin >> n >> m;
    // n = # of teachers
    // m = # student groups
    vector<ll> t(n);
    vector<array<ll, 3>> group_sum(m);
    trav(x,t) cin >> x;
    sort(rall(t));
    while(sz(t)>m) t.pop_back();
    sort(all(t));

    vector<vector<pi>> s(m);
    int sum_sz = 0, cur_id = 0;
    FOR(i,0,m){
        int num_students; cin >> num_students;
        group_sum[i] = {0, num_students, i};
        sum_sz += num_students;
        s[i].reserve(num_students);
        FOR(j,0,num_students){
            int v; cin >> v;
            s[i].pb(make_pair(v, cur_id));
            group_sum[i][0] += v;
            ++cur_id;
        }
        sort(all(s[i]));
    }

    // sort group sum by average
    sort(all(group_sum), [&](array<ll, 3> g1, array<ll, 3> g2){
        return g1[0] * g2[1] < g1[1] * g2[0];
    });

    vector<bool> chk_left(m), chk_right(m);
    FOR(i,0,m){
        chk_left[i] = (i-1 >= 0 ? chk_left[i-1] : 1) && (group_sum[i][0] <= t[i] * group_sum[i][1]);
    }

    ROF(i,m-1,0){
        chk_right[i] = (i+1 < m ? chk_right[i+1] : 1) && (group_sum[i][0] <= t[i] * group_sum[i][1]);
    }

    const int INF = 1e9;
    vector<int> dp_right(m), dp_left(m);
    ROF(i,m-2,0){
        if(group_sum[i][0] <= t[i+1] * group_sum[i][1]){
            dp_right[i] = (i+1 < m ? dp_right[i+1] : 0) + 1;
        }
    }

    FOR(i,1,m){
        if(group_sum[i][0] <= t[i-1] * group_sum[i][1]){
            dp_left[i] = (i-1 >= 0 ? dp_left[i-1] : 0) + 1;
        }
    }
    dp_right[m-1] = dp_left[0] = INF;

    vector<int> ans(sum_sz);
    FOR(i,0,m){
        // ith student group, sorted by age average
        FOR(j,0,sz(s[group_sum[i][2]])){
            ll new_sum = group_sum[i][0]-s[group_sum[i][2]][j].ff;
            ll new_ppl = group_sum[i][1]-1;

            //new_sum/new_ppl < old_sum/old_ppl ? 
            if(new_sum * group_sum[i][1] < group_sum[i][0] * new_ppl){
                // new average is smaller
                int l = 0, r = i;
                while(l < r){
                    int m = (l+r)/2;
                    if(group_sum[m][0] * new_ppl > new_sum * group_sum[m][1]){
                        r = m;
                    } else{
                        l = m + 1;
                    }
                }
                /// pos l has target position
                bool chk1 = (i - l <= dp_right[l]);
                bool chk2 = (l - 1 >= 0 ? chk_left[l - 1] : 1);
                bool chk3 = (i + 1 < m ? chk_right[i + 1] : 1);
                bool chk4 = (new_sum <= t[l] * new_ppl);
                // if(id == 16){
                //     dbg(chk1);
                //     dbg(chk2);
                //     dbg(chk3);
                //     dbg(chk4);
                // }
                if(chk1 && chk2 && chk3 && chk4){
                    // possible
                    ans[s[group_sum[i][2]][j].ss] = 1;
                }
            } else{
                // new average is greater than or equal to
                int l = i, r = m - 1;
                while(l < r){
                    int m = (l+r+1)/2;
                    if(group_sum[m][0] * new_ppl >= new_sum * group_sum[m][1]){
                        r = m - 1;
                    } else{
                        l = m;
                    }
                }
                // pos l has target position
                bool chk1 = (l - i <= dp_left[l]);
                bool chk2 = (i - 1 >= 0 ? chk_left[i - 1] : 1);
                bool chk3 = (l + 1 < m ? chk_right[l + 1] : 1);
                bool chk4 = (new_sum <= t[l] * new_ppl);
                if(chk1 && chk2 && chk3 && chk4){
                    //possible
                    ans[s[group_sum[i][2]][j].ss] = 1;
                }
            }
        }
    }

    trav(x, ans){
        cout << x;
    }
    cout << nl;
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
