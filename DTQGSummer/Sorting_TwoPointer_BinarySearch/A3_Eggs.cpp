// DTQGSummer/Sorting_TwoPointer_BinarySearch/A3_Eggs.cpp
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

void init(){
    file("testcs.inp", "testcs.out");
}

vector<pair<int,int>> a;
bool check(ll time, ll x){
    ll res = 0;
    for(auto [p, t] : a){
        if(time >= p){
            res += (time - p) / t + 1;
        }
        if (res >= x)   return true;
    }
    return res >= x;
}

void solve(){
    ll n, x; cin >> n >> x;
    a.resize(n);
    for(auto &[p, t] : a) cin >> p >> t;
    ll l = 0, r = 1e18;
    while( l < r){
        ll mid = (l + r) / 2;
        if(check(mid, x))  r = mid;
        else l = mid + 1;
    }
    cout << l << '\n';
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