#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    for(int i=0; i<n; ++i){
        cin >> a[i];
    }

    int l = 1, r = n;
    while(l < r){
        int m = (l + r + 1) >> 1, s = 0;
        for(int i=0; i<n; ++i){
            b[i] = a[i] >= m ? 1 : -1;
        }

        bool ans_exists = 0;
        map<int, int> mp; mp[0] = -1;
        for(int i=0; i<n; ++i){
            s += b[i];
            if(s > 0 && i + 1 >= k){
                ans_exists = 1; break;
            }
            auto it = mp.lower_bound(s);
            if(mp.find(s) == mp.end()){
                mp[s] = i;
            }
            if(it == mp.begin()){
                continue;
            }
            it = prev(it);
            if(s - it->first > 0 && i - it->second >= k){
                ans_exists = 1; break;
            }
        }

        if(ans_exists){
            l = m;
        } else{
            r = m - 1;
        }
    }
    cout << l << endl;
    return 0;
}
