// DTQGSummer/STL/B_Counting.cpp
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
    string s; cin >> s;
    
    map<char, int> freq;

    for(char x : s)
        freq[x]++;
    
    for(auto [x, cnt] : freq)
        cout << x << ' ' << cnt << '\n';
}

int32_t main(void){
    FASTIO;
    // #ifndef ONLINE_JUDGE
    //     init();
    // #endif
    int q = 1;
    //cin >> q;
    while(q--)
        solve();
}