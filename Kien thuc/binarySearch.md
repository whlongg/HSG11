# 🔎 Kỹ Thuật Tìm Kiếm Nhị Phân (Binary Search) 🚀

## 1. 👋 Giới thiệu về Tìm kiếm nhị phân

Tìm kiếm nhị phân (Binary Search) là một thuật toán tìm kiếm **hiệu quả** 💪 được sử dụng để **tìm kiếm một giá trị mục tiêu** 🎯 trong một tập hợp dữ liệu **đã được sắp xếp** 📚. Thay vì tìm kiếm tuần tự từng phần tử (ví dụ: tìm kiếm tuyến tính), tìm kiếm nhị phân **liên tục chia đôi không gian tìm kiếm** ✂️, giúp giảm đáng kể thời gian tìm kiếm ⏱️.

**💡 Ý tưởng cơ bản:**

1. **🔍 Kiểm tra phần tử ở giữa khoảng tìm kiếm.**
2. **✅ Nếu phần tử giữa là giá trị mục tiêu:**  Tìm kiếm **thành công**! 🎉
3. **⬆️ Nếu phần tử giữa lớn hơn giá trị mục tiêu:**  **Thu hẹp** không gian tìm kiếm xuống **nửa bên trái**. ⬅️
4. **⬇️ Nếu phần tử giữa nhỏ hơn giá trị mục tiêu:** **Thu hẹp** không gian tìm kiếm xuống **nửa bên phải**. ➡️
5. **🔄 Lặp lại các bước 1-4** cho đến khi tìm thấy giá trị mục tiêu hoặc không gian tìm kiếm trở nên rỗng.

**📝 Trong bài này mình sẽ sử dụng bài toán cây thứ k để minh họa:**

- Bạn hãy tưởng tượng bạn có một khu vườn với những hàng cây trồng thẳng tắp. Mỗi cây có một vị trí xác định trên đường thẳng đó. Bạn muốn lắp đặt một chiếc máy tưới cây tự động.

- Với mỗi lần bạn muốn dùng máy tưới, bạn sẽ:

- 1.  **Đặt máy tưới tại một vị trí** nào đó trên đường thẳng.
- 2.  **Chọn số lượng cây (k)** mà bạn muốn máy tưới sẽ tưới.

- Máy tưới này hoạt động rất đặc biệt: nó sẽ **tưới lần lượt cho những cây gần nó nhất**. Đầu tiên, nó tưới cây gần nó nhất, sau đó tưới cây gần thứ nhì, rồi cây gần thứ ba, và cứ thế, cho đến khi tưới đủ **k cây**.

- Điều bạn cần tính là **"công suất" của máy tưới**. Công suất này được đo bằng **khoảng cách từ vị trí đặt máy tưới đến cây xa nhất** trong số **k cây** mà máy tưới đã tưới.

- **Nhiệm vụ của bạn:** Với mỗi phương án đặt máy tưới (vị trí máy và số lượng cây k), hãy **tính toán và cho biết công suất cần dùng** của máy tưới đó.
- Note: Bài toán này mình tham khảo của anh YugiHacker.

## 2. 🤔 Khi nào sử dụng Tìm kiếm nhị phân? 📌

Tìm kiếm nhị phân không phải lúc nào cũng "vạn năng". Để sử dụng hiệu quả kỹ thuật này, cần đáp ứng các **điều kiện tiên quyết** sau:

* **2.1. 🗂️ Không gian tìm kiếm có thứ tự (Ordered Search Space):**  Dữ liệu cần tìm kiếm phải được **sắp xếp** theo một thứ tự nhất định (tăng dần hoặc giảm dần). Hoặc, không gian các giá trị mà bạn đang tìm kiếm phải có **tính chất đơn điệu**.

