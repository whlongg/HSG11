// DTQGSummer/Recursion/tamphan.cpp
//AC with C++20 (GCC13-64)
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

void init()
{
    file("testcs.inp", "testcs.out");
}

void np(int n, string s = "")
{
    if ((int)s.size() == n)
    {
        cout << s << '\n';
        return;
    }
    for (char c = '0'; c <= '2'; ++c)
        np(n, s + c);
}

void solve()
{
    int n;
    cin >> n;
    np(n);
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