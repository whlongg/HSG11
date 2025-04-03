//DTQGSPRING/DoThi/B.cpp
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

const int MAXN = 2e5+5;
vector <int> adj[MAXN];
vector dist(MAXN, -1);

int bfs(int s, int n){
    queue <int> q;
    q.push(s);
    dist[s]=0;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : adj[u])
            if(dist[v]==-1)
                dist[v]=dist[u]+1, q.push(v);
    }
    return dist[n];
}

void solve(){
    int n, m, u, v; cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans = bfs(1, n);
    cout << (ans == -1?-1:ans+1);
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