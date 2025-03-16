#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll &x : a)
        cin >> x;
    int l = 0;
    multiset<ll> s;
    ll ans = 0;
    for (int r = 0; r < n; ++r)
    {
        s.insert(a[r]);
        while (*s.rbegin() - *s.begin() > k)
        {
            s.erase(s.find(a[l]));
            l++;
        }
        ans += (r - l + 1);
    }
    cout << ans << '\n';
    return 0;
}