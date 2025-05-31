// DTQGSPRING/DoThi/G_DuongBo_DuongSat.cpp
// https://yhdtqgspring25.contest.codeforces.com/group/Au4M0A1OWN/contest/590578/problem/G


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
#define MAX 200006
#define MOD 1000000007

void init()
{
    file("testcs.inp", "testcs.out");
}

struct DSU
{
    vector<int> p;
    DSU(int n)
    {
        p.resize(n + 1);
        iota(p.begin(), p.end(), 0);
    }

    int get(int v)
    {
        if (v == p[v])
            return v;
        return p[v] = get(p[v]);
    }

    void unite(int a, int b)
    {
        a = get(a);
        b = get(b);
        if (a != b)
            p[b] = a;
    }
};

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    DSU dsu_r(n);
    FOR(i, 0, m - 1)
    {
        int u, v;
        cin >> u >> v;
        dsu_r.unite(u, v);
    }

    DSU dsu_l(n);
    FOR(i, 0, k - 1)
    {
        int u, v;
        cin >> u >> v;
        dsu_l.unite(u, v);
    }

    map<pair<int, int>, int> cnt;
    vector<pair<int, int>> ids(n + 1);

    FOR(i, 1, n)
    {
        int r_id = dsu_r.get(i);
        int l_id = dsu_l.get(i);
        ids[i] = {r_id, l_id};
        cnt[ids[i]]++;
    }

    FOR(i, 1, n)
    cout << cnt[ids[i]] << (i == n ? "" : " ");
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