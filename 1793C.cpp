#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << ": " << x << '\n'
#define ll long long
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }

void test_case() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int cmin = 1, cmax = n, i = 0, j = n - 1;
    while(i <= j) {
        if(min(a[i], a[j]) != cmin && max(a[i], a[j]) != cmax) {
            break;
        }
        if(a[i] == cmin) {
            ++cmin, ++i;
        } else if(a[j] == cmin) {
            ++cmin, --j;
        } else if(a[i] == cmax) {
            --cmax, ++i;
        } else if(a[j] == cmax) {
            --cmax, --j;
        }
    }

    if(i > j) {
        cout << -1 << '\n';
    } else{
        cout << i + 1 << " " << j + 1 << '\n';
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int t; cin >> t;
    for(int i = 0; i < t; ++i) {
        test_case();
    }

    return 0;
}
