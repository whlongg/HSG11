// DTQGSummer/Recursion/H_NquanHau.cpp
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
    file("queens.inp", "queens.out");
}

int ans = 0;
char board[8][8];
bool d1[15], d2[15], col[8];

void backtrack(int r)
{
    if (r == 8)
    {
        ans++;
        return;
    }

    for (int c = 0; c < 8; c++)
    {
        if (board[r][c] == '*' || col[c] || d1[r - c + 7] || d2[r + c])
            continue;
        col[c] = d1[r - c + 7] = d2[r + c] = true;
        backtrack(r + 1);
        col[c] = d1[r - c + 7] = d2[r + c] = false;
    }
}

void solve()
{
    string s;
    for (int i = 0; i < 8; ++i)
    {
        cin >> s;
        for (int _ = 0; _ < 8; ++_)
        {
            board[i][_] = s[_];
        }
    }

    backtrack(0);
    cout << ans;
}

int32_t main(void)
{
    FASTIO;
    init();
    int q = 1;
    // cin >> q;
    while (q--)
        solve();
}