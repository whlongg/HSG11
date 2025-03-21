//DTQGSPRING/ContestDP/a4.cpp
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

void solve() {
    int n; 
    cin >> n;
    vector<int> a(n), dp(n, 1), trace(n, -1);
    for (int i = 0; i < n; i++) cin >> a[i];
    int max_len = 1, last_idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                trace[i] = j;
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            last_idx = i;
        }
    }
    vector<int> lis;
    while (last_idx != -1) {
        lis.push_back(a[last_idx]);
        last_idx = trace[last_idx];
    }
    reverse(lis.begin(), lis.end());
    cout << max_len << "\n";
    for (int x : lis) cout << x << " ";
}

int32_t main(void){
    FASTIO;
    //init();
    int q = 1;
    //cin >> q;
    while(q--)
        solve();
}