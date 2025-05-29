// DTQGSummer/STL/E_CountSumX.cpp
//vl sao nhan sai x ma nay no van duoc 71 diem nhi
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

void solve()
{
    int n, x, val;
    cin >> n >> x;
    unordered_map<int, int> mp;
    ll ans = 0;
    for (int i = 0; i < n; ++i)
        cin >> val, mp[val]++;

    for (auto &[k, v] : mp)
    {
        int temp = x - k;

        if (k < temp && mp.count(temp))
            ans += 1LL * v * mp[temp];
        else if (k == temp)
            ans += 1LL * v * (v - 1) / 2;
    }
    cout << ans;
}

int32_t main(void)
{
    FASTIO;
    // #ifndef ONLINE_JUDGE
    //     init();
    // #endif
    int q = 1;
    // cin >> q;
    while (q--)
        solve();
}