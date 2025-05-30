// DTQGSummer/STL/H_v2x.cpp
//AC with C++20 (GCC 13-64)
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

void init()
{
    file("testcs.inp", "testcs.out");
}

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> a(n, vector<ll>(m));
    vector<int> rmap(n);
    iota(rmap.begin(), rmap.end(), 0);
    vector<int> cmap(m);
    iota(cmap.begin(), cmap.end(), 0);

    vector<ll> rsum(n, 0);
    vector<ll> csum(m, 0);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> a[i][j];
            rsum[i] += a[i][j];
            csum[j] += a[i][j];
        }
    }

    for (int _ = 1; _ <= q; _++)
    {
        char t;
        cin >> t;
        //cout << "index: " << _ << " " << t << '\n';
        if (t == '1')
        {
            int r1, r2;
            cin >> r1 >> r2;
            swap(rmap[r1 - 1], rmap[r2 - 1]);
        }
        else if (t == '2')
        {
            int r, c;
            ll x;
            cin >> r >> c >> x;
            int pr = rmap[r - 1];
            int pc = cmap[c - 1];
            ll oval = a[pr][pc];
            a[pr][pc] = x;
            rsum[pr] += (x - oval);
            csum[pc] += (x - oval);
        }
        else if (t == 'r')
        {
            int r;
            cin >> r;
            cout << rsum[rmap[r - 1]] << '\n';
        }
        else if (t == 'c')
        {
            int c;
            cin >> c;
            cout << csum[cmap[c - 1]] << '\n';
        }
    }

    for (int i = 0; i < n; ++i)
    {
        int pr = rmap[i];
        for (int j = 0; j < m; ++j)
        {
            int pc = cmap[j];
            cout << a[pr][pc] << (j == m - 1 ? "" : " ");
        }
        cout << '\n';
    }
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