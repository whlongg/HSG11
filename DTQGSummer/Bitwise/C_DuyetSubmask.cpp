// DTQGSummer/Bitwise/C_DuyetSubmask.cpp


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
    int n;
    cin >> n;
    for (int i = 0; i < (1 << n); ++i)
    {
        vector<int> smasks;
        for (int sub = i;; sub = (sub - 1) & i)
        {
            smasks.push_back(sub);
            if (sub == 0)
                break;
        }
        reverse(smasks.begin(), smasks.end());
        for (int sub : smasks)
        {
            cout << bitset<13>(sub).to_string().substr(13 - n) << '\n';
        }
        if (i < (1 << n) - 1)
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