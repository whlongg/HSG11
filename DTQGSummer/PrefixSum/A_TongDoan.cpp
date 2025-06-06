// DTQGSummer/PrefixSum/A_TongDoan.cpp


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

int arr[MAX];
int prefix[MAX];

void solve(int a, int b){
    cout << prefix[b] - prefix[a-1] <<'\n';
}

int32_t main(void){
    FASTIO;
    #ifndef ONLINE_JUDGE
        init();
    #endif
    int n; cin >> n;
    prefix[0] = 0;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
        prefix[i] = prefix[i-1] + arr[i];
    }
    int q = 1;
    cin >> q;
    while(q--){
        int a, b; cin >> a >> b;
        solve(a, b);
    }
        
}