#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
ll d[1002][1002], prefix[1002][1002];

int main() {
    fast;
    int n, m, q;
    cin >> n >> m >> q;
    while (q--) {
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        d[x1][y1] += c;
        d[x1][y2 + 1] -= c;
        d[x2 + 1][y1] -= c; 
        d[x2 + 1][y2 + 1] += c;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            prefix[i][j] = d[i][j] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cout << prefix[i][j] << ' ';
        }
        cout << '\n';
    }
}