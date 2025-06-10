// DTQGSummer/DP2/A4_XepBo.cpp


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
#define MOD 20020303

void init(){
    file("testcs.inp", "testcs.out");
}

int dp[MAX];
//con thu i la C -> i-1 con truoc co the duoc sap xep theo bat ki cach nao do (hop le) 
//-> so cach la dp[i-1]
//con thu i la D -> xep sau k con bo cai so voi con bo duc gan nhat 
// noi cach khac tu i-1 -> i-1-k deu phai la bo cai (C) XCCCCC.....CD
//do truong hop 1, truoc do co the xep theo cach bat ki hop le X
//-> so cach hop le la dp[i-k-1]
//-> dp[i] = dp[i-1] + dp[i-k-1]
//base dp[0]=1 (co 1 cach xep hang rong)

//xet truong hop i tu 1 den k (so cach xep k bo)
//xep tat ca deu la cai -> 1 cach
//hoac xep 1 con bo duc o bat ki vi tri nao tu 1 den i (co i cach)
//-> tong so cach nay la (allC)+i(xepD) = i + 1
//dp[i] = i + 1 cho 1 ≤ i ≤ k


void solve(){
    int n,k; cin >> n >> k;
    dp[0] = 1;
    for(int i = 1; i <= n; ++i){
        if(i <= k)  dp[i] = i + 1;
        else dp[i] = (dp[i-1] + dp[i-1-k]) % MOD;
    }
    cout << dp[n];
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

