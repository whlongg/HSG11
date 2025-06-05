// DTQGSummer/SoHoc/A_DemUoc2.cpp


/*
    author: Nguyen Hoang Long
    oj.vnoi.info/user/nhl08contact
*/
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
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define REP(i, b) for (int i = 1; i <= n; ++i)
#define MAX 1000006
#define MOD 1000000007

void init()
{
    file("testcs.inp", "testcs.out");
}

int divs[MAX];
void prep(){
    for(int i = 1; i <= MAX; ++i)
        for(int j = i; j < MAX; j += i)
            divs[j]++;
}

void solve(){
    int n; cin >> n;
    cout << divs[n] << '\n';
}

int32_t main(void)
{
    FASTIO;
#ifndef ONLINE_JUDGE
    init();
#endif
    prep();
    int q = 1;
    cin >> q;
    while (q--)
        solve();
}