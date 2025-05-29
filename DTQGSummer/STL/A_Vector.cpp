// DTQGSummer/STL/A_Vector.cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out)          \
    freopen((inp), "r", stdin); \
    freopen((out), "w", stdout);
#define FASTIO                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(nullptr);
void init()
{
    file("testcs.inp", "testcs.out");
}

void solve()
{
    int n;
    cin >> n;
    cin.ignore();
    string s, line;
    int k;
    vector<int> v;
    for (int i = 1; i <= n; ++i)
    {
        getline(cin, line);
        stringstream ss(line);
        ss >> s >> k;
        //cout << s << ' ' << k << '\n';
        if (s == "push")
            v.push_back(k);
        else if (s == "pop" && !v.empty())
            v.pop_back();
        else if (s == "index")
        {
            if (0 <= k && k - 1 < v.size())
                cout << v[k - 1] << '\n';
            else
                cout << -1 << '\n';
        }
        else if (s == "size")
            cout << v.size() << '\n';
    }
}

int32_t main(void)
{
    FASTIO;
    #ifndef ONLINE_JUDGE
        init();
    #endif
    int q = 1;
    // cin >> q;
    while (q--)
        solve();
}