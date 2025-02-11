#include <bits/stdc++.h>
using namespace std;
#define double long double

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    double s;
    cin >> s;
    double l = 0, r = s;
    while (r - l > 1e-12)
    {
        double mid = (l + r) / 2;
        if (mid * mid + sqrt(mid) >= s)
            r = mid;
        else
            l = mid;
    }
    cout << fixed << setprecision(6) << l << endl;
    return 0;
}