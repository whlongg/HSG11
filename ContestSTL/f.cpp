#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, ans = 0;
    cin >> n >> m;
    vector<set<int>> s(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            int x;
            cin >> x;
            s[i].insert(x);
        }
    vector<bool> c(n, false);
    for (int i = 0; i < n; i++)
        if (!c[i])
        {
            ans++;
            c[i] = true;
            for (int j = i + 1; j < n; j++)
            {
                if (!c[j] && s[i] == s[j])
                {
                    c[j] = true;
                }
            }
        }
    cout << ans;
    return 0;
}