# **🔥KẾ HOẠCH ÔN LUYỆN 7 NGÀY MAX LEVEL**  
- *Nếu bạn không học gì trong mấy tháng qua, thì chúa cũng không cứu được bạn :)*
- *From hlong with love*
## **📋 MỤC LỤC**
- [Tóm Tắt Kế Hoạch](#-bảng-tóm-tắt-kế-hoạch-7-ngày)
- [Lưu Ý Quan Trọng](#-lưu-ý-quan-trọng)
- [Chi Tiết Kế Hoạch](#-chi-tiết-kế-hoạch-từng-ngày)

| Ngày | Chủ đề | Chiều (Học lý thuyết & Code lại) | Tối (Luyện bài tập thực chiến) |  
|------|--------|---------------------------------|---------------------------------|  
| [1️⃣](#-ngày-1-đồ-thị-cơ-bản-bfs-dfs-connected-components)  | **Đồ thị cơ bản** | BFS, DFS, Connected Components | Bài tập BFS/DFS trên Grid & Graph |  
| [2️⃣](#-ngày-2-đường-đi-ngắn-nhất--chu-trình)  | **Đường đi ngắn nhất & Chu trình** | Dijkstra, Floyd-Warshall, Cycle Detection | Bài tập Dijkstra, Floyd, Chu trình |  
| [3️⃣](#-ngày-3-dp-cơ-bản)  | **DP cơ bản** | Khái niệm DP, DP trên Grid, Fibonacci | Bài tập DP dễ → trung bình |  
| [4️⃣](#-ngày-4-dp-nâng-cao)  | **DP nâng cao** | Knapsack, LIS (Dãy con tăng dài nhất) | Bài tập DP nâng cao |  
| [5️⃣](#-ngày-5-kỹ-thuật-quan-trọng)  | **Kỹ thuật quan trọng** | Binary Search, Two Pointers, Sorting | Bài tập áp dụng các kỹ thuật này |  
| [6️⃣](#-ngày-6-cấu-trúc-dữ-liệu)  | **Cấu trúc dữ liệu** | Stack, Queue, Set, Map, Segment Tree | Bài tập về cấu trúc dữ liệu |  
| [7️⃣](#-ngày-7-giả-lập-thi-thật)  | **Giả lập thi thật** | Giải đề thi tỉnh của các năm trước | Tự chấm điểm, ghi lại lỗi, tối ưu phản xạ |  

---

# **🔥 LƯU Ý QUAN TRỌNG**  
✅ **Ngủ đủ 6-7 tiếng/ngày** (không thức quá khuya).  
✅ **Sau mỗi 1.5-2h học, nghỉ 10-15 phút.**  
✅ **Dành 10 phút cuối ngày tổng kết lại kiến thức.**  
✅ **Giữ tinh thần thoải mái, tránh stress.**  

---

# **📌 CHI TIẾT KẾ HOẠCH TỪNG NGÀY**  

## **🔵 NGÀY 1: ĐỒ THỊ CƠ BẢN (BFS, DFS, Connected Components)**  
### **✅ Chiều (Học lý thuyết & Code lại)**
- **BFS & DFS:** Hiểu cách duyệt đồ thị bằng **Queue (BFS)** và **Stack/Recursion (DFS)**.  
- **Connected Components:** Đếm số thành phần liên thông của đồ thị.  
- **Code lại BFS, DFS từ đầu**, tự viết hàm mà không nhìn tài liệu.  

### **🔥 Tối (Luyện bài tập thực chiến)**
- **Bài dễ:** Tìm số thành phần liên thông, đếm số đảo trên bản đồ.  
- **Bài trung bình:** Đường đi ngắn nhất trong grid dùng BFS.  

### **⚠️ Lưu ý:**
- BFS dùng **Queue**, DFS có thể dùng **Stack hoặc Đệ quy**.  
- Đồ thị có thể là **Adjacency List (danh sách kề) hoặc Matrix (ma trận kề)**.  

---

## **🟢 NGÀY 2: ĐƯỜNG ĐI NGẮN NHẤT & CHU TRÌNH**  
### **✅ Chiều (Học lý thuyết & Code lại)**
- **Dijkstra:** Tìm đường đi ngắn nhất từ 1 đỉnh đến tất cả đỉnh khác.  
- **Floyd-Warshall:** Tìm đường đi ngắn nhất giữa mọi cặp đỉnh (khi số đỉnh nhỏ).  
- **Cycle Detection:** Tìm chu trình trong đồ thị có hướng/vô hướng.  

### **🔥 Tối (Luyện bài tập thực chiến)**
- **Bài Dijkstra:** Tìm đường đi ngắn nhất trên đồ thị có trọng số.  
- **Bài Floyd:** Tính tất cả cặp đường đi ngắn nhất.  
- **Bài Cycle Detection:** Kiểm tra đồ thị có chu trình không.  

### **⚠️ Lưu ý:**
- Dijkstra dùng **Priority Queue (Min-Heap)**.  
- Floyd dùng **Ma trận**, độ phức tạp **O(n³)** nên chỉ dùng khi số đỉnh nhỏ (~100).  

---

## **🟡 NGÀY 3: DP CƠ BẢN**  
### **✅ Chiều (Học lý thuyết & Code lại)**
- **Khái niệm DP:** Tư duy lưu trữ kết quả con.  
- **Fibonacci bằng DP:** Code DP bottom-up & top-down.  
- **DP trên Grid:** Tìm đường đi ít tốn kém nhất trong lưới.  

### **🔥 Tối (Luyện bài tập thực chiến)**
- **Bài DP cơ bản:** DP đường đi trên Grid, DP Fibonacci biến thể.  

### **⚠️ Lưu ý:**
- **Top-down (đệ quy có memoization) vs Bottom-up (dùng bảng)**.  
- Khi có **giới hạn nhỏ (<=10⁵), dùng mảng dp**.  

---

## **🟠 NGÀY 4: DP NÂNG CAO**  
### **✅ Chiều (Học lý thuyết & Code lại)**
- **Knapsack:** Dạng bài chọn đồ vật sao cho tổng giá trị lớn nhất.  
- **LIS (Dãy con tăng dài nhất):** Tìm dãy tăng dài nhất.  

### **🔥 Tối (Luyện bài tập thực chiến)**
- **Bài Knapsack (0/1 Knapsack, Unbounded Knapsack)**  
- **Bài LIS (Dùng mảng dp hoặc Binary Search + Fenwick Tree)**  

### **⚠️ Lưu ý:**
- **Knapsack có thể dùng mảng 1D thay vì 2D để tiết kiệm bộ nhớ.**  

---

## **🔴 NGÀY 5: KỸ THUẬT QUAN TRỌNG**  
### **✅ Chiều (Học lý thuyết & Code lại)**
- **Binary Search:** Tìm kiếm trên mảng, tìm nghiệm trong khoảng.  
- **Two Pointers:** Duyệt 2 con trỏ để tối ưu thuật toán.  
- **Sorting & Custom Sort:** Sắp xếp theo điều kiện đặc biệt.  

### **🔥 Tối (Luyện bài tập thực chiến)**
- **Bài Binary Search:** Tìm phần tử trong mảng, tìm giá trị tối ưu.  
- **Bài Two Pointers:** Đếm số cặp thỏa mãn điều kiện.  
- **Bài Sorting:** Custom sort theo yêu cầu bài toán.  

---

## **🟣 NGÀY 6: CẤU TRÚC DỮ LIỆU**  
### **✅ Chiều (Học lý thuyết & Code lại)**
- **Stack / Queue:** Duyệt biểu thức, giải toán biểu thức hậu tố.  
- **Set / Map:** Dùng để lưu trữ, tìm kiếm nhanh.  
- **Segment Tree / Fenwick Tree:** Xử lý truy vấn nhanh trên mảng.  

### **🔥 Tối (Luyện bài tập thực chiến)**
- **Bài Stack/Queue:** Xử lý ngoặc, kiểm tra dãy số hợp lệ.  
- **Bài Set/Map:** Đếm số phần tử khác nhau trong dãy số.  

---

## **⚡ NGÀY 7: GIẢ LẬP THI THẬT**  
- **Thi thử đề tỉnh 3-5 tiếng, tự chấm điểm.**  
- **Ghi lại lỗi sai, tối ưu phản xạ.**  
- **Fix nhanh những phần còn yếu.**  

**💡 Chốt lại:** Theo lộ trình này, bro sẽ **MAX level trong 7 ngày!** 🔥