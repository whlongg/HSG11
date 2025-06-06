// DTQGSummer/PrefixSum/E_DemKiTu.cpp


/*
    author: Nguyen Hoang Long
    oj.vnoi.info/user/nhl08contact
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
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

int prefix[MAX][26];

void solve(){
    char c;
    int l, r; 
    cin >> c >> l >> r;
    int ans = prefix[r][c-'a'] - prefix[l-1][c-'a'];
    cout << ans << '\n'; 
}

int32_t main(void){
    FASTIO;
    #ifndef ONLINE_JUDGE
        init();
    #endif
    int n; cin >> n;
    int q = 1;
    cin >> q;
    string s; cin >> s;
    for(int i = 0; i < s.size(); ++i){
        for(int j = 0; j < 26; ++j)
            prefix[i+1][j] = prefix[i][j];
        prefix[i+1][s[i] - 'a']++;
    }
    while(q--)
        solve();
}