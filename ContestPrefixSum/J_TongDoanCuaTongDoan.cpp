#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x : a) cin >> x;
    
    // Tính prefix sum của mảng a
    vector<ll> pref(n+1, 0);
    for(int i = 0; i < n; i++)
        pref[i+1] = pref[i] + a[i];

    vector<ll> b;
    b.reserve(n*(n+1)/2);
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++)
            b.push_back(pref[j+1] - pref[i]);
    vector<ll> b_pref(b.size() + 1, 0);
    for(int i = 0; i < b.size(); i++)
        b_pref[i+1] = b_pref[i] + b[i];
    
    int q;
    cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << b_pref[r] - b_pref[l-1] << '\n';
    }
    return 0;
}

// **Bài toán: Tổng đoạn của tổng đoạn**

// **Thời gian chạy:** 1 giây
// **Giới hạn bộ nhớ:** 256 megabytes

// Cho một mảng `a` gồm `n` phần tử. Gọi `s(l, r)` là tổng của các phần tử từ `a` tại chỉ số `l` đến `a` tại chỉ số `r` (giả sử mảng `a` được đánh chỉ số bắt đầu từ 1).

// Tạo một mảng `b` gồm `n(n+1)/2` phần tử, trong đó mỗi phần tử là tổng của một đoạn con của `a`. Mảng `b` được xây dựng theo thứ tự sau:

// `b = [s(1,1), s(1,2), ..., s(1,n), s(2,2), s(2,3), ..., s(2,n), s(3,3), ..., s(n,n)]`

// Ví dụ, nếu `a = [1, 2, 5, 10]`, thì `b = [1, 3, 8, 18, 2, 7, 17, 5, 15, 10]`.

// Bạn được cho `q` truy vấn. Mỗi truy vấn thứ `i` bao gồm hai số nguyên `l_i` và `r_i`. Với mỗi truy vấn này, bạn cần tính tổng các phần tử của mảng `b` từ chỉ số `l_i` đến chỉ số `r_i` (tính cả hai đầu).

// **Input:**

// - Dòng đầu tiên chứa một số nguyên dương `n` (`1 <= n <= 3 * 10^5`).
// - Dòng thứ hai chứa `n` số nguyên dương `a_1, a_2, ..., a_n` (`1 <= a_i <= 10^9`).
// - Dòng thứ ba chứa một số nguyên dương `q` (`1 <= q <= 3 * 10^5`).
// - `q` dòng tiếp theo, dòng thứ `i` chứa hai số nguyên dương `l_i` và `r_i` (`1 <= l_i <= r_i <= n(n+1)/2`).

// **Subtask:**

// - **Subtask 1 (30%):** `n <= 1000`, `q <= 3 * 10^5`.
// - **Subtask 2 (30%):** `n <= 3 * 10^5`, `q = 1`.
// - **Subtask 3 (40%):** `n <= 3 * 10^5`, `q <= 3 * 10^5`.