#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int INF = 1e9;
const int N = 1e5+5;
#define pii pair<int, int>
#define FOR(i, a, b) for(int i = (a); i <= (b); ++i)
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);
#define vt(v) vector<int>(v)
#define mp map<int, int> mp;

int Rand(int l, int r){
    return l + rand() % (r+l-1);
}

void dfs(int u){
    visited[u]=true;
    for(int v : adj[u])
        if(!visited[v])
            dfs(v);
}

void dijkstra(int s){
    priority_queue <pii, vector<pii>, greater<pii>> pq;
    dist[s]=0;
    pq.push({0,s})
    while(!pq.emty()){
        auto [du, u] = pq.top();
        pq.pop();
        if(du > dist[u])    continue;
        for(auto[v, w] : adj[u])
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
    }
}

void bfs(int start){
    queue <int> q;
    q.push(start);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : adj[u]){
            if(!visited[v]){
                q.push(v);
                visited[v] = true;
            }
        }
    }
}

int32_t main(){
    srand(time(0));

}