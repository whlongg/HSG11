#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define all(x) begin(x), end(x)
const ll INF = 2e9;

bool check(ll k, ll t, vector<int> &a, vector<int> &b)
{
    if (!k)
        return true;
    ll l = 0, r = t;
    ll time_nan = -1;
    while (l <= r)
    {
        ll mid = l + (r - l) / 2;
        ll cnt = 0;
        for (int x : a)
            cnt += mid / x;
        if (cnt >= k)
        {
            time_nan = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    if (time_nan == -1 || time_nan > t)
        return false;
    ll rem = t - time_nan;
    ll cnt = 0;
    for (int x : b)
        cnt += rem / x;
    return cnt >= k;
}

void solve()
{
    ll t;
    int n;
    cin >> t >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    int m;
    cin >> m;
    vector<int> b(m);
    for (int &x : b)
        cin >> x;
    sort(all(a));
    sort(all(b));
    ll l = 0, r = INF;
    ll ans = 0;
    while (l <= r)
    {
        ll mid = l + (r - l) / 2;
        if (check(mid, t, a, b))
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
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