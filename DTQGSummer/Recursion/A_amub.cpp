// DTQGSummer/Recursion/amub.cpp
// AC with C++ 20 (GCC 13-64)
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
#define MOD 1000000007
void init()
{
    file("testcs.inp", "testcs.out");
}

int recur(ll a, ll b)
{
    a %= MOD;
    if (b == 0)
        return 1; //lmao qua set nham thanh 0....
    ll res = recur(a, b / 2);
    res = (res * res) % MOD;
    if (b % 2 == 1)
        res = (res * a) % MOD;
    return res;
}

void solve()
{
    int a, b;
    cin >> a >> b;
    cout << recur(a, b) << '\n';
}

int32_t main(void)
{
    FASTIO;
#ifndef ONLINE_JUDGE
    init();
#endif
    int q = 1;
    cin >> q;
    while (q--)
        solve();
}