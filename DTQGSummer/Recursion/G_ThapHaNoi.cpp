// DTQGSummer/Recursion/G_ThapHaNoi.cpp
/*
    author: Nguyen Hoang Long
    oj.vnoi.info/nhl08contact
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);
#define FOR(i, a, b) for(int i = (a); i <= (b); ++i)
#define REP(i,b) for(int i = 1; i <= n; ++i)
#define MAX 1000000009
#define MOD 1000000007

void init(){
    file("testcs.inp", "testcs.out");
}

vector<pair<int,int>> moves;

void move(int n, int from, int to, int aux){
    if(n==1){
        moves.push_back({from, to});
        return;
    }
    move(n-1, from, aux, to);
    moves.push_back({from, to});
    move(n-1, aux, to, from);
}

void solve(){
    int n; cin >> n;
    move(n, 1, 3, 2);
    cout << moves.size() << '\n';
    for(auto [x, y] : moves)
        cout << x << ' ' << y << '\n';
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