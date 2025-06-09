// DTQGSummer/DP2/A3_BanhQuy.cpp


/*
    author: Nguyen Hoang Long
    oj.vnoi.info/user/nhl08contact
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
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
    file("cookies.inp", "cookies.out");
}

void solve()
{
    int n, k;
    cin >> n >> k;
    set<int> dp[2];
    dp[0].insert(n * 2);
    for (int i = 1; i <= k; ++i)
    {
        dp[i % 2].clear();
        for (int x : dp[(i - 1) % 2])
        {
            if (x % 2 == 0 && x >= 2)
                dp[i % 2].insert(x / 2);
            if(x>0) 
                dp[i % 2].insert(x - 1);
        }
    }
    cout << dp[k % 2].size() << '\n';
    for (int x : dp[k % 2])
        cout << fixed << setprecision(1) << (x / 2.0) << ' ';
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