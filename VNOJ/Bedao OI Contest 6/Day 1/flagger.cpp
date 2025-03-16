#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1000000007;

ll power_mod_func(ll x, ll y)
{
    ll res = 1;
    x %= MOD;
    while (y > 0)
    {
        if (y & 1LL)
            res = res * x % MOD;
        x = x * x % MOD;
        y >>= 1LL;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);cin.tie(0);
    freopen("flagger.inp", "r", stdin);
    freopen("flagger.out", "w", stdout);
    int n, m;
    cin >> n >> m;

    int K = min(n, m);
    vector<vector<ll>> Cn(n + 1, vector<ll>(K + 1, 0));
    vector<vector<ll>> Cm(m + 1, vector<ll>(K + 1, 0));

    for (int i = 0; i <= n; i++)
    {
        Cn[i][0] = 1;
        for (int k = 1; k <= min(i, K); k++)
        {
            Cn[i][k] = (Cn[i - 1][k] + Cn[i - 1][k - 1]) % MOD;
        }
    }

    for (int i = 0; i <= m; i++)
    {
        Cm[i][0] = 1;
        for (int k = 1; k <= min(i, K); k++)
        {
            Cm[i][k] = (Cm[i - 1][k] + Cm[i - 1][k - 1]) % MOD;
        }
    }

    vector<ll> fact(K + 1, 1);
    for (int k = 1; k <= K; k++)
    {
        fact[k] = fact[k - 1] * k % MOD;
    }

    vector<ll> pow4(K + 1, 1);
    for (int k = 1; k <= K; k++)
    {
        pow4[k] = pow4[k - 1] * 4 % MOD;
    }

    ll row_pairs = (ll)n * ((m >= 2) ? ((ll)m * (m - 1) / 2 % MOD) : 0) % MOD;

    ll column_pairs = (ll)m * ((n >= 2) ? ((ll)n * (n - 1) / 2 % MOD) : 0) % MOD;

    ll solitary_flags = 0;
    for (int k = 1; k <= K; k++)
    {
        ll Cnk = Cn[n][k];
        ll Cmk = Cm[m][k];
        ll fk = fact[k];
        ll p4k = pow4[k];
        ll term = (((Cnk * Cmk) % MOD) * (fk)) % MOD;
        term = (term * p4k) % MOD;
        solitary_flags = (solitary_flags + term) % MOD;
    }

    ll total = (row_pairs + column_pairs) % MOD;
    total = (total + solitary_flags) % MOD;
    cout << total;
}