// DTQGSummer/PrefixSum/J_TongDoanCuaTongDoan.cpp


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
    file("testcs.inp", "testcs.out");
}

ll get_sum(ll k, int n, const vector<ll> &pa, const vector<ll> &ppa, const vector<ll> &b_cnt, const vector<ll> &b_sum)
{
    if (k == 0)
        return 0;

    int low = 1, high = n, p = 0;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (b_cnt[mid] <= k)
        {
            p = mid;
            low = mid + 1;
        }
        else
            high = mid - 1;
    }

    ll total = 0;
    if (p > 0)
        total = b_sum[p];
    ll done_cnt = (p > 0) ? b_cnt[p] : 0;
    ll rem_cnt = k - done_cnt;

    if (rem_cnt > 0)
    {
        int c_block = p + 1;
        ll endj = c_block + rem_cnt - 1;
        ll spa = ppa[endj] - ppa[c_block - 1];
        ll sval = rem_cnt * pa[c_block - 1];
        total += (spa - sval);
    }
    return total;
}

void solve()
{
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    vector<ll> pa(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        pa[i] = pa[i - 1] + a[i];
    vector<ll> ppa(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        ppa[i] = ppa[i - 1] + pa[i];
    vector<ll> block_ecnt(n + 1, 0);
    FOR(i, 1, n)
    block_ecnt[i] = n - i + 1;
    vector<ll> b_cnt(n + 1, 0);
    FOR(i, 1, n)
    b_cnt[i] = b_cnt[i - 1] + block_ecnt[i];
    vector<ll> block_vsum(n + 1, 0);
    FOR(i, 1, n)
    block_vsum[i] = (ppa[n] - ppa[i - 1]) - (n - i + 1) * pa[i - 1];
    vector<ll> b_sum(n + 1, 0);
    FOR(i, 1, n)
    b_sum[i] = b_sum[i - 1] + block_vsum[i];

    int q;
    cin >> q;
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        ll sum_r = get_sum(r, n, pa, ppa, b_cnt, b_sum);
        ll sum_l = get_sum(l - 1, n, pa, ppa, b_cnt, b_sum);
        cout << sum_r - sum_l << '\n';
    }
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