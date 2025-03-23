//TrainCF800_1200/Watermelon.cpp
//https://codeforces.com/problemset/problem/4/A
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);

void init(){
    file("input.txt", "output.txt");
}
void solve(){
        int n; cin >> n;
        if(n==2){
            cout << "NO";
            return;
        }
        cout << ((n%2==0)?"YES":"NO");
}
int32_t main(void){
    FASTIO;
    //init();
    int q = 1;
    //cin >> q;
    while(q--)
        solve();
}