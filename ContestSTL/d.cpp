#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define FOR(i,a,b) for(int i =(a); i <= (b); ++i)
#define FOD(i,a,b) for(int i =(a); i >= (b); --i)
#define REP(i,n) for(int i=1; i <= n; ++i)
#define N 1e7
//#define file(inp, out) freopen((inp), 'r', stdin);freopen((out), 'w', stdout)
//#define int long long

int32_t main(){
    map <int, int> mp;
    int n, k; cin >> n;
    for(int i=1; i<=n; ++i){
        cin >> k;
        mp[k]++;
    }
    cout << mp.size();
}