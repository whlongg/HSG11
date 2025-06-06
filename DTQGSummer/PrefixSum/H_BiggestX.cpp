// DTQGSummer/PrefixSum/H_BiggestX.cpp


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
const int MAX = 400 + 5;
#define MOD 1000000007

void init()
{
    file("testcs.inp", "testcs.out");
}

int n, a[MAX][MAX], s1[MAX][MAX], s2[MAX][MAX];

void solve()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> a[i][j];

    for (int len = 1; len <= n; ++len)
        for (int i = 0; i + len <= n; ++i)
            for (int j = 0; j + len <= n; ++j)
            {
                s1[i + len][j + len] = s1[i + len - 1][j + len - 1] + a[i + len - 1][j + len - 1];
                s2[i + len][j] = s2[i + len - 1][j + 1] + a[i + len - 1][j];
            }
    int ans = INT_MIN;
    FOR(len, 2, n)
    for (int i = 0; i + len <= n; ++i)
        for (int j = 0; j + len <= n; ++j)
            ans = max(ans, s1[i + len][j + len] - s1[i][j] - (s2[i + len][j] - s2[i][j + len]));
    cout << ans;
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