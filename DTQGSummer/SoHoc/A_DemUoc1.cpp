//DTQGSummer/SoHoc/A_DemUoc1.cpp
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
#define MAX 1000000009
#define MOD 1000000007

void init(){
    file("testcs.inp", "testcs.out");
}

void solve(){
    int n; cin >> n;
    int res = 0; 
    for(int i = 1; i <= sqrt(n); ++i)
        if(n%i==0){
            if(i*i==n)
                res++;
            else
                res +=2;
        }
    cout << res;
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