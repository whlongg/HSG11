// DTQGSummer/Bitwise/A_BitFunc.cpp


/*
    author: Nguyen Hoang Long
    oj.vnoi.info/user/nhl08contact
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
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

void solve(){
    int n; cin >> n;
    int a = __builtin_popcountll(n);
    int l = -1;
    for(int i = 63; i >= 0; --i)
        if((n >> i) & 1){
            l = i;
            break;
        }
    int r = -1;
    for(int i = 0; i <= 63; ++i)
        if((n >> i) & 1){
            r = i;
            break;
        }
    
    cout << a << ' ' << l << ' ' << r;
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