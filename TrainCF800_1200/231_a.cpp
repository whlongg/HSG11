//TrainCF800_1200/231_a.cpp
//https://codeforces.com/problemset/problem/231/A
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

int solve(){
    int a, b, c;
    cin >> a >> b >> c;
    if (a+b+c>=2)
        return 1;
    else
        return 0;
    
}
int32_t main(void){
    FASTIO;
    #ifndef ONLINE_JUDGE
        init();
    #endif
    int q = 1;
    cin >> q;
    int ans=0;
    while(q--)
        ans += solve();
    cout << ans; 
}