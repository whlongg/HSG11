// DTQGSPRING/DoThi/H_TruotBang.cpp
/*
    author: Nguyen Hoang Long
    oj.vnoi.info/user/nhl08contact
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

char grid[200][200];

void solve(){
    int n, m;
    cin >>n >> m;
    for(int i = 0; i < n; ++i){
        string s; cin >> s;
        for(int j = 0; j < m; ++j)
            grid[i][j] = s[j];
    }
    queue<pair<int, int>> q;
    vector<vector<bool>> vstop(n, vector<bool>(m, false));
    vector<vector<bool>> touched(n, vector<bool>(m, false));

    int start_r=1, start_c = 1;
    q.push({start_r, start_c});
    vstop[start_r][start_c] = true;
    touched[start_r][start_c] = true;
    int ans = 1;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0,0,-1,1};

    while(!q.empty()){
        pair<int, int> curr = q.front();
        q.pop();
        int x = curr.first;
        int y = curr.second;

        for(int i = 0; i < 4; ++i){
            int currx = x;
            int curry = y;
            int stopx = x;
            int stopy = y;

            while(true){
                int nx = currx + dx[i];
                int ny = curry + dy[i];

                if(grid[nx][ny] == '.'){
                    currx = nx;
                    curry = ny;
                    if(!touched[currx][curry])
                        touched[currx][curry] = true, ans++;
                    stopx = currx;
                    stopy = curry;
                }
                else{
                    if(!vstop[stopx][stopy]){
                        vstop[stopx][stopy] = true;
                        q.push({stopx, stopy});
                    }
                    break;
                }
            }
        }
    }
    cout << ans << '\n';
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