#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ll n; cin >> n;
    int cnt = 0, l = -1, r = -1;
    for(int i = 0; i < 64; ++i){
        if((n >> i) & 1){
            cnt++;
            if(r==-1)
                r=i;
            l = i;
        }
    }
    cout << cnt << ' ' << l << ' ' << r;
}