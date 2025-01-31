#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

void dfs(int u){
    visited[u]=true;
    cout << "Da tham dinh: " << u << '\n';
    for(int i : adj[u])
        if(!visited[i])
            dfs(i);
}

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for(int i = 1; i <= n; ++i)
        if(!visited[i])
            dfs(i);
}