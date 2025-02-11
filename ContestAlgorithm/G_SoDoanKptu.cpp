#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    int l = 0;
    map<int, int> cnt;
    ll ans = 0;
    for (int r = 0; r < n; ++r)
    {
        cnt[a[r]]++;
        while (cnt.size() > k)
        {
            cnt[a[l]]--;
            if (cnt[a[l]] == 0)
                cnt.erase(a[l]);
            l++;
        }
        ans += (r - l + 1);
    }
    cout << ans << '\n';
    return 0;
}