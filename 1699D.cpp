#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

int fr[5005];
int main(){ 
    ios::sync_with_stdio(0); cin.tie(NULL);
    int t; cin >> t;
    for(int z = 0; z < t; ++z){
        int n; cin >> n;
        vector<int> a(n), c;
        for(int i = 0; i < n; ++i){
            cin >> a[i]; c.push_back(a[i]);
        }

        sort(c.begin(), c.end());
        c.resize(unique(c.begin(), c.end()) - c.begin());

        int ans = 0;
        for(auto& t : c){
            int mc = 0, sc = 0, p = 0, pt = 0;
            vector<pair<int, int>> get_right;
            for(int i = 0; i < n; ++i){
                if(a[i] == t){
                    if(sc > 0){
                        get_right.push_back(make_pair(-max(2 * mc - sc, sc & 1), i - 1));
                        for(int j = p; j <= i; ++j){
                            if(a[j] != t){
                                fr[a[j]]--;
                            }
                        }
                        sc = mc = 0, p = i + 1;
                    }
                    ++fr[t];
                } else{
                    if(fr[t] > 0){
                        get_right.push_back(make_pair(fr[t], i - 1));
                        for(int j = pt; j <= i; ++j){
                            if(a[j] == t){
                                fr[a[j]]--;
                            }
                        }
                        pt = i + 1;
                    }
                    fr[a[i]]++, sc++;
                    mc = max(mc, fr[a[i]]);
                }
            }

            if(fr[t] > 0){
                get_right.push_back(make_pair(fr[t], n - 1));
                for(int i = pt; i < n; ++i){
                    if(a[i] == t){
                        fr[a[i]]--;
                    }
                }
            }

            if(sc > 0){
                get_right.push_back(make_pair(-max(2 * mc - sc, sc & 1), n - 1));
                for(int i = p; i < n; ++i){
                    if(a[i] != t){
                        fr[a[i]]--;
                    }
                }
            }

            int m = get_right.size();
            vector<int> dp(m + 1);
            for(int i = 0, run_sum = 0; i < m; ++i){
                run_sum += get_right[i].first;
                dp[i + 1] = run_sum;
                for(int j = i, mc = 0, sc = 0; ~j; --j){
                    if(get_right[j].first > 0){
                        fr[t] += get_right[j].first;
                        sc += get_right[j].first;
                        mc = max(mc, fr[t]);
                    } else{
                        int rptr = get_right[j].second;
                        int lptr = (j - 1 >= 0 ? get_right[j - 1].second + 1 : 0);
                        for(int k = lptr; k <= rptr; ++k){
                            fr[a[k]]++, ++sc;
                            mc = max(mc, fr[a[k]]);
                        }
                    }
                    dp[i + 1] = max(dp[i + 1], (mc == sc && get_right[j].first > 0 ? fr[t] : -max(2 * mc - sc, sc & 1)) + dp[j]);
                }

                for(int j = i; ~j; --j){
                    if(get_right[j].first > 0){
                        fr[t] -= get_right[j].first;
                    } else{
                        int rptr = get_right[j].second;
                        int lptr = (j - 1 >= 0 ? get_right[j - 1].second + 1 : 0);
                        for(int k = lptr; k <= rptr; ++k){
                            fr[a[k]]--;
                        }
                    }
                }
            }
            ans = max(ans, dp.back());
        }
        cout << ans << '\n';
    }
    return 0;
}
