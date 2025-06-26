// DTQGSummer/Bitwise/B_SUM-XOR.cpp


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
#define ull unsigned long long

void init()
{
    file("testcs.inp", "testcs.out");
}

// a+b = a ^ b => bit a[i] ≠ bit b[i];
//  => a & b == 0
//=> cho b, đếm số a t/m;
// 0 ≤ a ≤ b
// a & b == 0

void solve()
{
    ull b;
    cin >> b;
    if (b == 0)
    {
        cout << 1;
        return;
    }
    int z = 0;
    while (b > 0)
    {
        if ((b & 1) == 0)
            z++;
        b >>= 1;
    }
    ull ans = 1ULL << z;
    cout << ans;
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