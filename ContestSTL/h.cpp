#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<long long>> a(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    vector<long long> rs(n + 1, 0);
    vector<long long> cs(m + 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            rs[i] += a[i][j];
            cs[j] += a[i][j];
        }
    vector<int> r_mp(n + 1);
    for (int i = 1; i <= n; i++)
    {
        r_mp[i] = i;
    }

    for (int k = 0; k < q; k++)
    {
        char t;
        cin >> t;
        if (t == '1')
        {
            int r1, r2;
            cin >> r1 >> r2;
            swap(r_mp[r1], r_mp[r2]);
            swap(rs[r1], rs[r2]);
        }
        else if (t == '2')
        {
            int r, c;
            long long v;
            cin >> r >> c >> v;
            int real_r = r_mp[r];
            rs[r] -= a[real_r][c];
            cs[c] -= a[real_r][c];
            a[real_r][c] = v;
            rs[r] += a[real_r][c];
            cs[c] += a[real_r][c];
        }
        else if (t == 'r')
        {
            int r;
            cin >> r;
            cout << rs[r] << '\n';
        }
        else if (t == 'c')
        {
            int c;
            cin >> c;
            cout << cs[c] << '\n';
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            cout << a[r_mp[i]][j] << (j == m ? "" : " ");
        cout << '\n';
    }
    return 0;
}