// DTQGSummer/SoHoc/I_NghichDaoModulo.cpp


/*
    author: Nguyen Hoang Long
    oj.vnoi.info/user/nhl08contact
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);
#define FOR(i, a, b) for(int i = (a); i <= (b); ++i)
#define REP(i,b) for(int i = 1; i <= n; ++i)
const int MAX = 1e6 + 5;
#define MOD 1000000007

void init(){
    file("testcs.inp", "testcs.out");
}

int egcd(int a, int b, int &x, int &y){
    if(b ==0){
        x = 1, y = 0;
        return a;
    }
    int x1, y1;
    int d = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a/b) * y1;
    return d;
}

int ModInv(int a, int m){
    int x, y; 
    int g = egcd(a, m, x, y);
    if( g != 1) return -1;
    return (x % m + m) % m;
}

void solve(){
    int n, m;
    cin >> n >> m;
    cout << ModInv(n, m);
}

int32_t main(void){
    FASTIO;
    #ifndef ONLINE_JUDGE
        init();
    #endif
    int q = 1;
    //cin >> q;
    while(q--)
        solve();
}