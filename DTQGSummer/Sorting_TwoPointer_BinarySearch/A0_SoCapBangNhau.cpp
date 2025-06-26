// DTQGSummer/Sorting_TwoPointer_BinarySearch/A0_SoCapBangNhau.cpp
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
// lb >= x
// ub < x
void solve()
{
    int n, m;
    cin >> n >> m;
    int a[n], b[m];
    for (int &x : a)
        cin >> x;
    for (int &x : b)
        cin >> x;
    ll res = 0;
    for (int i = 0; i < n; ++i)
    {
        int check = a[i];
        int first_idx = lower_bound(b, b + m, check) - b;
        if (b[first_idx] == a[i])
        {
            int last_idx = upper_bound(b, b + m, check) - b;
            res += last_idx - first_idx;
        }
    }
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