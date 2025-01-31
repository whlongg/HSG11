#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;
int backtrack(int a, int n)
{
    if (n == 0)
    {
        return 1;
    }
    int tmp = backtrack(a, n / 2);
    tmp = (tmp * tmp) % MOD;
    if (n % 2)
        tmp = (tmp * a)%MOD;
    return tmp;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int b, a;
        cin >> a >> b;
        cout << backtrack(a, b) << '\n';
    }
}