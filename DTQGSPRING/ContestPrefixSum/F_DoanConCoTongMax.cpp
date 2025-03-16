#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n; cin >> n;
    int a[n];
    for(int i=0; i < n; ++i)
        cin >> a[i];
    int dp[n], max_so_far=a[0];
    dp[0]=a[0];
    for(int i = 1; i < n; ++i){
        dp[i] = max(a[i], dp[i-1]+a[i]);
        max_so_far = max(max_so_far, dp[i]);
    }
    cout << max_so_far;
}