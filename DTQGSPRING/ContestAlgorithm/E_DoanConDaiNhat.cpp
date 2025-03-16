#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll s;
    cin >> n >> s;
    int a[n];
    for (int &x : a)
        cin >> x;
    int l = 0, ans = 0;
    ll sum = 0;
    for (int r = 0; r < n; ++r)
    {
        sum += a[r];
        while (sum > s)
        {
            sum -= a[l];
            l++;
        }
        ans = max(ans, r - l + 1);
    }
    cout << ans << '\n';
}