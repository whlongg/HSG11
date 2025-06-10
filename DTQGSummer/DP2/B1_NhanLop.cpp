// DTQGSummer/DP2/B1_NhanLop.cpp


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

int dp[MAX];
struct cs
{
    int li, ri, wi;
};

bool cmp(const cs &a, const cs &b)
{
    if (a.ri != b.ri)
        return a.ri < b.ri;
    return a.li < b.li;
}

void solve()
{
    int n;
    cin >> n;
    cs v[n + 1];
    FOR(i, 1, n)
    cin >> v[i].li >> v[i].ri >> v[i].wi;
    sort(v + 1, v + n + 1, cmp);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        int curl = v[i].li, curw = v[i].wi;
        int notok = dp[i - 1];
        cs temp;
        temp.ri = curl - 1;
        temp.li = LLONG_MAX;
        auto check = upper_bound(v + 1, v + 1 + n, temp, cmp);
        int ok = curw;
        if (check != v + 1)
        { // tim thay
            int preidx = (check - v) - 1;
            ok += dp[preidx];
        }
        dp[i] = max(notok, ok);
        //cout << dp[i] << ' ' << v[i].li << ' ' << v[i].ri << ' ' << v[i].wi << ' ' << notok << ' ' << ok << ' ' << check - v - 1 << '\n';
    }
    cout << dp[n];
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