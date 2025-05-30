// DTQGSummer/STL/K_3n-n=2n.cpp
//AC with C++ 20 (GCC 13-64)
//AC with C++ 17 (GCC 7-32)
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);

void init(){
    file("testcs.inp", "testcs.out");
}

void solve(){
    int n; cin >> n;
    vector<ll> a(3*n);
    for(int i = 0; i < 3*n; ++i)
        cin >> a[i];
    
    vector<ll> pref_msum(3*n);
    priority_queue<ll, vector<ll>, greater<ll>> pql;
    ll cursl = 0;

    for(int i = 0; i < 3 *n; ++i){
        cursl += a[i];
        pql.push(a[i]);
        if(pql.size() > n){
            cursl -= pql.top();
            pql.pop();
        }
        if(pql.size()==n)
            pref_msum[i] = cursl;
    }

    vector<ll> suff_msum(3*n);
    priority_queue<ll> pqr;
    ll cursr = 0;

    for(int i = 3*n-1; i >= 0; --i){
        cursr += a[i];
        pqr.push(a[i]);
        if ( pqr.size() > n){
            cursr -= pqr.top();
            pqr.pop();
        }
        if ( pqr.size() == n)
            suff_msum[i] = cursr;
    }

    ll res = LLONG_MIN;

    for(int k = n; k <= 2*n; ++k)
        res = max(res, pref_msum[k-1]-suff_msum[k]);
    cout << res << '\n';
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