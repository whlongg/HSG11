#include <bits/stdc++.h>
using namespace std;
//commit main.
/* AUTO-SYNC STATUS START */
/* ℹ️ Committing to branch 'main'... */
/* ⏱️ Thời gian: 23:37:46 19/03/2025 */
/* AUTO-SYNC STATUS END */
const int MAXN = 5005;
const int MAXM = 1000005;
const int MAXQ = 100005;

struct Edge {
    int to, next;
};

int n, m, q;
Edge edges[MAXM * 2];
int head[MAXN], edgeCount = 0;
vector<int> sameColorEdges[MAXN];
bool reachable[MAXN][MAXN];
char colorStr[MAXN];
int color[MAXN];

int parent[MAXN];
int visited[MAXN];
bool isBipartite;

queue<pair<int, int>> q;
vector<pair<int, int>> sameColorPairs;

void addEdge(int u, int v) {
    edges[++edgeCount] = {v, head[u]};
    head[u] = edgeCount;
}

int findSet(int v) {
    return v == parent[v] ? v : parent[v] = findSet(parent[v]);
}

void dfs(int node, int currentColor) {
    visited[node] = currentColor;
    
    for (int nextNode : sameColorEdges[node]) {
        if (visited[nextNode] == -1) {
            addEdge(node, nextNode);
            addEdge(nextNode, node);
            dfs(nextNode, currentColor ^ 1);
        } else if (visited[node] == visited[nextNode]) {
            isBipartite = false;
        }
        
        int a = min(node, nextNode);
        int b = max(node, nextNode);
        reachable[a][b] = true;
        q.push({a, b});
    }
}

void bfs() {
    for (auto pair : sameColorPairs) {
        int a = pair.first, b = pair.second;
        if (a > b) swap(a, b);
        reachable[a][b] = true;
        q.push({a, b});
    }
    
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        
        for (int i = head[x]; i; i = edges[i].next) {
            for (int j = head[y]; j; j = edges[j].next) {
                int a = edges[i].to, b = edges[j].to;
                if (color[a] != color[b]) continue;
                
                if (a > b) swap(a, b);
                if (!reachable[a][b]) {
                    reachable[a][b] = true;
                    q.push({a, b});
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m >> q;
    cin >> (colorStr + 1);
    
    for (int i = 1; i <= n; i++) {
        color[i] = colorStr[i] - '0';
        parent[i] = i;
    }
    
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        
        if (color[a] != color[b]) {
            if (findSet(a) != findSet(b)) {
                addEdge(a, b);
                addEdge(b, a);
                parent[findSet(a)] = findSet(b);
            }
        } else {
            sameColorEdges[a].push_back(b);
            sameColorEdges[b].push_back(a);
        }
        
        if (a > b) swap(a, b);
        if (color[a] == color[b]) 
            sameColorPairs.push_back({a, b});
    }
    for (int i = 1; i <= n; i++)
        sameColorPairs.push_back({i, i});
    memset(visited, -1, sizeof(visited));
    for (int i = 1; i <= n; i++) {
        if (visited[i] != -1) continue;
        isBipartite = true;
        dfs(i, 0);   
        if (!isBipartite) {
            addEdge(i, i);
        }
    }
    bfs();
    while (q--) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);   
        cout << (reachable[a][b] ? "YES" : "NO") << "\n";
    }
    return 0;
}
