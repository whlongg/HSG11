#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int MOD = 1e9 + 7;

int n, m;
int L[N], R[N];
int par[N][20], dep[N];
int maxL[N], minR[N];
int uf[N];
long long ways[N];
long long total = 1;

vector<int> tree[N];

void dfs(int u, int p)
{
    par[u][0] = p;
    for (int i = 1; i < 20; ++i)
    {
        if (par[u][i - 1] != -1)
            par[u][i] = par[par[u][i - 1]][i - 1];
        else
            par[u][i] = -1;
    }
    for (int v : tree[u])
    {
        if (v != p)
        {
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
}

int get_kth(int u, int k)
{
    for (int i = 0; i < 20; ++i)
    {
        if ((k >> i) & 1)
        {
            u = par[u][i];
            if (u == -1)
                break;
        }
    }
    return u;
}

int lca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    u = get_kth(u, dep[u] - dep[v]);
    if (u == v)
        return u;
    for (int i = 19; i >= 0; --i)
    {
        if (par[u][i] != -1 && par[u][i] != par[v][i])
        {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

int find(int u)
{
    if (uf[u] != u)
        uf[u] = find(uf[u]);
    return uf[u];
}

long long inv(long long x)
{
    long long res = 1, p = MOD - 2;
    while (p)
    {
        if (p & 1)
            res = res * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return res;
}

void unite(int u, int v)
{
    u = find(u);
    v = find(v);
    if (u == v)
        return;
    total = total * inv(ways[u]) % MOD;
    total = total * inv(ways[v]) % MOD;
    maxL[u] = max(maxL[u], maxL[v]);
    minR[u] = min(minR[u], minR[v]);
    ways[u] = max(0LL, minR[u] - maxL[u] + 1LL);
    total = total * ways[u] % MOD;
    uf[v] = u;
}

void process_query(int a, int b, int c, int d)
{
    vector<int> path_ab, path_cd;
    int lca_ab = lca(a, b);
    int lca_cd = lca(c, d);

    int u = a;
    while (u != lca_ab)
    {
        path_ab.push_back(u);
        u = par[u][0];
    }
    path_ab.push_back(lca_ab);

    vector<int> temp;
    u = b;
    while (u != lca_ab)
    {
        temp.push_back(u);
        u = par[u][0];
    }
    reverse(temp.begin(), temp.end());
    for (int node : temp)
        path_ab.push_back(node);

    u = c;
    while (u != lca_cd)
    {
        path_cd.push_back(u);
        u = par[u][0];
    }
    path_cd.push_back(lca_cd);

    temp.clear();
    u = d;
    while (u != lca_cd)
    {
        temp.push_back(u);
        u = par[u][0];
    }
    reverse(temp.begin(), temp.end());
    for (int node : temp)
        path_cd.push_back(node);

    if (path_ab.size() != path_cd.size())
        return;

    for (size_t i = 0; i < path_ab.size(); ++i)
    {
        unite(path_ab[i], path_cd[i]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    memset(par, -1, sizeof(par));
    for (int i = 2; i <= n; ++i)
    {
        int p;
        cin >> p;
        tree[p].push_back(i);
        tree[i].push_back(p);
    }
    for (int i = 1; i <= n; ++i)
    {
        cin >> L[i] >> R[i];
        maxL[i] = L[i];
        minR[i] = R[i];
        ways[i] = max(0LL, minR[i] - maxL[i] + 1LL);
        uf[i] = i;
        total = total * ways[i] % MOD;
    }
    dep[1] = 0;
    dfs(1, -1);

    cin >> m;
    while (m--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        process_query(a, b, c, d);
        cout << total << '\n';
    }
    return 0;
}