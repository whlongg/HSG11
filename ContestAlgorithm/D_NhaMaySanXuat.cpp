#include <bits/stdc++.h>
using namespace std;
#define ll long long

bool check(ll t, int n, int m, const vector<int> &a)
{
    ll count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (t / a[i] >= m)
            return true;
        count += t / a[i];
        if (count >= m)
            return true;
    }
    return count >= m;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    ll max_a = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        max_a = max(max_a, (ll)a[i]);
    }
    ll l = 0, r = max_a * m;
    ll ans = r;
    while (l <= r)
    {
        ll mid = l + (r - l) / 2;
        if (check(mid, n, m, a))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << ans << '\n';
    return 0;
}