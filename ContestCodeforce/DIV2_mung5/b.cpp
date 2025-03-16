#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        vector<int> count(n + 2, 0);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
            if (a[i] <= n + 1)
            {
                count[a[i]]++;
            }
        }

        int limit = n + 1;
        vector<vector<int>> dp(limit + 1, vector<int>(k + 2, 0));

        for (int i = 1; i <= limit; ++i)
        {
            for (int j = 2; j <= k; j += 2)
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 2] + count[i]);
                dp[i][j - 1] = max(dp[i][j - 1], dp[i - 1][j - 1]);
                if (count[i] > 0)
                    dp[i][j - 1] = max(dp[i][j - 1], dp[i - 1][j - 2] + 1);
            }
            if (k % 2 == 0)
            {
                dp[i][k] = max(dp[i][k], dp[i - 1][k]);
            }
            else
            {
                dp[i][k - 1] = max(dp[i][k - 1], dp[i - 1][k - 1]);
            }
        }

        int ans = limit;
        for (int i = 1; i <= limit; ++i)
        {
            if (dp[i][k] < i)
            {
                ans = i;
                break;
            }
            if (k % 2 == 0 && dp[i][k - 1] < i)
            {
                ans = i;
                break;
            }
        }

        cout << ans << endl;
    }
    return 0;
}