// DTQGSummer/PrefixSum/F_DoanConCoTongLonNhat.cpp


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
const int MAX = 1e6 + 5;
#define MOD 1000000007

void init()
{
    file("testcs.inp", "testcs.out");
}

ll prefix[MAX];

void solve()
{
    int n;
    cin >> n;
    int a[n + 1];
    prefix[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        prefix[i] = prefix[i - 1] + a[i];
    }

    ll maxs = -1e18;
    ll minPrefix = 0;
    for (int i = 1; i <= n; ++i)
    {
        maxs = max(maxs, prefix[i] - minPrefix);
        minPrefix = min(minPrefix, prefix[i]);
    }
    cout << maxs;
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