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
// Cho bảng n x n chứa các số nguyên.
// Tính tổng lớn nhất của hình vuông con kích thước k * k.
// Ý Tưởng: prefix sum 2D (cộng dồn 4 hướng).
// Gọi a[i][j] là tổng của khối từ 1,1 -> i,j
//  a[i][j] = a[i-1][j] + a[i][j-1] - a[i-1][j-1] + x (x là giá trị ô hiện tại)
// Khi có prefix 2D, tổng (ans) là:
// sum = a[i][j] - a[i-k][j] - a[i][j-k] + a[i-k][j-k]
// Duyệt qua mọi ô i,j làm góc phải-dưới của khối k*k -> chọn max
void solve(){
    int n, k; cin >> n >> k;
    ll ans = -1000000;
    vector<vector<ll>> prefix(n+1, vector<ll>(n+1,0));
    for(int i = 1; i <= n;++i){
        for(int j = 1; j <= n; ++j){
            ll x;
            cin >> x;

            prefix[i][j] = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + x;

            if(i >= k && j >= k){
                ll sumk = prefix[i][j] - prefix[i - k][j] - prefix[i][j - k] + prefix[i - k][j - k];
                ans=max(ans, sumk);
            }
        }
    }
    cout << ans << '\n';
}



int32_t main(void){
    FASTIO;
    // #ifndef ONLINE_JUDGE
    //     init();
    // #endif
    int q = 1;
    //cin >> q;
    while(q--)
        solve();
}