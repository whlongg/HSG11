#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    long long res = 0;
    int left = 0;
    int right = n - 1;
    while (left < right)
    {
        if (a[left] + a[right] == x)
        {
            int left_count = 1;
            int right_count = 1;
            while (left + 1 < right && a[left] == a[left + 1])
            {
                left++;
                left_count++;
            }
            while (right - 1 > left && a[right] == a[right - 1])
            {
                right--;
                right_count++;
            }
            if (a[left] == a[right])
                res += (long long)left_count * (left_count - 1) / 2;
            else
                res += (long long)left_count * right_count;
            left++;
            right--;
        }
        else if (a[left] + a[right] < x)
            left++;
        else
            right--;
    }
    cout << res;
    return 0;
}