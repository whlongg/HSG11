// DTQGSummer/SoHoc/K_Bo3So.cpp

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
const int N = 5e6 + 5;
#define MOD 1000000007

void init()
{
    file("triple.inp", "triple.out");
}

int min_prime[N];

void sieve()
{
    FOR(i, 2, N - 1)
    if (!min_prime[i])
        for (int j = i; j < N; j += i)
            if (!min_prime[j])
                min_prime[j] = i;
}

int core(int x)
{
    int res = 1;
    while (x > 1)
    {
        int p = min_prime[x];
        int cnt = 0;
        while (x % p == 0)
        {
            x /= p;
            cnt++;
        }
        if (cnt % 2 == 1)
            res *= p;
    }
    return res;
}

void solve()
{
    sieve();
    int n;
    cin >> n;

    unordered_map<int, int> cnt;
    for (int i = 1; i <= n; ++i)
    {
        int c = core(i);
        cnt[c]++;
    }

    int res = 0;
    for (auto [key, val] : cnt)
    {
        if (val >= 3)
            res += val * (val - 1) * (val - 2) / 6;
    }

    cout << res;
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