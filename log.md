### A. A mu b
> yêu cầu tính giá trị của a^b (mod 10^9 + 7)

- a & b == 10^9 -> TLE (nếu dùng for để nhân a với chính nó b lần -> O(b) -> TLE)
- Giải pháp: Dùng lũy thừa nhị phân (lũy thừa bằng cách bình phương)
- Nếu b là số chẵn -> (b = 2k) -> a^b = a^(2k) = (a^k)^2
- Nếu b là số lẻ (b = 2k +1): a^b = a^(2k+1) = (a^k)^2 * a
```cpp
def recur(ll a, ll b):
    if(b == 0)  return 1;
    ll res = (res*res) % MOD;
    if(b %2 == 1)   res = (res*a) % MOD;
```
-> dpt O(logb)

### B. Tam phân
> yêu cầu sinh tất cả xâu có độ dài n chỉ chứa kí tự "0", "1", "2". Các xâu này phải được in ra theo thứ tự từ điển

- Đệ quy quay lui (backtracking)
    - Xây dựng xâu kết quả, s, từng kí tự một, từ trái sang phải.
        1. Bắt đầu với một xâu rỗng `s =""`
        2. Tại mỗi bước, ta thử thêm lần lượt các kí tự "0", "1", "2" vào cuối xâu `s`.
        3. Sau khi thêm 1 kí tự, ta gọi đệ quy để tiếp tục xây dựng phần còn lại của xâu.
        4. Khi xâu s đạt đủ dộ dài n, ta có 1 xâu hoàn chỉnh. In xâu này -> quay lui về để thử các khả năng khác.
    - Việc thử các kí tự theo đúng thứ tự đảm bảo các xâu kết quả được sinh ra theo thứ tự từ điển.
```cpp
def np(int n, string s = ""):
    if((int)s.size == n){
        cout << s << '\n';
        return;
    }
    for(char c = '0'; c <= '2'; ++c)
        np(n, s + c)
```
-> dpt O(n*3^n)

### C. Liệt kê hoán vị.
> Cho số nguyên n, yêu cầu in ra tất cả các hoán vị (các cách sắp xếp) của các số từ 1 đến n.

- Đệ quy quay lui (backtracking)
- Ý tưởng: xây dựng một hoán vị `idx` bằng cách thêm từng số vào.
- Để đảm bảo mỗi số (1->n) chỉ xuất hiện đúng 1 lần trong 1 hoán vị, cần cơ chế để `đánh dấu` các số đã được sử dụng. Đây chính là vai trò của mảng boolean `check`.
    1. Trạng thái đệ quy
        - Hoán vị đang xây dựng dở: `vector<int> idx`
        - Những số nào đã được dùng: `vector<bool> check`
    2. Đệ quy: Thử thêm một số vào `idx`
        - Duyệt qua tất cả các số `i` từ 1 đến n.
        - Nếu số `i` này chưa được dùng `(!check[i])`, ta chọn nó:
            1. Đánh dấu là đã dùng: `check[i]=true`.
            2. Thêm nó vào hoán vị: `idx.push_back(i)`.
            3. Gọi đệ quy `backtrack(n)` để tìm số tiếp theo.
            4. Quay lui(quan trọng): Sau khi nhánh đệ quy ở bước 3 chạy xong(đã tìm thấy hết các hoán vị bắt đầu bằng `idx` hiện tại), ta phải nhả số `i` ra để thử các khả năng khác. Ta làm điều này bằng cách đảo ngược bước 1 và bước 2: `idx.pop_back()` và `check[i]=false`
```cpp
def backtrack(int n){
    //base case
    if((int)idx.size() == n){
        for(x : idx) cout << x << "";
        cout << '\n';
        return;
    }
    // recursive
    for(int i = 1; i <= n; ++i)
        if(!check[i]){
            check[i]=true;
            idx.push_back(i);
            backtrack();
            idx.pop_back();
            check[i]=false;
        }
}
```
-> dpt: O(n*n!)

### D. Tổng tập con.
> Cho mảng a n phần tử và 1 số nguyên s. Đếm số lượng tập con `không rỗng` của mảng a có các phần tử `đúng bằng s`
- n <= 20 -> quay lui. Ý tưởng: Ta duyệt qua tất cả 2^n tập con có thể có. Với mỗi phần tử a[i] (từ i = 0 -> n-1), có 2 lựa chọn:
    1. Không chọn phần tử a[i] vào tập con.
    2. Chọn phần tử a[i] vào tập con.
