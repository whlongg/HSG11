// DTQGSummer/PrefixSum/D_TuoiCay2.cpp


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

int arr[1004][1004], prefix[1004][1004];

void solve(int x, int y, int u, int v, int c){
    arr[x][y] += c;
    arr[x][v+1] -=c;
    arr[u+1][y] -=c;
    arr[u+1][v+1] +=c; 
}

int32_t main(void){
    FASTIO;
    #ifndef ONLINE_JUDGE
        init();
    #endif
    int n, m; cin >> n >> m;
    int q = 1;
    cin >> q;
    while(q--){
        int x, y,u,v,c;
        cin >> x >> y >> u >> v >> c;
        solve(x,y,u,v,c);
    }
    FOR(i,1,n)
        FOR(j,1,m)
            prefix[i][j] = arr[i][j] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];

    FOR(i,1,n){
        FOR(j,1,m){
            cout << prefix[i][j] << ' ';
        }
        cout << '\n';
    }
}