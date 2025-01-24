#include <bits/stdc++.h>
using namespace std;
const int N = 405;
int n, a[N][N], s1[N][N], s2[N][N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    for (int len = 1; len <= n; len++)
        for (int i = 0; i + len <= n; i++)
            for (int j = 0; j + len <= n; j++)
            {
                s1[i + len][j + len] = s1[i + len - 1][j + len - 1] + a[i + len - 1][j + len - 1];
                s2[i + len][j] = s2[i + len - 1][j + 1] + a[i + len - 1][j];
            }
    int ans = INT_MIN;
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len <= n; i++)
            for (int j = 0; j + len <= n; j++)
                ans = max(ans, s1[i + len][j + len] - s1[i][j] -
                                   (s2[i + len][j] - s2[i][j + len]));
    cout << ans;
    return 0;
}
