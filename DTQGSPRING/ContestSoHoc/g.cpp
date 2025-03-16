#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

ll power(ll a, ll b, ll m)
{
    ll r = 1;
    a %= m;
    while (b > 0)
    {
        if (b & 1)
            r = (r * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return r;
}

ll inv(ll a, ll m)
{
    ll x, y;
    ll g = gcd(a, m);
    if (g != 1)
        return -1;

    function<void(ll, ll)> euclid = [&](ll a, ll b)
    {
        if (b == 0)
        {
            x = 1;
            y = 0;
            return;
        }
        euclid(b, a % b);
        ll x1 = y;
        ll y1 = x - (a / b) * y;
        x = x1;
        y = y1;
    };

    euclid(a, m);
    return (x % m + m) % m;
}

int main()
{
    ll a, m;
    cin >> a >> m;
    cout << inv(a, m) << '\n';
    return 0;
}