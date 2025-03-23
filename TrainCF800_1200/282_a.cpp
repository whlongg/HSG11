//TrainCF800_1200/282_a.cpp
//https://codeforces.com/problemset/problem/282/A
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
    int x = 0; 
    while (n--){
        string s; cin >> s;
        if(s[0]=='-' || s[2]=='-')   x--;
        else if(s[0]=='+' || s[2]=='+')  x++;
    }
    cout << x;
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