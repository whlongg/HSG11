# 🚀 Phân tích thuật toán giải bài "Đỉnh núi"

## 📌 Ý tưởng chính

Bài toán yêu cầu kiểm tra xem một đoạn con từ l đến r có phải là "đỉnh núi" không. Một dãy được gọi là đỉnh núi khi nó có dạng:
b₁ ≤ b₂ ≤ ... ≤ bᵢ ≥ bᵢ₊₁ ≥ ... ≥ bₙ

Tức là dãy tăng dần đến một điểm nào đó, sau đó giảm dần.

## ✨ Thuật toán

Thuật toán được chia làm 3 phần chính:

### 1️⃣ Tiền xử lý mảng tăng/giảm

- Mảng `inc[i]`: lưu vị trí xa nhất về bên trái mà dãy vẫn tăng dần từ vị trí đó đến i
  - Nếu a[i] ≥ a[i-1], thì inc[i] = inc[i-1]
  - Ngược lại, inc[i] = i (bắt đầu tăng từ vị trí i)

- Mảng `dec[i]`: lưu vị trí xa nhất về bên phải mà dãy vẫn giảm dần từ vị trí i đến đó
  - Nếu a[i] ≥ a[i+1], thì dec[i] = dec[i+1]
  - Ngược lại, dec[i] = i (kết thúc giảm tại vị trí i)

### 2️⃣ Tiền xử lý Sparse Table để tìm max

Sparse Table là cấu trúc dữ liệu cho phép tìm phần tử lớn nhất trong đoạn [l,r] với độ phức tạp O(1). Cách xây dựng:

- st[i][j] lưu vị trí phần tử lớn nhất trong đoạn [i, i + 2^j - 1]
- Với j = 0, st[i][0] = i (đoạn chỉ có 1 phần tử)
- Với j > 0, st[i][j] = vị trí phần tử lớn nhất giữa st[i][j-1] và st[i + 2^(j-1)][j-1]

### 3️⃣ Xử lý truy vấn

Với mỗi truy vấn [l,r]:
1. Nếu l = r, đáp án luôn là "Yes" (đoạn 1 phần tử luôn là đỉnh núi)
2. Tìm vị trí phần tử lớn nhất (max_pos) trong đoạn [l,r] bằng Sparse Table
3. Kiểm tra:
   - Nếu inc[max_pos] ≤ l: đoạn từ l đến max_pos tăng dần
   - Nếu dec[max_pos] ≥ r: đoạn từ max_pos đến r giảm dần
4. Nếu cả hai điều kiện đều thỏa mãn, đoạn [l,r] là đỉnh núi

## 🔍 Phân tích độ phức tạp

- Tiền xử lý mảng inc, dec: O(n)
- Tiền xử lý Sparse Table: O(n log n)
- Xử lý mỗi truy vấn: O(1)
- Tổng độ phức tạp: O(n log n + q)

## 🌟 Ví dụ minh họa

Giả sử có dãy a = [1, 2, 3, 5, 2, 1]

1. Mảng inc = [1, 1, 1, 1, 5, 6]
   - inc[1] = 1 (bắt đầu tăng từ vị trí 1)
   - inc[2] = 1 (bắt đầu tăng từ vị trí 1)
   - inc[3] = 1 (bắt đầu tăng từ vị trí 1)
   - inc[4] = 1 (bắt đầu tăng từ vị trí 1)
   - inc[5] = 5 (a[5] < a[4], nên bắt đầu tăng từ vị trí 5)
   - inc[6] = 6 (a[6] < a[5], nên bắt đầu tăng từ vị trí 6)

2. Mảng dec = [4, 4, 4, 4, 6, 6]
   - dec[6] = 6 (kết thúc giảm tại vị trí 6)
   - dec[5] = 6 (kết thúc giảm tại vị trí 6)
   - dec[4] = 4 (kết thúc giảm tại vị trí 4)
   - dec[3] = 4 (kết thúc giảm tại vị trí 4)
   - dec[2] = 4 (kết thúc giảm tại vị trí 4)
   - dec[1] = 4 (kết thúc giảm tại vị trí 4)

3. Truy vấn [1, 6]:
   - max_pos = 4 (a[4] = 5 là lớn nhất)
   - inc[4] = 1 ≤ 1 ✓
   - dec[4] = 4 < 6 ✗
   - Đáp án: "No" (không phải đỉnh núi)

4. Truy vấn [1, 4]:
   - max_pos = 4 (a[4] = 5 là lớn nhất)
   - inc[4] = 1 ≤ 1 ✓
   - dec[4] = 4 ≥ 4 ✓
   - Đáp án: "Yes" (là đỉnh núi)

Thuật toán này rất hiệu quả vì chỉ cần O(1) để kiểm tra mỗi truy vấn sau khi đã tiền xử lý.