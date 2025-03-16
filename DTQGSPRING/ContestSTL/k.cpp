#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    pq.push({a[0] + b[0], {0, 0}});
    set<pair<int, int>> visited;
    visited.insert({0, 0});
    for (int i = 0; i < k; ++i) {
        int sum = pq.top().first;
        int index_a = pq.top().second.first;
        int index_b = pq.top().second.second;
        pq.pop();
        cout << sum << (i == k - 1 ? "" : " ");
        if (index_a + 1 < n && visited.find({index_a + 1, index_b}) == visited.end()) {
            pq.push({a[index_a + 1] + b[index_b], {index_a + 1, index_b}});
            visited.insert({index_a + 1, index_b});
        }
        if (index_b + 1 < n && visited.find({index_a, index_b + 1}) == visited.end()) {
            pq.push({a[index_a] + b[index_b + 1], {index_a, index_b + 1}});
            visited.insert({index_a, index_b + 1});
        }
    }
    cout << '\n';
    return 0;
}