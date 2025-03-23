//TrainCF800_1200/158_a.cpp
//https://codeforces.com/problemset/problem/158/A
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);

void init(){
    file("testcs.inp", "testcs.ans");
}
void solve(){
    int n, k, ans = 0; cin >> n >> k; 
    int a[n+1];
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for(int i = 1; i <= n; ++i) 
        if(a[i] >= a[k] && a[i] > 0)
            ans++;
    cout << ans;
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

