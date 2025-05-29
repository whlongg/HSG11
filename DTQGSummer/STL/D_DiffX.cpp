// DTQGSummer/STL/D_DiffX.cpp
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
    int n, x; cin >> n;
    set <int> st;
    for(int i = 1; i <= n; ++i)
        cin >> x, st.insert(x);
    cout << st.size();
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