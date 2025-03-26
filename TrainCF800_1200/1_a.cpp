//TrainCF800_1200/1_a.cpp
//https://codeforces.com/problemset/problem/1/A
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);
void init(){
    file("testcs.inp", "testcs.out");
}

void solve(){
    long long n,m,a;
    cin >> n >> m >> a;
    cout << ((n+a-1)/a) * ((m+a-1)/a);
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