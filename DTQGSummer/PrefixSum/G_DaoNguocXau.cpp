// DTQGSummer/PrefixSum/G_DaoNguocXau.cpp


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

void solve()
{
    string s;
    cin >> s;
    int n = s.length();
    int q;
    cin >> q;

    vector<int> k(q);
    for (int i = 0; i < q; ++i)
        cin >> k[i];

    vector<bool> flip(n / 2 + 1, false);

    for (int i = 0; i < q; i++)
        flip[k[i]] = !flip[k[i]];

    for (int i = 1; i <= n / 2; i++)
        flip[i] = flip[i] ^ flip[i - 1];

    for (int i = 1; i <= n / 2; i++)
        if (flip[i])
            swap(s[i - 1], s[n - i]);
    cout << s << '\n';
    return;
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