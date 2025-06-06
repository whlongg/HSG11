// DTQGSummer/PrefixSum/B_DemCay.cpp


/*
    author: Nguyen Hoang Long
    oj.vnoi.info/user/nhl08contact
*/
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
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define REP(i, b) for (int i = 1; i <= n; ++i)
const int MAX = 1e6 + 5;
#define MOD 1000000007

void init()
{
    file("testcs.inp", "testcs.out");
}

int arr[1003][1003];
int prefix[1003][1003];
void solve(int r1, int c1, int r2, int c2)
{
    cout << prefix[r2][c2] - prefix[r1 - 1][c2] - prefix[r2][c1 - 1] + prefix[r1 - 1][c1 - 1] << '\n';
}

int32_t main(void)
{
    FASTIO;
#ifndef ONLINE_JUDGE
    init();
#endif
    int q = 1, n;
    cin >> n >> q;
    FOR(i, 1, n)
    {
        FOR(j, 1, n)
        {
            char s;
            cin >> s;
            if (s == '.')
                arr[i][j] = 0;
            else
                arr[i][j] = 1;
        }
    }
    FOR(i, 1, n)
        FOR(j, 1, n)
            prefix[i][j] = arr[i][j] + prefix[i][j - 1] + prefix[i - 1][j] - prefix[i - 1][j - 1];
    while (q--)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        solve(r1, c1, r2, c2);
    }
}