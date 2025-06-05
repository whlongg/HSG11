// DTQGSummer/SoHoc/F_UocSNT.cpp


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
const int MAX = 1e6 + 5;
#define MOD 1000000007

void init()
{
    file("PRIME.INP", "PRIME.OUT");
}

int primes[MAX];
void sangnguyento()
{
    FOR(i, 2, MAX)
    primes[i] = 0;
    FOR(i, 2, MAX)
    {
        if (primes[i] == 0)
            for (int j = i; j < MAX; j += i)
                primes[j]++;
    }
}

void solve()
{
    sangnguyento();
    int n, res = -1, mcnt = -1;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        if (primes[x] > mcnt)
            mcnt = primes[x], res = x;
    }
    cout << res;
}

int32_t main(void)
{
    FASTIO;
//#ifndef ONLINE_JUDGE
    init();
//#endif
    int q = 1;
    // cin >> q;
    while (q--)
        solve();
}