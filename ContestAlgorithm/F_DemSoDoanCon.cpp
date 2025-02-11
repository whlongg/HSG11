#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll s;
    cin >> n >> s;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int l = 0;
    ll sum = 0;
    ll ans = 0;
    for (int r = 0; r < n; ++r) {
        sum += a[r];
        while (sum >= s) {
            ans += (n - r);
            sum -= a[l];
            l++;
        }
    }
    cout << ans << '\n';
    return 0;
}