// DTQGSummer/DP2/A1_NuocMua.cpp


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
    file("rainwater.inp", "rainwater.out");
}

int max_left[MAX], max_right[MAX], a[MAX];

void solve()
{
    int n;
    cin >> n;
    for (int &x : a)
        cin >> x;
    max_left[0] = a[0];
    for (int i = 1; i < n; ++i)
        max_left[i] = max(max_left[i - 1], a[i]);
    max_right[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; --i)
        max_right[i] = max(max_right[i + 1], a[i]);

    ll res = 0;
    FOR(i, 0, n - 1)
    {
        int h = min(max_left[i], max_right[i]);
        if (h > a[i])
            res += h - a[i];
    }

    cout << res;
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