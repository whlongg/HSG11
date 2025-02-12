#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    sort(a.begin(), a.end());
    while (q--) {
        int x, k;
        cin >> x >> k;
        ll l = 0, r = 2000000000LL * 2 + 1000;
        ll ans = r;
        while (l <= r) {
            ll mid = l + (r - l) / 2;
            int cnt = upper_bound(a.begin(), a.end(), x + mid) - lower_bound(a.begin(), a.end(), x - mid);
            if (cnt >= k) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}

//Nhạc wu công búp 200% sức mạnh