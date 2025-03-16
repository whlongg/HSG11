#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;
int phi[N + 1];

void sieve()
{
    for (int i = 1; i <= N; i++)
    {
        phi[i] = i;
    }
    for (int i = 2; i <= N; i++)
    {
        if (phi[i] == i)
        {
            for (int j = i; j <= N; j += i)
            {
                phi[j] -= phi[j] / i;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    sieve();
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        cout << phi[n] << '\n';
    }
    return 0;
}