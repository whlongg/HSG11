//DTQGSPRING/ContestDP/a3.cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);

void init(){
    file("input.txt", "output.txt");
}
void solve(){
    int n; cin >> n;
    int a[n+1], res = 1;
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    vector <int> dp(n+1, 1);
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j < i; ++j)
            if (a[i] > a[j])
                dp[i]=max(dp[i], dp[j]+1);
        res = max(res, dp[i]);
    } 
    //for(int i = 1; i <= n; i++) cout << "dp[" << i << "] = " << dp[i] << "\n";
    cout << res;

}

int32_t main(void){
    FASTIO;
    //init();
    int q = 1;
    //cin >> q;
    while(q--)
        solve();
}