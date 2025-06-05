// DTQGSummer/SoHoc/E_UCLN.cpp


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

int cnt[MAX];

void solve()
{
    int n;
    cin >> n;
    int a[n];
    for (int &x : a)
    {
        cin >> x;
        cnt[x]++;
    }
    for (int g = MAX - 1; g >= 1; --g)
    {
        int s = 0;
        for (int j = g; j < MAX; j += g)
        {
            s += cnt[j];
        }
        if (s >= 2)
        {
            cout << g;
            return;
        }
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