//TrainCF800_1200/Way_Too_Long_Words.cpp
//https://codeforces.com/problemset/problem/71/A
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
    string s; cin >> s;
    if(s.size()<=10)
        cout << s;
    else
        cout << s[0] << s.size()-2 << s[s.size()-1];
    cout << '\n';
}
int32_t main(void){
    FASTIO;
    //init();
    int q = 1;
    cin >> q;
    while(q--)
        solve();
}