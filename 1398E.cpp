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


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    // Let k be the # lightning spells
    // Then, problem is equivalent to choosing the k strongest spells to 2x.
    // However, note that if all k strongest spells are lightning spells
    // We discard one the weakest lightning spell -> let the strongest thunder spell be 2x.

    ll cur_sum = 0, dynamic_sum = 0;
    set<int> one, two, tot;
    auto it = tot.end();
    FOR(i,0,n){
        int t, d; cin >> t >> d;
        if(t){
            // lightning spell -> 2x
            if(d < 0){
                two.erase(-d);
                assert(it != tot.end());
                if(-d > *it){
                    dynamic_sum += d;
                } else{
                    dynamic_sum -= *it;
                    it = next(it);
                }
                tot.erase(-d);
            } else{
                two.insert(d);
                tot.insert(d);
                if(it != tot.end() && d > *it){
                    dynamic_sum += d;
                } else{
                    assert(it != tot.begin());
                    it = prev(it);
                    dynamic_sum += *it;
                }
            }
        } else{
            // thunder spell -> regular
            if(d < 0){
                one.erase(-d);
                if(it != tot.end() && -d >= *it){
                    assert(it != tot.begin());
                    it = prev(it);
                    dynamic_sum += *it + d;
                }
                tot.erase(-d);
            } else{
                one.insert(d);
                tot.insert(d);
                if(it != tot.end() && d > *it){
                    dynamic_sum += d - *it;
                    it = next(it);
                }
            }
        }
        cur_sum += d;
        // dbg(one);
        // dbg(two);
        // dbg(tot);
        // dbg(cur_sum);
        // dbg(dynamic_sum);
        // if(it != tot.end()){
            // dbg(*it);
        // }
        if(!sz(one)){
            cout << cur_sum + dynamic_sum - (sz(two)?*two.begin():0) << nl;
        }
        else if(sz(two)){
            if(*two.begin()>*one.rbegin()){
                cout << cur_sum + dynamic_sum - (*two.begin()-*one.rbegin()) << nl;
            } else{
                cout << cur_sum + dynamic_sum << nl;
            }
        } else{
            cout << cur_sum << nl;
        }
    }
    return 0;
}
