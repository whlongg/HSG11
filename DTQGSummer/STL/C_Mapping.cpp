// DTQGSummer/STL/C_Mapping.cpp
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
    map<int, int> mp;
    for (int i = 1; i <= n; ++i)
    {
        getline(cin, line);
        stringstream ss(line);
        ss >> s >> k;

        if (s == "add")
            mp[k]++;
        else if (s == "del" && mp.count(k) > 1)
            mp[k]--;
        else if (s == "del" && mp.count(k) == 1)
            mp.erase(k);
        else if (s == "count")
            cout << ((mp.count(k)>0)?mp[k]:0) << '\n';
        else if (s == "size")
            cout << mp.size() << '\n';
    }
}

int32_t main(void)
{
    FASTIO;
    // #ifndef ONLINE_JUDGE
    //     init();
    // #endif
    int q = 1;
    // cin >> q;
    while (q--)
        solve();
}