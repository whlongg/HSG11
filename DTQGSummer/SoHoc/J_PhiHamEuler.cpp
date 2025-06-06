// DTQGSummer/SoHoc/J_PhiHamEuler.cpp


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
    file("testcs.inp", "testcs.out");
}

int phi(int n)
{
    int res = n;
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            res -= res / i;
        }
    }
    if (n != 1)
        res -= res / n;
    return res;
}

void solve()
{
    int n;
    cin >> n;
    cout << phi(n);
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