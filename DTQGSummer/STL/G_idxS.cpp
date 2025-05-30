// DTQGSummer/STL/G_idxS.cpp
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
    cin >> n;
    map<int, vector<int>> mp;
    for (int i = 0; i < n; ++i)
    {
        int _;
        cin >> _;
        mp[_].push_back(i + 1);
    }

    for (auto &[val, pos] : mp)
    {
        cout << val << '\n';
        for (int i = 0; i < pos.size(); ++i)
        {
            cout << pos[i] << ((i == pos.size()) ? "" : " ");
        }
        cout << '\n';
    }
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