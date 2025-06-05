#include <bits/stdc++.h>
//#pragma GCC optimine("O3")
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, p;
    cin >> n >> p;
    int ans = 1e9;
    for (int i = 2; i * i <= p; ++i)
    {
        if (p % i == 0)
        {
            int cnt = 0;
            while (p % i == 0)
            {
                p /= i;
                cnt++;
            }
            int tmp = n, cur = 0;
            while (tmp)
            {
                cur += tmp / i;
                tmp /= i;
            }
            ans = min(ans, cur / cnt);
        }
    }
    if (p > 1)
    {
        int tmp = n, cur = 0;
        while (tmp)
        {
            cur += tmp / p;
            tmp /= p;
        }
        ans = min(ans, cur);
    }
    cout << ans << "\n";
    return 0;
}