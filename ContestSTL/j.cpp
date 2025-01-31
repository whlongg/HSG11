#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, x;
    cin >> n >> x;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n - 2; i++)
    {
        int left = i + 1;
        int right = n - 1;
        while (left < right)
        {
            long long sum = (long long)a[i].first + a[left].first + a[right].first;
            if (sum == x)
            {
                cout << a[i].second << " " << a[left].second << " " << a[right].second << endl;
                return 0;
            }
            else if (sum < x)
            {
                left++;
            }
            else
            {
                right--;
            }
        }
    }
    cout << "IMPOSSIBLE" << endl;
    return 0;
}