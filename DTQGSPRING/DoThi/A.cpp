//DTQGSPRING/DoThi/A.cpp
//https://yhdtqgspring25.contest.codeforces.com/group/Au4M0A1OWN/contest/590578/problem/A
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);
const int N = 100005;

void init(){
    file("testcs.inp", "testcs.out");
}

vector <int> adj[N];
bool visited[N];

void bfs(int s){
    visited[s]=true;
    queue <int> q;
    q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : adj[u]){
            if(!visited[v]){
                q.push(v);
                visited[v]=true;
            }
        }
    }
}

void solve(){
    int n, m, u, v, ans=0; cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i = 1; i <= n; ++i){
        if(!visited[i]){
            bfs(i);
            ans++;
        }
    }
    cout << ans-1;
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