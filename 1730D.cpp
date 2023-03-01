#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { 
    return os << '(' << p.first << ", " << p.second << ')'; 
}

template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { 
    os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; 
}

int main(){ 
    ios::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    for(int z = 0; z < t; ++z) {
        int n; cin >> n;
        string s1, s2; cin >> s1 >> s2;
        map<pair<int, int>, int> f;
        for(int i = 0; i < n; ++i) {
            int L = min(s1[i], s2[n - i - 1]), R = max(s1[i], s2[n - i - 1]);
            f[{L, R}]++;
        }

        int o = 0;
        for(auto& p : f) {
            o += p.second & 1;
            o += (p.second & 1) && (p.first.first != p.first.second);
        }

        if(o > 1){
            cout << "NO\n";
        } else{
            cout << "YES\n";
        }
    }
    return 0;
}
