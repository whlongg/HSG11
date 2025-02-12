# 🔎 Kỹ Thuật Tìm Kiếm Nhị Phân (Binary Search) 🚀

## 1. 👋 Giới Thiệu

Tìm kiếm nhị phân (Binary Search) là một thuật toán tìm kiếm **hiệu quả** 💪 được sử dụng để **tìm kiếm một giá trị mục tiêu** 🎯 trong một tập hợp dữ liệu **đã được sắp xếp** 📚. Thay vì tìm kiếm tuần tự, tìm kiếm nhị phân **liên tục chia đôi không gian tìm kiếm** ✂️, giúp giảm đáng kể thời gian tìm kiếm ⏱️.

### 1.1. 💡 Ý Tưởng Cơ Bản

1.  **🔍 Kiểm tra phần tử ở giữa khoảng tìm kiếm.**
2.  **✅ Nếu phần tử giữa là giá trị mục tiêu:** Tìm kiếm **thành công**! 🎉
3.  **⬆️ Nếu phần tử giữa lớn hơn giá trị mục tiêu:** **Thu hẹp** không gian tìm kiếm xuống **nửa bên trái**. ⬅️
4.  **⬇️ Nếu phần tử giữa nhỏ hơn giá trị mục tiêu:** **Thu hẹp** không gian tìm kiếm xuống **nửa bên phải**. ➡️
5.  **🔄 Lặp lại các bước 1-4** cho đến khi tìm thấy giá trị mục tiêu hoặc không gian tìm kiếm rỗng.

### 1.2. 📌 Ví Dụ Minh Họa: Bài Toán "Cây Thứ K"

Bạn có một khu vườn với nhiều cây được trồng thẳng hàng. Bạn cần đặt một máy tưới tự động sao cho:

*   Máy tưới bắt đầu tưới từ cây gần nó nhất, tiếp tục tưới cây gần thứ hai, thứ ba, ..., cho đến khi tưới đủ **k cây**.
*   Công suất máy tưới được đo bằng **khoảng cách từ vị trí đặt máy đến cây xa nhất trong số k cây đã tưới**.
*   **Nhiệm vụ:** Xác định công suất *tối thiểu* cần thiết để tưới đủ k cây. (Đã chỉnh sửa yêu cầu bài toán cho rõ ràng hơn)

_(Bài toán tham khảo từ anh YugiHacker.)_

## 2. 🤔 Khi Nào Sử Dụng Tìm Kiếm Nhị Phân?

Tìm kiếm nhị phân không phải lúc nào cũng "vạn năng".  Cần đáp ứng các **điều kiện tiên quyết** sau:

### 2.1. 🗂️ Không Gian Tìm Kiếm Có Thứ Tự

Dữ liệu cần tìm kiếm phải được **sắp xếp** (tăng dần hoặc giảm dần). Hoặc, không gian các giá trị mà bạn đang tìm kiếm phải có **tính chất đơn điệu**.

### 2.2. 📈 Tính Đơn Điệu

Phải tồn tại một **tính chất đơn điệu** liên quan đến điều kiện kiểm tra và không gian tìm kiếm:

*   **⬆️ Tăng đơn điệu:** Nếu một giá trị `x` thỏa mãn điều kiện, thì mọi giá trị `y` **lớn hơn hoặc bằng** `x` cũng phải thỏa mãn điều kiện. (Ví dụ: bài "Cây thứ k")
*   **⬇️ Giảm đơn điệu:** Nếu một giá trị `x` thỏa mãn điều kiện, thì mọi giá trị `y` **nhỏ hơn hoặc bằng** `x` cũng phải thỏa mãn điều kiện.

### 2.3. ✅ Hàm Kiểm Tra Hiệu Quả

Cần có một hàm `check(value)` có thể **kiểm tra nhanh chóng** ⚡ (thường là O(log N) hoặc tốt hơn) xem một giá trị `value` có thỏa mãn điều kiện hay không.

## 3. 🚀 Các Ứng Dụng Phổ Biến

Tìm kiếm nhị phân có **rất nhiều ứng dụng** 🌍 trong lập trình thi đấu và thực tế:

