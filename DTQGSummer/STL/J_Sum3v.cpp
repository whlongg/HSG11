// DTQGSummer/STL/J_Sum3v.cpp
//AC with C++20 (GCC 13-64)
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
    int n;
    ll x;
    cin >> n >> x;

    vector<pair<ll, int>> v(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i].first;
        v[i].second = i + 1;
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < n - 2; ++i)
    {
        ll target = x - v[i].first;
        int l = i + 1;
        int r = n - 1;

        while (l < r)
        {
            ll cur_sum = v[l].first + v[r].first;
            if (cur_sum == target)
            {
                cout << v[i].second << " " << v[l].second << " " << v[r].second << '\n';
                return;
            }
            else if (cur_sum < target)
                l++;
            else
                r--;
        }
    }

    cout << "IMPOSSIBLE\n";
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