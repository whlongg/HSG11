// DTQGSummer/SoHoc/D_TongSoNguyenTo.cpp


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
#define MAX 1000000009
#define MOD 1000000007

void init(){
    file("testcs.inp", "testcs.out");
}

int primes[10000007];
int n = 10000007;
void sangnguyento(){
    FOR(i,1,n) primes[i]=1;
    primes[0]=primes[1]=0;
    FOR(i,2, sqrt(n)){
        if(primes[i])
            for(int j = i * i; j <= n; j+=i)
                primes[j]=0;
    }
}

void solve(){
    sangnguyento();
    int k;
    ll res=0; cin >> k;
    for(int i = 1; i <= k; ++i)
        if(primes[i])
            res+=i;
    cout << res;
}

int32_t main(void){
    FASTIO;
    #ifndef ONLINE_JUDGE
        init();
    #endif
    int q = 1;
    //cin >> q;
    while(q--)
        solve();
}