- Viết 1 hàm `backtrack(i, sum)` với ý nghĩa: "đang xet sphần tử thứ i, và tổng của các phần tử đã chọn cho đến hiện tại là sum".

```cpp
def backtrack(int i, int sum){
    //base case:
    if(i == n){
        if(sum == s && !subs.emty())    res++;
        return
    }
    // Recursive
    backtrack(i+1, sum);
    subs.push_back(a[i]);
    backtrack(i + 1, sum + a[i]);
    subs.pop_back();
}
```
-> DPT: n tầng, mỗi tầng tự gọi mình 2 lần -> O(2^n).

### E. Dãy ngoặc
> In ra số lượng các dãy ngoặc đúng có độ dài 2n, sau đó in ra tất cả các dãy đó theo thứ tự từ điển.
- Một dãy đúng thỏa mãn 2 điều kiện sau:
    1. Tổng số ngoặc mở bằng tổng số ngoặc đúng (và bằng n) `'(' = ')'`
    2. Tại bất kỳ vị trí nào trong dãy, khi duyệt từ trái sang phải, số lượng ngoặc mở luôn phải lớn hơn hoặc bằng số lượng ngoặc đóng.
- Ý tưởng: Sử dụng đệ quy quay lui. Xây dựng dãy ngoặc `cur` từng ký tự một, tại mỗi bước ta có 2 lựa chọn: Thêm `'('` hoặc thêm `')'`
- Luật của dãy ngoặc đúng:
    1. Luật thêm `(`: Ta chỉ có thể thêm `(` nếu số lượng ngoặc mở op đã dùng chưa vượt quá n.
    2. `)`: Ta chỉ có thể thêm `)` nếu số lượng ngoặc đóng cl đã dùng ít hơn số lượng ngoặc mở op đã dùng (cl < op). Đây là điều kiện đảm bảo tại mọi thời điểm, số `(` luôn lớn hơn hoặc bằng số `)`.
- Viết 1 hàm đệ quy `backtrack(string cur, int op, int cl)` mang nghĩa: Đang xây dựng dãy `cur` đã dùng `op` ngoặc mở và `cl` ngoặc đóng

```cpp
def backtrack(string cur, int op, int cl){
    if(cur.size()==2*n){
        ans.push_back(cur);
        ++cnt;
        return;
    }
    if(op < n)  backtrack(cur + '(', op+1, cl);
    if(cl < op) backtrack(cur + '(', op, cl+1);
}
```
-> Số lượng dãy ngoặc đúng độ dài 2n được tính bằng số Catalan thứ n Cn = 1/(n+1). -> DPT: O(n * Cn) (vì mỗi dãy có độ dài n và ta phải in nó ra).

### F. Nhân số lớn
> Yêu cầu tính (a*b) (mod MOD).
- Bẫy nằm ở ràng buộc (a,b = 1e18).
- Nếu ta tính `(a*b)%MOD` theo cách ngây thơ phép nhân a * b có thể tạo ra một số lên đến 1e36 -> Tràn số (overflow) ngay cả với kiểu long long.
- *Giải Pháp:* Nhân nhị phân (hoặc nhân Ai Cập), hoạt động trên cùng nguyên lý với lũy thừa nhị phân (bit/bài A).
- *Ý tưởng:* a * b = a cộng với chính nó b lần. Thay vì cộng b lần(TLE), ta sẽ phân tích b thành tổng các lũy thừa của 2. Ví dụ: b = 13 = 8 + 4 + 1. Vậy a * 13 = a * (8 + 4 + 1) = (a * 8) + (a*4) + (a * 1).
- Ta có thể tính các giá trị a * 1, a * 3, a * 4, a * 8,... bằng cách nhân đôi a liên tục, tức là a = (a+a) % MOD. Phép cộng này không bao giờ bị tràn số, vì a < MOD nên a + a < 2 * MOD (vẫn nằm trong phạm vi của long long).
```cpp
ll mulmod(ll a, ll b, ll mod){
    ll ans = 0; 
    a %= mod;
    while(b > 0){
        if(b&1) // Tương đương b % 2 == 1
            // nếu bit là 1, ta cộng 'a' đang là a * 2^k vào kết quả.
            ans = (ans + a) % mod;
        // 2. Nhân đôi 'a' để chuẩn bị cho bit tiếp theo
        // Từ a*2^k thành a*2^(k+1)
        a = (a + a)%mod;
        // 3. DỊch bit của b sang phải (chia 2);
        b >>=1;
    }
    return;
}
```
-> Vòng lặp while chạy đến khi b = 0. DPT O(logb).

