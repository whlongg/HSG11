//DTQGSPRING/DoThi/D_DemPhong.cpp
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

int n, m;
const int MAX = 1005;
vector<string> grid;
bool visited[MAX][MAX];

int dx[]={-1, 1, 0 , 0};
int dy[]={ 0, 0, -1, 1};

void dfs(int x, int y){
    visited[x][y]=true;
    for(int d = 0; d < 4; ++d){
        int nx = x + dx[d], ny = y + dy[d];
        if(nx >= 0 && ny >= 0 && nx < n && ny < m && !visited[nx][ny] && grid[nx][ny] == '.')
            dfs(nx, ny);
    }
}

void solve(){
    cin >> n >> m;
    grid.resize(n);
    for(int i = 0; i < n; ++i)  cin >> grid[i];

    int cp = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            if(!visited[i][j] && grid[i][j] == '.')
                dfs(i, j), cp++;
    
    cout << cp;
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