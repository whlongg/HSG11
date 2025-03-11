**Bài toán: Điểm trong đường tròn** (Problem D in DIV-3)

Những người lính màu hồng đã vẽ `n` đường tròn với tâm nằm trên trục hoành của mặt phẳng. Ngoài ra, họ cho biết rằng *tổng các bán kính* là đúng bằng `m`.

Hãy tìm số lượng điểm nguyên nằm *bên trong hoặc trên biên* của ít nhất một đường tròn. Nói một cách chính thức, bài toán được định nghĩa như sau.

Bạn được cho một dãy số nguyên `x1, x2, ..., xn` và một dãy số nguyên dương `r1, r2, ..., rn`, trong đó biết rằng tổng của các `ri` bằng `m`.

Bạn phải đếm số lượng các cặp số nguyên `(x, y)` thỏa mãn điều kiện sau:

*   Tồn tại một chỉ số `i` sao cho `(x - xi)^2 + y^2 <= ri^2` (1 <= i <= n).

\*Thông tin này có thực sự hữu ích không? Đừng hỏi tôi; tôi thực sự không biết.

**Đầu vào**

Mỗi bài kiểm tra chứa nhiều trường hợp kiểm tra. Dòng đầu tiên chứa số lượng trường hợp kiểm tra `t` (1 <= t <= 10^4). Mô tả của các trường hợp kiểm tra theo sau.

Dòng đầu tiên của mỗi trường hợp kiểm tra chứa hai số nguyên `n` và `m` (1 <= n <= m <= 2 * 10^5).

Dòng thứ hai của mỗi trường hợp kiểm tra chứa `x1, x2, ..., xn` - tâm của các đường tròn (-10^9 <= xi <= 10^9).

Dòng thứ ba của mỗi trường hợp kiểm tra chứa `r1, r2, ..., rn` - bán kính của các đường tròn (1 <= ri, tổng của các ri từ i=1 đến n bằng m).

Đảm bảo rằng tổng của `m` trên tất cả các trường hợp kiểm tra không vượt quá 2 * 10^5.

**Đầu ra**

Với mỗi trường hợp kiểm tra, in ra số lượng điểm nguyên thỏa mãn điều kiện trên một dòng riêng biệt.

**Ví dụ**

**Input**

```
4
2 3
0 0
1 2
2 3
0 2
1 2
3 3
0 2 5
1 1 1
4 8
0 5 10 15
2 2 2 2
```

**Output**

```
13
16
14
52
```

**Lưu ý**

Trong trường hợp kiểm tra đầu tiên, đường tròn với `r1 = 1` nằm hoàn toàn bên trong đường tròn với `r2 = 2`. Do đó, bạn chỉ cần đếm số lượng điểm nguyên bên trong đường tròn sau. Có 13 điểm nguyên thỏa mãn `x^2 + y^2 <= 2^2` nên đáp án là 13.

Trong trường hợp kiểm tra thứ hai, đường tròn với `r1 = 1` không nằm hoàn toàn bên trong đường tròn với `r2 = 2`. Có thêm 3 điểm nằm trong đường tròn thứ nhất nhưng không nằm trong đường tròn thứ hai, nên đáp án là 3 + 13 = 16.

**Giải thích thêm (không có trong đề):**

Bài toán yêu cầu bạn đếm số lượng điểm nguyên (tức là cả `x` và `y` đều là số nguyên) nằm trong *ít nhất một* trong số `n` đường tròn đã cho. Các đường tròn này có tâm nằm trên trục hoành (`y = 0`), và bạn được cung cấp tọa độ `x` của tâm và bán kính của mỗi đường tròn.
