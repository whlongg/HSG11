// DTQGSummer/Recursion/I_TongCapSoNhan.cpp
//https://yugihacker25summer.contest.codeforces.com/group/xiGaexJSKw/contest/611733/problem/I

//AC with this recipe: 
/*
    S(a,n)={
                1                                   n=0
                S(a, n / 2) x ( 1 + a ^ ((n+1)/2))  n le
                S(a, n-1) + a mu n mod m            n chan
           }
*/
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
#define MAX 1000000009
#define MOD 1000000007

void init()
{
    file("testcs.inp", "testcs.out");
}

int powmod(int a, int n, int mod)
{
    int res = 1;
    int base = a % mod;
    while (n > 0)
    {
        if (n & 1)
            res = (1LL * res * base) % mod;
        base = (1LL * base * base) % mod;
        n >>= 1;
    }
    return res;
}

int recur(int a, int n, int mod)
{
    if (n == 0)
        return 1 % mod;
    if (n % 2 == 1)
    {
        int inv = recur(a, n / 2, mod);
        int p = powmod(a, n / 2 + 1, mod);
        return (inv + inv * p % mod) % mod;
    }
    else
    {
        int inv = recur(a, n - 1, mod);
        int p = powmod(a, n, mod);
        return (inv + p) % mod;
    }
}

void solve()
{
    int a, n, mod;
    cin >> a >> n >> mod;
    cout << recur(a, n, mod);
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