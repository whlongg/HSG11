#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//commit main.
/* AUTO-SYNC STATUS START */
/* ℹ️ Committing to branch 'main'... */
/* ⏱️ Thời gian: 23:37:00 19/03/2025 */
/* AUTO-SYNC STATUS END */
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x : a) cin >> x;
    vector<ll> pref(n+1, 0);
    for(int i = 0; i < n; i++)
        pref[i+1] = pref[i] + a[i];
    int sizeb = max(1, (int)sqrt(n * (n+1) / 2 / 100));
    int numb = (n*(n+1)/2 + sizeb - 1) / sizeb;
    vector<ll> sumb(numb, 0);
    vector<pair<int,int>> mp(n*(n+1)/2 + 1);
    int idx = 1;
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++)
            mp[idx++] = {i, j};
    for(int i = 1; i <= n*(n+1)/2; i++) {
        auto [left, right] = mp[i];
        ll sums = pref[right+1] - pref[left];
        sumb[(i-1) / sizeb] += sums;
    }
    int q;
    cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        int lb = (l-1) / sizeb;
        int rb = (r-1) / sizeb;
        ll ans = 0;
        if(lb == rb) {
            for(int i = l; i <= r; i++) {
                auto [left, right] = mp[i];
                ans += pref[right+1] - pref[left];
            }
        } else {
            for(int i = lb+1; i < rb; i++)
                ans += sumb[i];
            for(int i = l; i <= (lb+1)*sizeb; i++) {
                auto [left, right] = mp[i];
                ans += pref[right+1] - pref[left];
            }
            for(int i = rb*sizeb+1; i <= r; i++) {
                auto [left, right] = mp[i];
                ans += pref[right+1] - pref[left];
            }
        }
        cout << ans << '\n';
    }
    return 0;
}