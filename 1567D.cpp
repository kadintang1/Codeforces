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
    int s, n; cin >> s >> n;
    vector<int> nums(n);
    vector<int> p10(10); p10[0] = 1;
    for(int i=1; i<10; ++i){
        p10[i]=p10[i-1]*10;
    }
    for(int i=0; i<10; ++i){
        int q = (s/p10[i])%10;
        // dbg(q);
        // dbg(i);
        if(!q) continue;
        for(int j=0; j<n && q; ++j){
            if(!nums[j]){
                nums[j] += p10[i]; --q;
            }
        }
        // dbg(nums);
        if(q){
            nums[0] += p10[i] * q;
        }
    }
    sort(all(nums));
    int num_zeroes = 0;
    while(!nums[num_zeroes]){
        ++num_zeroes;
    }

    while(num_zeroes > 0){
        sort(all(nums));
        auto i = upper_bound(all(nums), 1) - nums.begin();
        if(num_zeroes <= 9){
            for(int j = 0; j < num_zeroes; ++j){
                nums[j] = nums[i] / 10;
            }
            nums[i] -= nums[i] / 10 * num_zeroes;
            break;
        } else{
            for(int j = 0; j < 9; ++j){
                nums[j] = nums[i] / 10;
            }
            nums[i] /= 10; num_zeroes -= 9;
        }
    }

    trav(x, nums){
        cout << x << " ";
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
