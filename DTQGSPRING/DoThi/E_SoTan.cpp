// DTQGSPRING/DoThi/E_SoTan.cpp
//https://yhdtqgspring25.contest.codeforces.com/group/Au4M0A1OWN/contest/590578/problem/F
/*
    author: Nguyen Hoang Long
    oj.vnoi.info/nhl08contact
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out)          \
    freopen((inp), "r", stdin); \
    freopen((out), "w", stdout);
#define FASTIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define REP(i, b) for (int i = 1; i <= n; ++i)
#define MAX 1003
#define MOD 100000007

void init()
{
    file("ANT.INP", "ANT.OUT");
}

int grid[MAX][MAX], dist[MAX][MAX], ways[MAX][MAX];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int n, m;
bool visited[1003][1003];

bool check(int x, int y)
{
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

void bfs()
{
    queue<pair<int, int>> q;
    q.push({1, 1});
    dist[1][1] = 0;
    ways[1][1] = 1;
    visited[1][1] = true;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        for (int d = 0; d < 4; ++d)
        {
            int nx = x + dx[d], ny = y + dy[d];
            if (check(nx, ny) && grid[nx][ny]==1)
            {
                if (!visited[nx][ny])
                {
                    visited[nx][ny] = true;
                    dist[nx][ny] = dist[x][y] + 1;
                    ways[nx][ny] = ways[x][y];
                    q.push({nx, ny});
                }
                else if (dist[nx][ny] == dist[x][y] + 1)
                    ways[nx][ny] = (ways[nx][ny] + ways[x][y]) % MOD;
            }
        }
    }
}

void solve()
{
    cin >> n >> m;
    FOR(i, 1, n)
    {
        string s;
        cin >> s;
        FOR(j, 1, m)
        grid[i][j] = s[j - 1] - '0', dist[i][j] = -1;
    }

    if(grid[1][1]==0 || grid[n][m]==0){
        cout << 0 << '\n' << -1;
        return;
    }

    bfs();
    cout << ways[n][m] % MOD << '\n'
         << dist[n][m];
}

int32_t main(void)
{
    FASTIO;
    init();
    int q = 1;
    // cin >> q;
    while (q--)
        solve();
}