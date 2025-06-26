// DTQGSummer/Sorting_TwoPointer_BinarySearch/A1_TKNP-Basic.cpp
/*
    author: Nguyen Hoang Long
    oj.vnoi.info/user/nhl08contact
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
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
// lb min it >= x;
// ub max it > x;

int a[MAX];
void solve(int n, int type, int target)
{
    if (type == 1)
    {
        int idx = lower_bound(a, a + n, target) - a;
        cout << ((idx < n && a[idx] == target) ? "YES" : "-1");
        cout << '\n';
    }
    else if (type == 2)
    {
        int idx = lower_bound(a, a + n, target) - a;
        cout << ((idx < n && a[idx] == target) ? idx+1 : -1) << '\n';
    }
    else
    {
        int idx = upper_bound(a, a + n, target) - a - 1;
        cout << ((idx >= 0 && a[idx] == target)?idx+1:-1) << '\n';
    }
}

int32_t main(void)
{
    FASTIO;
#ifndef ONLINE_JUDGE
    init();
#endif
    int q = 1;
    int n;
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    while (q--)
    {
        int t, x;
        cin >> t >> x;
        solve(n, t, x);
    }
}