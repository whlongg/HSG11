// DTQGSummer/PrefixSum/C_TuoiCay.cpp
/*
    author: Nguyen Hoang Long
    oj.vnoi.info/user/nhl08contact
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);
#define FOR(i, a, b) for(int i = (a); i <= (b); ++i)
#define REP(i,b) for(int i = 1; i <= n; ++i)
const int MAX = 1e6 + 5;
#define MOD 1000000007

void init(){
    file("testcs.inp", "testcs.out");
}

int arr[MAX], idx[MAX], prefix[MAX];

void solve(){
    int l, r, x; cin >> l >> r >> x;
    idx[l] = idx[l] + x;
    idx[r+1] = idx[r+1] - x;
}

int32_t main(void){
    FASTIO;
    #ifndef ONLINE_JUDGE
        init();
    #endif

    int n; cin >> n;
    FOR(i,1,n)  cin >> arr[i];
    int q = 1;
    cin >> q;
    while(q--)
        solve();
    arr[0] = 0;
    FOR(i,1,n)
        prefix[i] = prefix[i-1] + idx[i];
    FOR(i,1,n)
        cout << arr[i]+prefix[i] << ' ';
}