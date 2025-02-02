## A. Milya và hai dãy số

**Giới hạn thời gian mỗi bài kiểm tra:** 1 giây

**Giới hạn bộ nhớ mỗi bài kiểm tra:** 256 megabyte

Một dãy số được gọi là tốt nếu với mọi phần tử `x` xuất hiện trong dãy số này, `x` phải xuất hiện ít nhất hai lần trong dãy số. Ví dụ, các dãy số `[1, 2, 1, 1, 2]`, `[3, 3]` và `[1, 2, 4, 1, 2, 4]` là tốt, trong khi các dãy số `[1]`, `[1, 2, 1]` và `[2, 3, 4, 4]` không tốt.

Milya có hai dãy số tốt `a` và `b` có độ dài `n`. Cô ấy có thể sắp xếp lại các phần tử trong dãy `a` theo bất kỳ cách nào. Sau đó, cô ấy thu được một dãy `c` có độ dài `n`, trong đó `c[i] = a[i] + b[i]` (1 ≤ i ≤ n).

Xác định xem Milya có thể sắp xếp lại các phần tử trong dãy `a` sao cho có ít nhất 3 phần tử khác nhau trong dãy `c` hay không.

**Đầu vào**

Mỗi bài kiểm tra bao gồm nhiều trường hợp kiểm tra. Dòng đầu tiên chứa một số nguyên `t` (1 ≤ t ≤ 1000) - số lượng trường hợp kiểm tra. Mô tả của các trường hợp kiểm tra như sau.

Dòng đầu tiên của mỗi trường hợp kiểm tra chứa một số nguyên `n` (3 ≤ n ≤ 50) - độ dài của các dãy `a` và `b`.

Dòng thứ hai của mỗi trường hợp kiểm tra chứa `n` số nguyên `a[1], a[2], ..., a[n]` (1 ≤ a[i] ≤ 10^9) - các phần tử của dãy `a`.

Dòng thứ ba của mỗi trường hợp kiểm tra chứa `n` số nguyên `b[1], b[2], ..., b[n]` (1 ≤ b[i] ≤ 10^9) - các phần tử của dãy `b`.

**Đầu ra**

Đối với mỗi trường hợp kiểm tra, đầu ra "YES" (không có dấu ngoặc kép) nếu có thể thu được ít nhất 3 phần tử khác nhau trong dãy `c` và "NO" nếu ngược lại.

Bạn có thể xuất ra mỗi chữ cái ở bất kỳ trường hợp nào (ví dụ: "YES", "Yes", "yes", "yEs" sẽ được công nhận là câu trả lời tích cực).

**Ví dụ**

**Đầu vào**

```
5
4
1 2 1 2
1 2 1 2
6
1 2 3 3 2 1
1 1 1 1 1 1
3
1 1 1
1 1 1
6
1 52 52 3 1 3
59 4 3 59 3 4
4
100 1 100 1
2 2 2 2
```

**Đầu ra**

```
YES
YES
NO
YES
NO
```
