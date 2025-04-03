//DTQGSPRING/ContestDP/A6.cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);

void init(){
    file("testcs.inp", "testcs.out");
}
void solve(){
    //Cho 1 dãy số, tìm tất cả các tổng có thể tạo ra từ dãy số này, in ra theo thứ tự tăng dần.
    int n, max_sum=0; cin >> n;
    int a[n];
    for(int i = 0; i < n; ++i){
        cin >> a[i];
        max_sum+=a[i]; //Tính biên của dp
    }
    vector<bool> dp(max_sum+1, false);
    dp[0]=true;
    //Muốn tạo ra tổng s từ x, thì ta cần biết tổng s-x có tồn tại không.
    // Nói cách khác: Nếu mình muốn tạo ra tổng s bằng cách bắt buộc phải dùng số x này, thì trước đó, mình phải có khả năng tạo ra được tổng s - x.
    // Vậy, câu hỏi: "Tôi có thể tạo ra được tổng s từ x không" khi này trở thành liệu tôi có thể tạo ra tổng s-x trước khi xét số x hay không
    // Nếu mà có thể tạo ra tổng s-x, chắc chắn khi thêm x vào có thể tạo ra tổng s.
    for(int x : a){
        for(int s = max_sum; s >= x; --s){  //lặp ngược tránh lặp số
            if(dp[s-x]) 
                dp[s]= true;
        }
    }
    int cnt=0;
    for(int i = 1; i <= max_sum; ++i)
        if(dp[i])
            ++cnt;
    cout << cnt << '\n';
    for(int i = 1; i <= max_sum; ++i)
        if(dp[i])
            cout << i <<' ';
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