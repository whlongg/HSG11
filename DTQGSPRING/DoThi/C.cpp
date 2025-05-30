//DTQGSPRING/DoThi/C.cpp
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

const int MAX = 2e5 + 5;
vector <int> adj[MAX];
int subtree[MAX];

int dfs(int u){
    subtree[u]=1;
    for(int v : adj[u])
        subtree[u] += dfs(v);
    return subtree[u];
}

void solve(){
    int n; cin >> n;
    for(int i = 2; i <= n; ++i){
        int p; cin >> p;
        adj[p].push_back(i);
    }
    dfs(1);
    for(int i = 1; i <= n; ++i)
        cout << subtree[i] -1 << ' ';
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