// DTQGSummer/Recursion/C_LietKeHoanVi.cpp
//AC with C++20 (GCC 13-64)
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

vector <bool> check;
vector <int> idx;

void backtrack(int n){
    if((int)idx.size() == n){
        for (int x : idx)   cout << x << "";
        cout << '\n';
        return;
    }

    for(int _ = 1; _ <= n; ++_)
        if(!check[_]){
            check[_]=true;
            idx.push_back(_);
            backtrack(n);
            idx.pop_back();
            check[_]=false;
        }
}

void solve(){
    int n; cin >> n;
    check.assign(n+1, false);
    idx.clear();
    backtrack(n);
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