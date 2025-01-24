#include <bits/stdc++.h>
using namespace std;

bool ok(vector<int> &v)
{
    int n = v.size();
    if (n == 1)
        return true;
    if (n == 2)
        return v[0] != v[1];
    int peak = 0, pos = -1;
    for (int i = 0; i < n; i++)
        if ((i == 0 || v[i] > v[i - 1]) && (i == n - 1 || v[i] > v[i + 1]))
        {
            peak++;
            pos = i;
        }
    if (peak != 1)
        return false;
    for (int i = 1; i < pos; i++)
        if (v[i] <= v[i - 1])
            return false;
    for (int i = pos + 1; i < n; i++)
        if (v[i] >= v[i - 1])
            return false;

    return true;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        vector<int> tmp(a.begin() + l - 1, a.begin() + r);
        cout << (ok(tmp) ? "Yes\n" : "No\n");
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