* **2.2. 📈 Tính đơn điệu (Monotonicity):** Phải tồn tại một **tính chất đơn điệu** liên quan đến điều kiện kiểm tra và không gian tìm kiếm. Điều này có nghĩa là:
    * **⬆️ Tăng đơn điệu:** Nếu một giá trị `x` thỏa mãn điều kiện, thì mọi giá trị `y` **lớn hơn hoặc bằng** `x` cũng phải thỏa mãn điều kiện. (Ví dụ: bài "Cây thứ k" - nếu công suất `X` đủ, thì `Y > X` cũng đủ).
    * **⬇️ Giảm đơn điệu:** Nếu một giá trị `x` thỏa mãn điều kiện, thì mọi giá trị `y` **nhỏ hơn hoặc bằng** `x` cũng phải thỏa mãn điều kiện. (Ví dụ: tìm giá trị lớn nhất không vượt quá giới hạn).

* **2.3. ✅ Hàm kiểm tra hiệu quả (Efficient Check Function):** Cần có một hàm `check(value)` có thể **kiểm tra nhanh chóng** ⚡ (thường là O(log N) hoặc tốt hơn) xem một giá trị `value` có thỏa mãn điều kiện hay không. Độ phức tạp của hàm `check` sẽ ảnh hưởng đến hiệu quả tổng thể của tìm kiếm nhị phân.

## 3. 🚀 Các ứng dụng phổ biến của Tìm kiếm nhị phân 🌟

Tìm kiếm nhị phân có **rất nhiều ứng dụng** 🌍 trong lập trình thi đấu và thực tế. Dưới đây là một số ví dụ phổ biến:

* **3.1. 🔍 Tìm kiếm giá trị trong mảng đã sắp xếp (Ví dụ cơ bản):**

    Đây là ứng dụng **cơ bản nhất** 🦴 của tìm kiếm nhị phân. Tìm kiếm một phần tử cụ thể trong một mảng đã được sắp xếp.  Các ngôn ngữ lập trình thường cung cấp các hàm thư viện hỗ trợ tìm kiếm nhị phân (ví dụ: `binary_search`, `lower_bound`, `upper_bound` trong C++, `bisect` trong Python).

    **💻 Ví dụ:** Kiểm tra xem số `x` có tồn tại trong mảng `a` đã sắp xếp hay không.

* **3.2. 🎯 Bài toán tối ưu hóa (Ví dụ "Cây thứ k"):**

    Như chúng ta đã thấy trong bài "Cây thứ k", tìm kiếm nhị phân có thể được sử dụng để tìm **giá trị tối ưu** (ví dụ: công suất tối thiểu, chi phí nhỏ nhất, thời gian ngắn nhất) thỏa mãn một điều kiện nào đó, nếu có tính đơn điệu.

    **💻 Ví dụ:** Tìm công suất tối thiểu của máy tưới cây để tưới được ít nhất `k` cây gần nhất.

* **3.3. 📐 Tìm kiếm cận trên/cận dưới (Tìm căn bậc hai, căn bậc n, ...):**

    Tìm kiếm nhị phân có thể được dùng để tìm căn bậc hai, căn bậc n của một số, hoặc tìm cận trên/cận dưới của một giá trị thỏa mãn một bất phương trình hoặc phương trình.

    **💻 Ví dụ:** Tìm căn bậc hai của một số dương `x` với độ chính xác nhất định. Ta có thể tìm kiếm nhị phân trong khoảng [0, x] (hoặc [0, max(1, x)]) giá trị `mid` sao cho `mid * mid` xấp xỉ `x`.

* **3.4. 🧩 Tìm kiếm trong không gian nghiệm rời rạc (Bài toán phân bổ tài nguyên):**

    Trong một số bài toán, không gian nghiệm có thể là các giá trị rời rạc (ví dụ: số lượng công việc, số lượng máy móc). Tìm kiếm nhị phân vẫn có thể áp dụng nếu có tính đơn điệu.

    **💻 Ví dụ:** Phân bổ `M` máy chủ cho `N` dịch vụ sao cho tối đa hóa hiệu suất, với điều kiện mỗi dịch vụ cần ít nhất một số lượng máy chủ nhất định. Ta có thể tìm kiếm nhị phân trên số lượng máy chủ tối đa có thể phân bổ cho một dịch vụ, và hàm `check` sẽ kiểm tra xem với số lượng máy chủ đó có đủ để phân bổ cho tất cả các dịch vụ hay không.

