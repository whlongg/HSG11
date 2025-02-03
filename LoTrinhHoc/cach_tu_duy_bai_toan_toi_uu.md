## **🔥 Cách Tư Duy Khi Gặp Bài Toán Tối Ưu**  
(Bài viết này sẽ giải thích theo cách dễ hiểu nhất, như đang dạy một đứa trẻ 5 tuổi 🚀)  

---

### **📌 1. Tham Lam (Greedy) - Luôn Chọn Cái Tốt Nhất Trước**  

🧸 **Hãy tưởng tượng**: Bạn vào tiệm bánh với 100 nghìn đồng. Có rất nhiều loại bánh, mỗi cái có giá khác nhau. Bạn muốn mua nhiều bánh nhất có thể.  

💡 **Cách tham lam giải quyết:**  
- Bạn sẽ luôn chọn cái bánh **rẻ nhất** trước để mua được nhiều nhất.  
- Mỗi lần mua, bạn lại tiếp tục chọn cái rẻ nhất còn lại.  

🔍 **Nhận xét:**  
- Cách này **đơn giản và nhanh**, nhưng đôi khi không phải tối ưu.  
- Nếu tiệm có một combo đặc biệt (mua 3 bánh loại A được tặng 1 bánh), cách chọn từng cái một có thể không phải cách tốt nhất.  

---

### **📌 2. Chia Để Trị (Divide & Conquer) - Chia Nhỏ Rồi Gộp Lại**  

🧩 **Hãy tưởng tượng**: Bạn có một bức tranh ghép hình (puzzle) với 1000 mảnh.  

💡 **Cách chia để trị giải quyết:**  
- Thay vì ghép tất cả cùng lúc (rất khó), bạn **chia nhỏ thành từng phần** nhỏ (ví dụ: ghép từng góc, rồi ghép phần giữa).  
- Khi các phần nhỏ đã xong, bạn **ghép lại** với nhau để hoàn thành bức tranh.  

🔍 **Nhận xét:**  
- Chia để trị rất tốt khi bài toán có thể tách thành nhiều phần nhỏ **độc lập**.  
- Nếu bạn chia tốt, bạn sẽ giải quyết nhanh hơn nhiều so với làm cả bài toán một lúc.  

🚀 **Ứng dụng**:  
- Sắp xếp danh sách dài bằng cách chia nhỏ (Merge Sort, Quick Sort).  
- Tìm kiếm nhanh bằng cách chia đôi (Binary Search).  

---

### **📌 3. Quy Hoạch Động (Dynamic Programming - DP) - Nhớ Lại Để Không Làm Lại**  

🐿 **Hãy tưởng tượng**: Bạn là một con sóc đi kiếm hạt dẻ để dành cho mùa đông.  

💡 **Cách quy hoạch động giải quyết:**  
- Mỗi lần bạn tìm được một chỗ có hạt dẻ, bạn **ghi nhớ vị trí đó**.  
- Khi cần hạt dẻ, bạn không phải đi tìm lại từ đầu mà chỉ cần đến đúng nơi đã nhớ.  

🔍 **Nhận xét:**  
- Quy hoạch động giúp **tránh lặp lại công việc** không cần thiết.  
- Tuy nhiên, bạn phải **tổ chức trí nhớ của mình thật tốt** để không bị rối.  

🚀 **Ứng dụng:**  
- Tìm đường đi ngắn nhất (Floyd-Warshall, Bellman-Ford).  
- Tìm số cách leo cầu thang (Fibonacci bằng DP).  

---

## **🎯 Ví dụ bài toán thực hành: Balo 0/1**  

🛍 **Câu chuyện:**  
Bạn có một cái **balo** với sức chứa **10 kg**. Có 3 món đồ bạn có thể mang theo:  
1. 📚 **Sách** - Nặng **3 kg**, giá trị **30 điểm**.  
2. 💻 **Laptop** - Nặng **5 kg**, giá trị **50 điểm**.  
3. 🧸 **Gấu bông** - Nặng **4 kg**, giá trị **40 điểm**.  

Nhiệm vụ của bạn là chọn đồ sao cho tổng giá trị cao nhất mà không vượt quá **10 kg**.  

---

### **1️⃣ Giải bằng tham lam - Chọn cái lớn nhất trước**  
**Chiến thuật:**  
- Chọn món có giá trị cao nhất trước (Laptop - 50 điểm).  
- Còn 5 kg trống → chọn món tiếp theo tốt nhất là Gấu bông (40 điểm).  
- Tổng: **Laptop + Gấu bông = 90 điểm**.  

**Nhưng nếu chọn Sách + Gấu bông (70 điểm) trước, sau đó vẫn có thể chọn Laptop (50 điểm) → tổng là 100 điểm, cao hơn.**  
⏩ **Tham lam không đúng trong bài này!**  

---

### **2️⃣ Giải bằng chia để trị - Thử tất cả cách kết hợp**  
**Chiến thuật:**  
- Nếu có **N món đồ**, ta có **2^N cách chọn** (mỗi món có thể **chọn hoặc không chọn**).  
- Ta thử tất cả cách rồi chọn cách tốt nhất.  

💡 **Vấn đề:** Nếu có 100 món, ta phải thử **2^100** cách, quá lâu!  

---

### **3️⃣ Giải bằng quy hoạch động - Nhớ lại để tối ưu**  
**Chiến thuật:**  
- Ta tạo một bảng `dp[i][j]`, trong đó `dp[i][j]` là giá trị lớn nhất khi xét `i` món đồ và balo có sức chứa `j`.  
- Công thức:  
  - Nếu không chọn món `i` → `dp[i][j] = dp[i-1][j]`.  
  - Nếu chọn món `i` → `dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i]] + v[i])`.  
- Tính dần từ nhỏ đến lớn, đảm bảo không làm lại việc cũ.  

🔹 **Kết quả:** DP tìm ra **100 điểm** là cách tốt nhất! 🚀  

---

## **🔍 Tóm lại cách tư duy khi gặp bài toán tối ưu**  
**📌 Bước 1: Xác định xem có thể dùng tham lam không?**  
- Nếu luôn chọn cái tốt nhất trước mà vẫn tối ưu → dùng tham lam.  
- Nếu chọn trước làm mất cơ hội tốt hơn → Tham lam không phù hợp.  

**📌 Bước 2: Nếu tham lam không được, thử chia để trị**  
- Nếu bài toán có thể **chia nhỏ thành các bài toán con độc lập**, dùng chia để trị.  
- Nếu bài toán có **quá nhiều cách chia nhỏ**, chia để trị có thể quá chậm.  

**📌 Bước 3: Nếu chia để trị quá chậm, hãy dùng quy hoạch động**  
- Xác định **trạng thái (dp[i][j])** phù hợp.  
- Viết công thức để tính trạng thái này từ trạng thái trước.  
- **Duyệt theo thứ tự đúng** để đảm bảo luôn có kết quả trước khi dùng.  

---

## **🚀 Bài tập rèn luyện**  
Hãy thử nghĩ cách giải bài toán này bằng tham lam, chia để trị, và quy hoạch động:  

🔹 **Bài toán:** Bạn có thể leo cầu thang, mỗi lần đi **1 bước hoặc 2 bước**. Có bao nhiêu cách để lên tới bậc thứ `N`?  

Hãy thử nghĩ và trả lời nhé! 🎯