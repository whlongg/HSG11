//DTQGSPRING/ContestDP/a2.cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<bool> a(n + 1, false);
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        a[x] = true;
    }
    vector<ll> dp(n + 1, 0);
    dp[1] = 1;
    dp[0] = 0;
    for (int i = 2; i <= n; ++i){
        if (!a[i])
            dp[i] = ((dp[i - 1]%MOD) + (dp[i - 2]%MOD)) % MOD;
        if(dp[i]==0 && dp[i-1]==0){
    		cout << 0;
    		return 0;
    	}
    }
    cout << dp[n] << '\n';
    return 0;
}