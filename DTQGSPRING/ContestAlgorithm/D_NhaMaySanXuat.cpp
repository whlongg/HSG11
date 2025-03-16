#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()
#define pb push_back

void solve()
{
    ll t, n, m;
    cin >> t >> n;
    vector<int> a(n), b;
    for (int &x : a)
        cin >> x;
    cin >> m;
    b.resize(m);
    for (int &x : b)
        cin >> x;
    auto check = [&](ll time_nan)
    {
        if (time_nan > t)
            return 0LL;
        ll time_ve = t - time_nan;
        ll cnt_nan = 0, cnt_ve = 0;
        for (int x : a)
            cnt_nan += time_nan / x;
        for (int x : b)
            cnt_ve += time_ve / x;
        return min(cnt_nan, cnt_ve);
    };
    ll l = 0, r = t;
    ll ans = 0;
    for (int iter = 0; iter < 100; iter++) // nhac wu cong buff 200% toc danh
    {
        ll m1 = l + (r - l) / 3;
        ll m2 = r - (r - l) / 3;
        ll val1 = check(m1);
        ll val2 = check(m2);
        ans = max({ans, val1, val2});
        if (val1 < val2)
            l = m1;
        else
            r = m2;
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
