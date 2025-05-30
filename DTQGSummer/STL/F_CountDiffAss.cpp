// DTQGSummer/STL/F_CountDiffAss.cpp
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
    int n, m; cin >> n >> m;
    set<vector<int>> uset;
    for(int i = 1; i <= n; ++i){
        vector<int> vt;
        
        for(int j = 0; j < m; ++j){
            int val; cin >> val;
            vt.push_back(val);
        }
        //xoa cac phan tu trung lap trong vector
        sort(vt.begin(), vt.end());
        vt.erase(unique(vt.begin(), vt.end()), vt.end());
        //end
        uset.insert(vt);
    }
    cout << uset.size();
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