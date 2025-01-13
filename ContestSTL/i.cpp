#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n;cin >> n;
    vector<long long> a(3 * n);
    for (int i = 0; i < 3 * n; i++)
        cin >> a[i];
    priority_queue<long long, vector<long long>, greater<long long>> pq1;
    priority_queue<long long> pq2;
    vector<long long> l(3 * n + 1, 0);
    vector<long long> r(3 * n + 1, 0);
    long long sum = 0;
    for (int i = 0; i < 3 * n; i++) {
        if (i < n) {
            pq1.push(a[i]);
            sum += a[i];
        } else if (pq1.size() > 0 && a[i] > pq1.top()) {
            sum -= pq1.top();
            pq1.pop();
            pq1.push(a[i]);
            sum += a[i];
        }
        l[i + 1] = sum;
    }
    sum = 0;
    for (int i = 3 * n - 1; i >= 0; i--) {
        if (i >= 2 * n) {
            pq2.push(a[i]);
            sum += a[i];
        } else if (pq2.size() > 0 && a[i] < pq2.top()) {
            sum -= pq2.top();
            pq2.pop();
            pq2.push(a[i]);
            sum += a[i];
        }
        r[i] = sum;
    }
    long long ans = -1e18;
    for (int i = n; i <= 2 * n; i++)
        ans = max(ans, l[i] - r[i]);
    cout << ans << endl;
    return 0;
}