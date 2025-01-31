#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
vector <vector<int>> adj;
vector <bool> visited;

void dfs(int u){
    visited[u]=true;
    cout << u << ' ';
    for(int v: adj[u])
        if (!visited[v])
            dfs(v);
}

int main(){
    int n, m;
    adj.resize(n+1);
    visited.resize(n+1, false);
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a); //Nếu đồ thị vô hướng.
    }
    for(int i = 1; i <= n; ++i)
        if(!visited[i])
            dfs(i);
}