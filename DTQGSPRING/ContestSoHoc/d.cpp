#include <bits/stdc++.h>
using namespace std;
const int N = 1e7;
int prime[N + 1]; // Sửa kích thước mảng

void sangnguyento()
{
    for (int i = 2; i <= N; ++i)
        prime[i] = 1;
    prime[0] = prime[1] = 0;
    for (int i = 2; i * i <= N; ++i)
    {
        if (prime[i])
        {
            for (int j = i * i; j <= N; j += i)
            {
                prime[j] = 0;
            }
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    sangnguyento();
    int n;
    cin >> n;
    long long ans = 0;
    for (int i = 2; i <= n; ++i)
    {
        if (prime[i])
        {
            ans += i;
        }
    }
    cout << ans;
    return 0;
}