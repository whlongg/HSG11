#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define INF 1e9
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define ll long long
#define pii pair<int,int>
const int N = 1e7;

void init(){
    freopen("DOCSACH.INP", "r", stdin);
    freopen("DOCSACH.OUT", "w", stdout);
}

void solve(){
    int n, sum_a=0; cin >> n;
    int a[n+1];
    FOR(i,1,n){
        cin >> a[i];
        sum_a += a[i];
    }
    int i = 1, j = n, lans = 0, rans = 0;
    sort(a+1, a+n+1);
    while(i <= j){
        if(lans==rans){
            lans+=a[i];
            rans+=a[j];
            i++; j--;
        }
        else if(lans < rans){
            lans +=a[i];
            ++i;
        }
        else{
            rans+=a[i];
            ++j;
        }
    }
    int ans = sum_a + abs(rans-lans);
    cout << ans;
}

int32_t main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    //init();
    int n=1;
    //cin >> n;
    while(n--)
        solve();
}
