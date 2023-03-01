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
#define rev(v) reverse(all(v))
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

bool test(string X, string Y){
    if(X==Y){
        return 1;
    }
    if(Y.back()=='0'){
        return 0;
    }
    for(int i=0; i<sz(Y); ++i){
        for(int j=0; i+j<=sz(Y); ++j){
            if(Y.substr(i,j)==X){
                int l = i-1, r = i+j;
                while(l>=0&&Y[l]=='1'){
                    --l;
                }
                while(r<sz(Y)&&Y[r]=='1'){
                    ++r;
                }
                if(l<0&&r==sz(Y)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

void solve(){
    ll x = 0, y = 0; 
    cin >> x >> y;
    string X = "", Y = "";
    while(x){
        X = (X + to_string(x&1));
        x >>= 1;
    }
    while(y){
        Y = (Y + to_string(y&1));
        y >>= 1;
    }
    rev(X); rev(Y);
    if(test(X, Y)){
        cout << "YES" << nl; return;
    }

    X += '1';
    rev(X);
    if(test(X, Y)){
        cout << "YES" << nl; return;
    }
    rev(X); X.pop_back();

    while(X.back()=='0'){
        X.pop_back();
    }

    if(test(X, Y)){
        cout << "YES" << nl; return;
    }

    rev(X);
    if(test(X, Y)){
        cout << "YES" << nl; return;
    }
    cout << "NO" << nl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();
    return 0;
}