### 3.1. 🔍 Tìm Kiếm Giá Trị Trong Mảng Đã Sắp Xếp

Đây là ứng dụng **cơ bản nhất** 🦴. Các ngôn ngữ lập trình thường cung cấp các hàm thư viện (ví dụ: `binary_search`, `lower_bound`, `upper_bound` trong C++, `bisect` trong Python).

**💻 Ví dụ:** Kiểm tra xem số `x` có tồn tại trong mảng `a` đã sắp xếp hay không.

### 3.2. 🎯 Bài Toán Tối Ưu Hóa (Ví Dụ "Cây Thứ K")

Tìm **giá trị tối ưu** (ví dụ: công suất tối thiểu, chi phí nhỏ nhất) thỏa mãn một điều kiện, nếu có tính đơn điệu.

**💻 Ví dụ:** (Bài toán "Cây thứ k")

### 3.3. 📐 Tìm Kiếm Cận Trên/Cận Dưới

Tìm căn bậc hai, căn bậc n, hoặc cận trên/cận dưới của một giá trị thỏa mãn bất phương trình/phương trình.

**💻 Ví dụ:** Tìm căn bậc hai của một số dương `x`. Tìm kiếm nhị phân trong khoảng [0, max(1, x)] giá trị `mid` sao cho `mid * mid` xấp xỉ `x`.

### 3.4. 🧩 Tìm Kiếm Trong Không Gian Nghiệm Rời Rạc

Áp dụng khi không gian nghiệm là các giá trị rời rạc và có tính đơn điệu.

**💻 Ví dụ:** Phân bổ `M` máy chủ cho `N` dịch vụ (xem chi tiết trong bản nháp của bạn - ví dụ rất tốt).

### 3.5. 🌳 Tìm Kiếm Trên Đồ Thị/Cây (Trường Hợp Đặc Biệt)

*   **🛣️ Tìm đường đi ngắn nhất có trọng số cạnh thỏa mãn điều kiện:** Tìm kiếm nhị phân trên giá trị trọng số.
*   **🌲 Tìm kiếm trên cây nhị phân tìm kiếm (BST):** BST được xây dựng dựa trên ý tưởng của tìm kiếm nhị phân.

## 4. 🔑 Mẹo và Lưu Ý

### 4.1. 📏 Chọn Khoảng Tìm Kiếm Ban Đầu `[l, r]`

*   Đảm bảo khoảng tìm kiếm **đủ lớn** để chứa nghiệm. 🎯
*   Tránh chọn khoảng tìm kiếm **quá lớn** không cần thiết. 🐌
*   Xác định rõ `l` và `r` có thể là giá trị nghiệm hay không.

### 4.2. ⚙️ Thiết Kế Hàm `check(value)`

*   Hàm `check` là **trái tim** ❤️. Đảm bảo nó **chính xác** và **hiệu quả** ⚡.
*   Chú ý đến **tính đơn điệu** 📈⬇️.

### 4.3. 🚧 Xử Lý Trường Hợp Biên

*   Đảm bảo vòng lặp có **điểm dừng** 🛑.
*   Xử lý trường hợp **không tìm thấy nghiệm** ❌ (nếu có thể).

### 4.4. 🔢 Chú Ý Kiểu Dữ Liệu

*   Sử dụng **kiểu dữ liệu phù hợp** (ví dụ: `long long`) để tránh tràn số. 🧐

## 5. 🎉 Kết Luận

Tìm kiếm nhị phân là một kỹ thuật **mạnh mẽ** 💪 và **linh hoạt** ✨. **Nắm vững** 🧠 nguyên tắc, điều kiện áp dụng và các biến thể là **quan trọng** 🌟. **Luyện tập thường xuyên** 🏋️‍♀️! 😎

## 6. 🔗 Tham Khảo

*   [Binary Search - GeeksforGeeks](https://www.geeksforgeeks.org/binary-search/)
*   [Binary Search - Wikipedia](https://en.wikipedia.org/wiki/Binary_search_algorithm)
*   Bài toán "Cây thứ k" - Tham khảo từ anh YugiHacker.

🚀 **Happy Coding!** 🎯