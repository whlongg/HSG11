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
// Đếm số cách chia dãy thành 3 đoạn liên tiếp có tổng bằng nhau
// sum(1->i) = sum(i+1 -> j) = sum(j + 1 -> n)
// Điều kiện tồn tại:
// Tổng toàn dãy S(gọi S là sum a[1] -> a[n]) không chia hết cho 3 => ans =0, Tại vì không thể chia đều thành 3 phần
// Nếu chia hết: Mỗi phần có tổng S/3
// => Tổng 2 phần đầu (1->j) = 2S/3 
// Đặt prefix[i] = a[0] + ... + a[i] (0-index)
// Duyệt i = điểm kết thúc đoạn đầu.
// Nếu prefix[i] == S/3 thì ta sẽ cần đếm số vị trí j > i+1 sao cho prefix[j] == 2S/3

// Đếm hiệu quả bằng suffix cnt.
// Duyệt ngược từ cuối về:
// cnt[i] = 1 nếu prefix[n-1] - prefix[i-1] == S/3 <=> sum(i -> n-1) == S/3
// Kiểm tra đơn giản hơn bằng cách cộng dần từ phải qua trái: 
//          ss+= a[i]; if(ss == S/3)    cnt[i]=1;
// Cộng dồn cnt[i] += cnt[i+1] -> cnt[i]= số vị trí j >= i có tổng suffix = S/3
// Duyệt từ trái qua -> Khi prefix sum 1->i == S/3 => Cộng cnt[i+2] (vì đoạn giữa cần >= 1 phần từ)


int a[1000006];
ll cnt[1000006];

void solve(){
    int n; cin >> n;
    ll s = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        s+=a[i];
    }  
    if( s % 3 != 0){
        cout << "0";
        return;
    }

    s/=3;

    ll ss = 0;
    for(int i = n -1; i >= 0; --i){
        ss+=a[i];
        if(ss==s)
            cnt[i] = 1;
    }

    // cộng dồn để cnt[i] = số vị trí j >= i có tổng suffix = S/3
    for(int i = n - 2; i >= 0; --i)
        cnt[i] += cnt[i+1];
    ll ans = 0; ss = 0;

    for(int i = 0; i+2 < n; ++i){
        ss+= a[i];
        if(ss == s)
            ans+= cnt[i+2];
    }
    cout << ans << '\n';
    return;
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