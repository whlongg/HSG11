// DTQGSummer/Bitwise/D_XOR_2Day.cpp


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


void solve(){
    int n; cin >> n;
    vector<int> a(n), b(n);
    FOR(i, 0, n-1)  cin >> a[i];
    FOR(i, 0, n-1)  cin >> b[i];

    ll res = 0;
    for(int k = 0; k < 22; ++k){
        ll bit_val = (1LL << k);
        ll mod_val = (1LL << (k +1));
        vector<int> b_prime(n);
        FOR(i,0,n-1)    b_prime[i] = b[i] % mod_val;
        sort(b_prime.begin(), b_prime.end());
        ll cntkSet = 0;
        FOR(i,0,n-1){
            ll aim = a[i] % mod_val;
            ll L1 = bit_val - aim;
            ll R1 = mod_val - aim;
            ll L2 = bit_val + mod_val - aim;
            ll R2 = 2 * mod_val - aim;
            auto itl1 = lower_bound(b_prime.begin(), b_prime.end(), L1);
            auto ith1 = lower_bound(b_prime.begin(), b_prime.end(), R1);
            
            cntkSet += (ith1 - itl1);
            auto itl2 = lower_bound(b_prime.begin(), b_prime.end(), L2);
            auto ith2 = lower_bound(b_prime.begin(), b_prime.end(), R2);
            cntkSet += (ith2 - itl2);
        }
        if(cntkSet % 2 == 1){
            res |= bit_val;
        }


    }   
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