//nguyenhoanglong
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<int> inc(n + 2, 0);
    inc[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[i] >= a[i-1]) inc[i] = inc[i-1];
        else inc[i] = i;
    }
    vector<int> dec(n + 2, n + 1);
    dec[n] = n;
    for (int i = n - 1; i >= 1; --i) {
        if (a[i] >= a[i+1]) dec[i] = dec[i+1];
        else dec[i] = i;
    }
    int log_n = log2(n) + 1;
    vector<vector<int> > st(n + 1, vector<int>(log_n));
    for (int i = 1; i <= n; ++i)
        st[i][0] = i;
    for (int j = 1; (1 << j) <= n; ++j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            int l = st[i][j-1];
            int r = st[i + (1 << (j-1))][j-1];
            st[i][j] = (a[l] >= a[r]) ? l : r;
        }
    while (q--) {
        int l, r;
        cin >> l >> r;
        if (l == r) {
            cout << "Yes\n";
            continue;
        }
        int k = log2(r - l + 1);
        int pos1 = st[l][k];
        int pos2 = st[r - (1 << k) + 1][k];
        int max_pos = (a[pos1] >= a[pos2]) ? pos1 : pos2;
        bool ans = (inc[max_pos] <= l) && (dec[max_pos] >= r);
        cout << (ans ? "Yes\n" : "No\n");
    }
    return 0;
}