// DTQGSummer/SoHoc/C_PhanTichThuaSoNguyenTo.cpp


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
#define MAX 1000000009
#define MOD 1000000007

void init()
{
    file("testcs.inp", "testcs.out");
}

map<ll, ll> mp;

void solve()
{
    ll n;
    cin >> n;
    for (ll i = 2; i * i <= n; ++i)
    {
        int res = 0;
        while (n % i == 0)
        {
            res++;
            n /= i;
            mp[i]++;
        }
    }
    if (n > 1)
    {
        mp[n]++;
    }
    cout << mp.size() << '\n';
    for (auto [x, k] : mp)
    {
        cout << x << ' ' << k << '\n';
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