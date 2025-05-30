// DTQGSummer/Recursion/D_TongTapCon.cpp
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

void init()
{
    file("testcs.inp", "testcs.out");
}

vector<int> a, subs;
int n, s, res;

void backtrack(int i, int sum)
{
    if (i == n)
    {
        if (sum == s && !subs.empty())
        {
            res++;
        }
        return;
    }
    backtrack(i + 1, sum);

    subs.push_back(a[i]);
    backtrack(i + 1, sum + a[i]);
    subs.pop_back();
}

void solve()
{
    int _;
    cin >> n >> s;
    for (int i = 1; i <= n; ++i)
        cin >> _, a.push_back(_);
    backtrack(0, 0);
    cout << res;
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