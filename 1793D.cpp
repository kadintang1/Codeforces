    #include <bits/stdc++.h>
    using namespace std;
        
    #define dbg(x) cerr << #x << ": " << x << '\n'
    #define ll long long
    template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
    template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }
        
    void test_case() {
        int n; cin >> n;
        vector<int> p(n), q(n);
        vector<int> gp(n + 1), gq(n + 1);
        for(int i = 0; i < n; ++i) {
            cin >> p[i]; gp[p[i]] = i;
        }
        for(int i = 0; i < n; ++i) {
            cin >> q[i]; gq[q[i]] = i;
        }
        long long ans = 1;
        int lp = -1, rp = -1, lq = -1, rq = -1, mxp = 1, mxq = 1;
        vector<bool> visp(n + 2), visq(n + 2);
        for(int x = 0; x < n; ++x) {
            int co = -1;
            if(!x) {
                for(int i = 0; i < n; ++i) {
                    if(min(p[i], q[i]) == 1) {
                        co = i; continue;
                    }
                    ans += i - co;
                }
                lp = rp = gp[1], lq = rq = gq[1]; ++mxp, ++mxq;
            } else{
                int nlp = min(lp, gp[x]), nrp = max(rp, gp[x]);
                for(int i = nlp; i < lp; ++i) {
                    visp[p[i]] = 1;
                }
                for(int i = rp + 1; i <= nrp; ++i) {
                    visp[p[i]] = 1;
                }
                while(visp[mxp]){
                    ++mxp;
                }
                int nlq = min(lq, gq[x]), nrq = max(rq, gq[x]);
                for(int i = nlq; i < lq; ++i) {
                    visq[q[i]] = 1;
                }
                for(int i = rq + 1; i <= nrq; ++i) {
                    visq[q[i]] = 1;
                }
                while(visq[mxq]) {
                    ++mxq;
                }
                if(mxp == mxq) {
                    int L = min(nlp, nlq), R = max(nrp, nrq);
                    if(!(gp[x + 1] >= L && gp[x + 1] <= R) && !(gq[x + 1] >= L && gq[x + 1] <= R)) {
                        long long opL = L - max(gp[x + 1] < L ? gp[x + 1] : -1, gq[x + 1] < L ? gq[x + 1] : -1);
                        long long opR = min(gp[x + 1] > R ? gp[x + 1] : n, gq[x + 1] > R ? gq[x + 1] : n) - R;
                        ans += opR * opL;
                    }
                }
                lp = nlp, rp = nrp, lq = nlq, rq = nrq;
            }
        }
     
        cout << ans << '\n';
    }
        
    int main(){
        ios::sync_with_stdio(0); cin.tie(0);
        
        // int t; cin >> t;
        // for(int i = 0; i < t; ++i) {
            test_case();
        // }
        
        return 0;
    }
