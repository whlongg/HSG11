#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n + 1);
    vector<long long> prefix_sum(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        prefix_sum[i] = prefix_sum[i - 1] + a[i];
    }

    int q;
    cin >> q;

    vector<tuple<long long, int, int>> segments;
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> pq;
    for (int i = 1; i <= n; ++i) {
        pq.push(make_tuple(prefix_sum[i] - prefix_sum[i - 1], i, i));
    }

    vector<long long> prefix_sum_b;
    vector<long long> index_map(n * (n + 1) / 2 + 1);
    prefix_sum_b.push_back(0);

    for (int i = 1; i <= n * (n + 1) / 2; ++i) {
        auto current = pq.top();
        long long sum = std::get<0>(current);
        int l = std::get<1>(current);
        int r = std::get<2>(current);
        pq.pop();
        prefix_sum_b.push_back(prefix_sum_b.back() + sum);
        index_map[i] = segments.size();
        segments.emplace_back(sum, l, r);
        if (r < n) {
            pq.push(make_tuple(prefix_sum[r + 1] - prefix_sum[l - 1], l, r + 1));
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << prefix_sum_b[r] - prefix_sum_b[l - 1] << endl;
    }

    return 0;
}