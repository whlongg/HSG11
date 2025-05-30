//DTQGSPRING/DoThi/E_SoTan.cpp
//AC with C++23

/*
    author: Nguyen Hoang Long
    oj.vnoi.info/nhl08contact
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);
#define FOR(i, a, b) for(int i = (a); i <= (b); ++i)
#define REP(i,b) for(int i = 1; i <= n; ++i)
#define MAX 100005
#define MOD 1000000007

void init(){
    file("testcs.inp", "testcs.out");
}


vector<int> adj[MAX]; 
int n, m, k; 
int dist[MAX];

void bfs(const vector<int>&exits){
    queue<int> q;
    vector<bool> visited(n+1, false);
    for(int u : exits){
        q.push(u);
        visited[u]=true;
        dist[u]=0;
    }

    while(!q.empty()){
        int u = q.front(); q.pop();

        for(int v : adj[u]){
            if(!visited[v]){
                visited[v]=true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

void solve(){
    cin >> n >> k;
    vector<int> exits;
    int _;
    FOR(i, 1, k)    cin >> _, exits.push_back(_);

    cin >> m;
    FOR(i, 1, m){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    bfs(exits);

    FOR(i, 1, n)    cout << dist[i] << ' ';
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