### Tháp Hà Nội.
- Để di cuyển n đĩa từ cọc nguồn (from) đến cọc đích (to) sử dụng cọc phụ (aux), ta thực hiện 3 bước.
    1. (Đệ quy) Di chyển n-1 đĩa trên cùng từ cọc `from` sang cọc `aux`(lấy cọc `to` làm phụ).
    2. (Cơ sở) Di chuyển đĩa lớn nhất (đĩa thứ n) từ cọc `from` sang cọc `to`.
    3. (Đệ quy) Di chuyển n-1 đĩa (đang ở cọc `aux`) sang cọc `to` (lấy cọc `from` làm phụ.)

### Các quân hậu.
```cpp
def backtrack(int r){   // đặt quân hậu vào hàng r.
    if(r==8){
        ans++; return;
    }
    for(int c = 0; i < 8; c++){
        if(board[r][c] == '*' || col[c] || d1[r-c+7] || d2[r+c])
            continue;
        col[c] = d1[r-c+7] = d2[r+c] =true;
        backtrack(r+1);
        col[c]=d1[r-c+7] = d2[r+c]= false;
    }
}
```

### I. Tổng cấp số nhân.
- Ý tưởng: S(n) bằng vòng lặp `for` sẽ mất O(n), với n lên đến 10^9 -> TLE.
- Đệ quy O(logN) dựa trên nguyên tắc chia để trị. Dựa trên tính chẵn/lẻ của n;
- Hàm hỗ trợ: Hàm lũy thừa nhị phân(giống hệt bài A) dùng để tính a^n (mod MOD) trong O(logN).
- Trường hợp n chẵn (n = 2k):
    1. S(n) = S(n-1) + a^n
        > Trả về S(n-1) ( đệ quy ) + a^n (lũy thừa nhị phân).
    2. Trường hợp n lẻ (2k+1)
        - Chia tổng S(n) làm 2 nửa:
            - Nửa đầu: S(k)
            - Nửa sau: S(k) * a^(k+1)
            - Kết hợp.

### J. Sudoku.
- Đây là một bài toán đệ quy quay lui (backtracking) điển hình.  
  Ý tưởng là **"Thử - Sai - Quay lui"**.  
  Ta duyệt qua bảng từ trái sang phải, từ trên xuống dưới.

- Khi tìm thấy ô trống đầu tiên `a[r][c] == '.'`, ta dừng lại.

- Ta thử điền lần lượt các số `v` từ `'1'` đến `'9'` vào ô đó.  
  Với mỗi số `v`, ta kiểm tra xem việc điền `v` vào ô `(r, c)` có hợp lệ không  
  (tức là **không vi phạm luật Sudoku**).

- **Nếu hợp lệ:**
  - Ta "đặt cược": `a[r][c] = v`.
  - Gọi đệ quy `rec()` để giải tiếp phần còn lại của bảng.
  - Nếu `rec()` trả về `true` (nghĩa là đã tìm được lời giải), ta cũng `return true`.

- **Nếu không hợp lệ (hoặc `rec()` trả về `false`):**
  - Ta phải "quay lui": `a[r][c] = '.'`.
  - Tiếp tục vòng lặp để thử số `v + 1`.

- Nếu thử hết từ `'1'` đến `'9'` mà không số nào dẫn đến lời giải,  
  ta `return false` để báo cho nhánh đệ quy "cha" biết rằng lựa chọn trước đó là sai.

- **Trường hợp cơ sở:**  
  Nếu hàm `rec()` chạy hết hai vòng `for` mà không tìm thấy ô `'.'` nào,  
  nghĩa là bảng đã được điền đầy. Đây là **lời giải hoàn chỉnh**, ta `return true`.

### Điền chữ L
- Ý tưởng:
    1. Chia: Chia bảng 2^n * 2^n thành 4 bảng con có kích thước 2^(n-1)*2^(n-1)
    2. Trị:
        - Ô trống (x,y) ban đầu chắc chắn phải nằm trong 1 trong 4 bảng con này(gọi là bảng con nóng).
        - 3 bảng con còn lại không có ô trống. Ta không thể giải đệ quy trực tiếp trên 3 bảng con này.
        - Ta đặt 1 hình chữ L (với số cnt) vào ngay tâm của bảng lớn. Hình L này chiếm đúng 1 ô ở góc của mỗi bảng trong 3 bảng con đầy.
        - Kết quả: Có 4 bảng con, mỗi bảng con giờ đều có chính xác 1 ô trống.
    3. Kết hợp: đệ quy 4 lần, một lần cho mỗi bảng con 2^(n-1)*2^(n-1) (với vị trí ô trống mới của chúng).