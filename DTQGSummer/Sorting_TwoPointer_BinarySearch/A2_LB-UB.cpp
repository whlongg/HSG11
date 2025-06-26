// DTQGSummer/Sorting_TwoPointer_BinarySearch/A2_LB-UB.cpp
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
//lb min >= x;
//ub min > x;
vector<int> a;
void solve(int n, int t, int x){
    int lb = lower_bound(a.begin(), a.end(), x) - a.begin();
    int ub = upper_bound(a.begin(), a.end(), x) - a.begin();
    if(t == 1){
        cout << (lb < n ? a[lb]:-1) << '\n';
    }
    else if( t == 2){
        cout << (ub < n ? a[ub]:-1) << '\n';
    }
    else if(t == 3){
        cout << ((ub-1 >= 0 && ub-1 < n) ? a[ub-1]:-1) << '\n';
    }
    else if(t == 4){
        int idx = lb -1;
        cout << ((idx >= 0 && idx < n) ? a[idx] : -1) << '\n';
    }
    else{
        cout << ub - lb << '\n';
    }
}

int32_t main(void){
    FASTIO;
    #ifndef ONLINE_JUDGE
        init();
    #endif
    int q = 1, n;
    cin >> n >> q;
    a.resize(n);
    for(int &x : a)
        cin >> x;
    while(q--){
        int t, x; cin >> t >> x;
        solve(n, t, x);
    }
        
}