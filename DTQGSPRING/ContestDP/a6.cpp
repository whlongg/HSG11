//DTQGSPRING/ContestDP/a6.cpp
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
    int a[n+1];
    for(int i = 1; i <= n; ++i)
        cin >> a[i];
    for(int i = n; i >= 1; --i)
        cout << a[i] << '\n';
}

int32_t main(void){
    FASTIO;
    init();
    int q = 1;
    //cin >> q;
    while(q--)
        solve();
}