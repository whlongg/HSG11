//DTQGSPRING/ContestDP/a5.cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);
const int MOD = 1000000007;
void init(){
    file("input.txt", "output.txt");
}
void solve(){
    int n; cin >> n; 
    int dp[n+1];
    dp[0]=1;
    for(int i = 1; i <= n; ++i)
        dp[i]=0;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= 6; ++j)
            if(i-j >= 0)
                dp[i]=((dp[i]%MOD) + (dp[i-j]%MOD))%MOD;
    }
    cout << dp[n];
}

int32_t main(void){
    FASTIO;
    //init();
    int q = 1;
    //cin >> q;
    while(q--)
        solve();
}