* **3.5. 🌳 Tìm kiếm trên đồ thị/cây (Trong một số trường hợp đặc biệt):**

    Mặc dù không phổ biến, nhưng trong một số trường hợp đặc biệt, tìm kiếm nhị phân có thể được áp dụng trên đồ thị hoặc cây, ví dụ như:

    * **🛣️ Tìm đường đi ngắn nhất có trọng số cạnh thỏa mãn một điều kiện:** Có thể tìm kiếm nhị phân trên giá trị trọng số và hàm `check` sẽ kiểm tra xem có tồn tại đường đi với trọng số không vượt quá giá trị đó hay không (ví dụ, sử dụng thuật toán Dijkstra hoặc Bellman-Ford).
    * **🌲 Tìm kiếm trên cây nhị phân tìm kiếm (Binary Search Tree - BST):**  BST được xây dựng dựa trên ý tưởng của tìm kiếm nhị phân.

## 4. 🔑 Mẹo và Lưu ý khi triển khai Tìm kiếm nhị phân 📝

Để triển khai tìm kiếm nhị phân một cách chính xác và hiệu quả, hãy ghi nhớ những **mẹo và lưu ý** sau:

* **4.1. 📏 Chọn khoảng tìm kiếm ban đầu `[l, r]` phù hợp:**
    * Đảm bảo khoảng tìm kiếm **đủ lớn** để chứa nghiệm. 🎯
    * Tránh chọn khoảng tìm kiếm **quá lớn** có thể gây tràn số hoặc làm chậm quá trình tìm kiếm (nếu không cần thiết). 🐌
    * Xác định rõ `l` và `r` có thể là giá trị nghiệm hay không (tùy vào điều kiện bài toán và cách cài đặt vòng lặp `while`). Ví dụ: `while (l < r)` vs `while (l <= r)`.

* **4.2. ⚙️ Thiết kế hàm `check(value)` cẩn thận:**
    * Hàm `check` là **trái tim** ❤️ của tìm kiếm nhị phân. Đảm bảo hàm này **phản ánh chính xác điều kiện cần kiểm tra** trong bài toán.
    * Hàm `check` cần **hiệu quả** ⚡ để không làm chậm quá trình tìm kiếm nhị phân.
    * Chú ý đến **tính đơn điệu** 📈⬇️ khi thiết kế hàm `check`.

* **4.3. 🚧 Xử lý các trường hợp biên (Lặp vô hạn, Không tìm thấy nghiệm):**
    * Đảm bảo vòng lặp tìm kiếm nhị phân có **điểm dừng** 🛑 (điều kiện `l <= r` hoặc `l < r`).
    * Xử lý trường hợp **không tìm thấy nghiệm** ❌ (nếu có thể xảy ra). Trong nhiều bài toán, nghiệm luôn tồn tại trong khoảng tìm kiếm đã xác định.

* **4.4. 🔢 Chú ý đến kiểu dữ liệu (Tránh tràn số):**
    * Sử dụng **kiểu dữ liệu phù hợp** (ví dụ: `long long` cho các giá trị lớn) để tránh tràn số trong các phép tính trung gian (ví dụ: `mid = (l + r) / 2`, `x + len`, `x - len`, ...). 🧐

## 5. 🎉 Kết luận

Tìm kiếm nhị phân là một **kỹ thuật thuật toán cực kỳ mạnh mẽ** 💪 và **linh hoạt** ✨, với độ phức tạp thời gian logarit làm cho nó trở nên **vô giá** 💎 cho việc giải quyết các bài toán hiệu quả, đặc biệt trong lập trình thi đấu. Việc **nắm vững** 🧠 nguyên tắc, điều kiện áp dụng và các biến thể của tìm kiếm nhị phân là một bước **quan trọng** 🌟 trên con đường trở thành một lập trình viên giỏi. Hãy **luyện tập thường xuyên** 🏋️‍♀️ với các bài tập khác nhau để thành thạo kỹ thuật này và áp dụng nó một cách tự tin trong các bài toán thực tế! 😎

---

📚 Chúc bạn học tập hiệu quả và chinh phục thành công kỹ thuật tìm kiếm nhị phân! 🤝 Nếu bạn có bất kỳ câu hỏi nào khác, đừng ngần ngại hỏi nhé! 😊💻🚀