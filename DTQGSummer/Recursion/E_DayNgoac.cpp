// DTQGSummer/Recursion/E_DayNgoac.cpp
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

int cnt, n;
vector<string> ans;

void backtrack(string cur, int op, int cl)
{
    if (cur.length() == 2 * n)
    {
        ans.push_back(cur);
        cnt++;
        return;
    }

    if (op < n)
        backtrack(cur + '(', op + 1, cl);

    if (cl < op)
        backtrack(cur + ')', op, cl + 1);
}

void solve()
{
    cin >> n;
    backtrack("", 0, 0);
    cout << cnt << '\n';
    for (string s : ans)
        cout << s << '\n';
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