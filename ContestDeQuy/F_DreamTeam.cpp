<<<<<<< HEAD
#include <bits/stdc++.h>
using namespace std;
int n, k, m, ans;
bool bad[11][11];
int t[10];

bool ok(int u, int tid)
{
    for (int i = 0; i < u; i++)
        if (t[i] == tid && bad[i + 1][u + 1])
            return 0;
    return 1;
}
void go(int u, int cnt)
{
    if (u == n)
    {
        ans += (cnt == k);
        return;
    }
    for (int i = 0; i < cnt; i++)
        if (ok(u, i))
        {
            t[u] = i;
            go(u + 1, cnt);
        }
    if (cnt < k)
    {
        t[u] = cnt;
        go(u + 1, cnt + 1);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k >> m;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        bad[u][v] = bad[v][u] = 1;
    }
    go(0, 0);
    cout << ans;
    return 0;
}
=======
#include <bits/stdc++.h>
using namespace std;
int n, k, m, ans;
bool bad[11][11];
int t[10];

bool ok(int u, int tid)
{
    for (int i = 0; i < u; i++)
        if (t[i] == tid && bad[i + 1][u + 1])
            return 0;
    return 1;
}
void go(int u, int cnt)
{
    if (u == n)
    {
        ans += (cnt == k);
        return;
    }
    for (int i = 0; i < cnt; i++)
        if (ok(u, i))
        {
            t[u] = i;
            go(u + 1, cnt);
        }
    if (cnt < k)
    {
        t[u] = cnt;
        go(u + 1, cnt + 1);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k >> m;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        bad[u][v] = bad[v][u] = 1;
    }
    go(0, 0);
    cout << ans;
    return 0;
}
>>>>>>> 5c268531b0287f0d2fe68db2110832e6f8451896
