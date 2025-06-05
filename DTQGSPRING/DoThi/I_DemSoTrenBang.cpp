// DTQGSPRING/DoThi/I_DemSoTrenBang.cpp
/*
    author: Nguyen Hoang Long
    oj.vnoi.info/user/nhl08contact
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
#define MAXN 2003
#define MOD 1000000007
#define MAXQ 200005
void init()
{
    file("testcs.inp", "testcs.out");
}

struct Query
{
    int r1, c1, r2, c2;
    int idx;
};

ll ans[MAXQ];
vector<Query> qs[MAXN];
ll ansArr[MAXQ];
int n, m;
bool visited[MAXN][MAXN];
int id[MAXN][MAXN];
char grid[MAXN][MAXN];
ll bit[MAXN][MAXN];

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void upd(int r, int c, int d)
{
    for (int i = r; i <= n; i += i & -i)
        for (int j = c; j <= m; j += j & -j)
            bit[i][j] += d;
}

ll get(int r, int c)
{
    if (r <= 0 || c <= 0)
        return 0;
    ll s = 0;
    for (int i = r; i > 0; i -= i & -i)
        for (int j = c; j > 0; j -= j & -j)
            s += bit[i][j];
    return s;
}

void dfs(int r, int c, int cid)
{
    if (r < 1 || r > n || c < 1 || c > m || visited[r][c] || grid[r][c] == '0')
        return;
    visited[r][c] = true;
    id[r][c] = cid;

    FOR(i, 0, 3)
    dfs(r + dr[i], c + dc[i], cid);
}

ll query(int r1, int c1, int r2, int c2)
{
    return get(r2, c2) - get(r1 - 1, c2) - get(r2, c1 - 1) + get(r1 - 1, c1 - 1);
}

void solve()
{
    int q;
    cin >> n >> m >> q;
    FOR(i, 1, n)
    FOR(j, 1, m)
    cin >> grid[i][j];

    int cid_c = 0;

    FOR(i, 1, n)
    FOR(j, 1, m)
    if (grid[i][j] == '1' && !visited[i][j])
    {
        cid_c++;
        dfs(i, j, cid_c);
    }

    FOR(i, 0, q - 1)
    {
        int r1, r2, c1, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        qs[r2].push_back({r1, c1, r2, c2, i});
    }
    map<int, pair<int, int>> last_pos;

    FOR(r, 1, n)
    {
        FOR(c, 1, m)
        {
            if (grid[r][c] == '1')
            {
                int cur_id = id[r][c];
                if (last_pos.count(cur_id))
                {
                    pair<int, int> old = last_pos[cur_id];
                    upd(old.first, old.second, -1);
                }
                upd(r, c, 1);
                last_pos[cur_id] = {r, c};
            }
        }
        for (const auto &curq : qs[r])
        {
            ans[curq.idx] = query(curq.r1, curq.c1, curq.r2, curq.c2);
        }
    }
    for (int i = 0; i < q; ++i)
        cout << ans[i] << '\n';
}

int32_t main(void)
{
    FASTIO;
#ifndef ONLINE_JUDGE
    init();
#endif
    int q = 1;
    // cin >> q;
    while (q--)
        solve();
}