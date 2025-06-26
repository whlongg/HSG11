// DTQGSummer/Bitwise/E_OR&OR.cpp


/*
    author: Nguyen Hoang Long
    oj.vnoi.info/user/nhl08contact
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);
#define FOR(i, a, b) for(int i = (a); i <= (b); ++i)
#define REP(i,b) for(int i = 1; i <= n; ++i)
const int MAX = 1e6 + 5;
#define MOD 1000000007

#include <bits/stdc++.h>
using namespace std;
#define ll long long

bool check(ll target, int n, int k, const vector<int> &a)
{
    int cnt = 0;
    ll cor = 0;
    for (int i = 0; i < n; ++i)
    {
        cor |= a[i];
        if ((cor & target) == target)
        {
            cnt++;
            cor = 0;
        }
    }
    return cnt >= k;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    ll ans = 0;
    for (int bit = 60; bit >= 0; --bit)
    {
        ll target = ans | (1LL << bit);
        if (check(target, n, k, a))
            ans |= (1LL << bit);
    }
    cout << ans;
    return 0;
}