#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    ll a[n], d[n+2], prefix[n+2];
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
        d[i]=0;
    }
    d[n+1]=0;
    int q, l, r, x; cin >> q;
    while(q--){
        cin >> l >> r >> x;
        d[l]+=x;
        d[r+1]-=x;
    }
    prefix[0]=0;
    for(int i = 1; i <= n+1; ++i)
        prefix[i]=prefix[i-1]+d[i];
    for(int i = 1; i <= n; ++i){
        a[i]+=prefix[i];
        cout << a[i] << ' ';
    }
}

