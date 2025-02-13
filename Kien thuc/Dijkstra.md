# 🧭 Thuật toán Dijkstra - Tìm Đường Đi Ngắn Nhất trên Đồ Thị 🚀
_cre: Astrelix_
## 1. 👋 Giới thiệu về Thuật toán Dijkstra

Thuật toán Dijkstra là một trong những thuật toán **kinh điển** ✨ và **mạnh mẽ** 💪 nhất trong lĩnh vực đồ thị, được Edsger W. Dijkstra công bố vào năm 1959.  Nó được sử dụng để giải quyết bài toán **tìm đường đi ngắn nhất từ một đỉnh nguồn đến tất cả các đỉnh còn lại** trong một đồ thị có trọng số không âm 🎯.

### Ứng dụng rộng rãi:

Thuật toán Dijkstra có vô số ứng dụng trong thực tế, ví dụ:

*   **🗺️ Định tuyến đường đi trên bản đồ:** Các ứng dụng bản đồ (Google Maps, Apple Maps) sử dụng Dijkstra (hoặc các biến thể) để tìm đường đi ngắn nhất giữa hai địa điểm, dựa trên mạng lưới đường giao thông và thời gian di chuyển/khoảng cách trên từng đoạn đường.
*   **🌐 Giao thức định tuyến mạng (Network Routing Protocols):** Trong mạng máy tính, Dijkstra được sử dụng trong các giao thức định tuyến như OSPF (Open Shortest Path First) để tìm đường đi ngắn nhất cho gói tin dữ liệu, giúp tối ưu hóa việc truyền tải thông tin trên mạng.
*   **🚗 Điều hướng tự lái:**  Trong xe tự lái, thuật toán Dijkstra có thể được sử dụng để lập kế hoạch đường đi hiệu quả, dựa trên bản đồ số, thông tin giao thông và các ràng buộc về luật lệ.
*   **🏭 Lập kế hoạch sản xuất và vận chuyển:**  Trong quản lý chuỗi cung ứng và logistics, Dijkstra có thể giúp tìm đường đi vận chuyển hàng hóa tối ưu, giảm thiểu chi phí và thời gian.
*   **🕹️ Trò chơi điện tử và AI:**  Trong game và trí tuệ nhân tạo, Dijkstra được dùng trong các thuật toán tìm đường đi cho nhân vật, robot, hoặc các tác nhân thông minh khác trong môi trường ảo.

## 2. 🤔 Bài toán Đường Đi Ngắn Nhất và Điều kiện Áp dụng Dijkstra

### 2.1. Bài toán Đường Đi Ngắn Nhất (Shortest Path Problem):

Cho một đồ thị có trọng số `G = (V, E)`, trong đó:

*   `V`: Tập hợp các đỉnh (vertices).
*   `E`: Tập hợp các cạnh (edges), mỗi cạnh `(u, v)` có trọng số không âm `w(u, v)`.
*   **Đỉnh nguồn `s`:** Một đỉnh xuất phát được chỉ định.

**Mục tiêu:** Tìm đường đi có tổng trọng số nhỏ nhất từ đỉnh nguồn `s` đến **tất cả các đỉnh `v` khác** trong đồ thị.

### 2.2. Điều kiện Áp dụng Thuật toán Dijkstra:

**Quan trọng:** Thuật toán Dijkstra chỉ hoạt động đúng đắn khi **trọng số của tất cả các cạnh trong đồ thị là không âm** (lớn hơn hoặc bằng 0).

**Tại sao cần trọng số không âm?**

Thuật toán Dijkstra dựa trên nguyên lý "tham lam" (greedy): tại mỗi bước, nó chọn đỉnh có khoảng cách ngắn nhất **tạm thời** từ nguồn và **xác nhận** đó là khoảng cách ngắn nhất **thực sự**. Nếu đồ thị có cạnh trọng số âm, nguyên lý tham lam này có thể bị phá vỡ, dẫn đến kết quả không chính xác.

**Khi nào nên dùng Dijkstra?**

*   Khi bạn cần tìm đường đi ngắn nhất từ một đỉnh nguồn đến **nhiều đỉnh khác** (hoặc tất cả các đỉnh) trong đồ thị.
*   Khi đồ thị có **trọng số cạnh không âm**.
*   Đồ thị có thể là **có hướng** hoặc **vô hướng**.

**Khi nào không nên dùng Dijkstra?**

*   Khi đồ thị có **cạnh trọng số âm**. Trong trường hợp này, bạn cần sử dụng thuật toán khác như **Bellman-Ford** hoặc ** thuật toán SPFA** (Shortest Path Faster Algorithm) (lưu ý SPFA không phải lúc nào cũng hoạt động tốt trong mọi trường hợp, có thể bị "bẫy" trong một số test case đặc biệt).
*   Khi bạn chỉ cần tìm đường đi ngắn nhất giữa **một cặp đỉnh** cụ thể (không phải từ một nguồn đến tất cả các đỉnh). Trong trường hợp này, Dijkstra vẫn có thể dùng được, nhưng có thể dừng sớm khi đã tìm thấy đường đi đến đỉnh đích, hoặc các thuật toán khác như A* search có thể hiệu quả hơn nếu có thêm thông tin heuristic.

## 3. ⚙️ Thuật toán Dijkstra - Các Bước Chi Tiết

Thuật toán Dijkstra hoạt động theo các bước sau:

1.  **Khởi tạo:**
    *   Gán **khoảng cách từ đỉnh nguồn `s` đến chính nó là 0:** `distance[s] = 0`.
    *   Gán **khoảng cách từ đỉnh nguồn `s` đến tất cả các đỉnh `v` khác là vô cùng lớn:** `distance[v] = ∞` (với mọi `v ≠ s`).
    *   Tạo một tập hợp **chưa xét `S`** chứa tất cả các đỉnh trong đồ thị. Tập `S` sẽ chứa các đỉnh mà chúng ta chưa **xác nhận** được khoảng cách ngắn nhất từ nguồn.

2.  **Lặp:** Trong khi tập **chưa xét `S` không rỗng**:
    *   **Chọn đỉnh `u` trong `S` có khoảng cách `distance[u]` nhỏ nhất**. Đỉnh này là đỉnh "gần nguồn nhất" trong số các đỉnh chưa xét.
    *   **Loại `u` khỏi tập `S`** (đánh dấu `u` là đã xét/đã tìm được đường đi ngắn nhất).
    *   **Cập nhật khoảng cách cho các đỉnh `v` kề với `u`:**  Duyệt qua tất cả các đỉnh `v` là hàng xóm của `u`. Với mỗi đỉnh `v`:
        *   Tính **khoảng cách từ nguồn `s` đến `v` qua `u`:** `new_distance = distance[u] + w(u, v)` (với `w(u, v)` là trọng số cạnh `(u, v)`).
        *   **Nếu `new_distance < distance[v]`:**  Điều này có nghĩa là chúng ta vừa tìm ra một đường đi ngắn hơn đến `v` (đi qua `u`). Cập nhật `distance[v] = new_distance`.

3.  **Kết thúc:** Khi tập `S` trở thành rỗng, thuật toán kết thúc. Mảng `distance` sẽ chứa khoảng cách ngắn nhất từ đỉnh nguồn `s` đến tất cả các đỉnh khác trong đồ thị. Nếu `distance[v] == ∞`, điều đó có nghĩa là không có đường đi từ `s` đến `v`.

## 4. 💻 Cài đặt Thuật toán Dijkstra (C++ với Priority Queue)

Để cài đặt thuật toán Dijkstra hiệu quả, chúng ta thường sử dụng **priority queue (hàng đợi ưu tiên)** để quản lý các đỉnh trong tập **chưa xét `S`** và nhanh chóng tìm ra đỉnh `u` có khoảng cách nhỏ nhất.

**Cấu trúc dữ liệu:**

*   **Đồ thị:** Sử dụng **danh sách kề (adjacency list)** `adj` để biểu diễn đồ thị. `adj[u]` là một danh sách các cặp `(v, weight)` cạnh từ `u` đến `v` có trọng số `weight`.
*   **Mảng khoảng cách `distance`:** Mảng `distance[n]` (với `n` là số đỉnh) để lưu khoảng cách ngắn nhất từ đỉnh nguồn đến mỗi đỉnh. Khởi tạo `distance[source] = 0` và `distance[v] = ∞` cho các đỉnh khác.
*   **Priority queue `pq`:**  Priority queue lưu các cặp `(khoảng_cách, đỉnh)`, ưu tiên các đỉnh có khoảng cách nhỏ hơn.

**Code C++ (Thuật toán Dijkstra với Priority Queue):**

```c++
#include <iostream>
#include <vector>
#include <queue>
#include <limits> // Để dùng numeric_limits<long long>::max()

using namespace std;

const long long INF = numeric_limits<long long>::max(); // Vô cùng lớn

int main() {
    int n, m; // n: số đỉnh, m: số cạnh
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n); // Danh sách kề
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v; // Đỉnh bắt đầu từ 0 (0-based indexing)
        adj[u].push_back({v, w}); // Cạnh (u, v) trọng số w
        adj[v].push_back({u, w}); // Nếu đồ thị vô hướng (bỏ dòng này nếu có hướng)
    }

    int source_node = 0; // Đỉnh nguồn (ví dụ đỉnh 0)
    vector<long long> distance(n, INF); // Mảng khoảng cách
    distance[source_node] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, source_node}); // {khoảng_cách, đỉnh}

    while (!pq.empty()) {
        long long d = pq.top().first; // Khoảng cách hiện tại
        int u = pq.top().second; // Đỉnh hiện tại
        pq.pop();

        if (d > distance[u]) {
            continue; // Nếu khoảng cách trong pq lớn hơn khoảng cách đã biết, bỏ qua
        }

        for (auto& edge : adj[u]) { // Duyệt các cạnh kề của u
            int v = edge.first; // Đỉnh kề
            int weight = edge.second; // Trọng số cạnh (u, v)
            if (distance[u] + weight < distance[v]) { // Nếu tìm được đường đi ngắn hơn đến v
                distance[v] = distance[u] + weight; // Cập nhật khoảng cách đến v
                pq.push({distance[v], v}); // Thêm v vào priority queue
            }
        }
    }

    // In khoảng cách ngắn nhất từ đỉnh nguồn đến các đỉnh khác
    cout << "Khoảng cách ngắn nhất từ đỉnh " << source_node + 1 << " đến các đỉnh khác:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Đỉnh " << i + 1 << ": ";
        if (distance[i] == INF) {
            cout << "Không có đường đi" << endl;
        } else {
            cout << distance[i] << endl;
        }
    }

    return 0;
}
````

**Giải thích code:**

  * **`#include <queue>`:** Sử dụng priority queue.
  * **`const long long INF = numeric_limits<long long>::max();`:** Định nghĩa giá trị vô cùng lớn để biểu thị khoảng cách ban đầu và khi không có đường đi.
  * **`vector<vector<pair<int, int>>> adj(n);`:** Khai báo danh sách kề `adj`.
  * **`priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;`:** Khai báo priority queue `pq` lưu các cặp `(khoảng_cách, đỉnh)`, và ưu tiên đỉnh có khoảng cách nhỏ hơn (`greater<pair<long long, int>>`).
  * **Vòng lặp `while (!pq.empty())`:** Vòng lặp chính của thuật toán Dijkstra.
  * **`pq.push({distance[v], v});`:** Thêm đỉnh `v` vào priority queue khi tìm thấy đường đi ngắn hơn đến `v`.
  * **`if (d > distance[u]) continue;`:**  Kiểm tra quan trọng để tránh xử lý lại các đỉnh đã được tối ưu hóa.

## 5\. ⏱️ Phân tích Độ phức tạp

  * **Xây dựng đồ thị (danh sách kề):** O(V + E), với V là số đỉnh, E là số cạnh.
  * **Khởi tạo:** O(V).
  * **Thuật toán Dijkstra với priority queue:**
      * **Số lần lặp `while` (tối đa):** O(V) (mỗi đỉnh được đưa vào và lấy ra khỏi pq tối đa 1 lần).
      * **Trong mỗi lần lặp:**
          * Thao tác `pq.pop()` và `pq.top()`: O(log V) (độ phức tạp của priority queue).
          * Duyệt các cạnh kề của đỉnh `u`: Tổng cộng O(E) cạnh được duyệt trong toàn bộ thuật toán.
          * Thao tác `pq.push()`: O(log V).

**Độ phức tạp tổng thể (Dijkstra với priority queue): O((V + E) log V)** hoặc thường được viết gọn là **O(E log V)** (nếu đồ thị liên thông, E \>= V-1). Trong trường hợp đồ thị dày đặc (E ≈ V²), độ phức tạp có thể gần với O(V² log V).

**So sánh với Dijkstra dùng mảng (không priority queue): O(V²)**

Có một phiên bản khác của Dijkstra sử dụng mảng để tìm đỉnh `u` có khoảng cách nhỏ nhất trong tập `S` (thay vì priority queue). Trong phiên bản này:

  * Tìm đỉnh `u` có khoảng cách nhỏ nhất trong `S`: O(V) (duyệt mảng `distance` và tập `S`).
  * Vòng lặp chính lặp O(V) lần.
  * Cập nhật khoảng cách các đỉnh kề: O(bậc của đỉnh u) - tổng cộng O(E) cho toàn bộ thuật toán.

**Độ phức tạp (Dijkstra dùng mảng): O(V²)**.

**Khi nào chọn Priority Queue vs. Mảng?**

  * **Priority Queue (O(E log V)):** Thường hiệu quả hơn cho **đồ thị thưa** (số cạnh E gần với số đỉnh V), vì log V thường nhỏ hơn V nhiều.
  * **Mảng (O(V²)):**  Có thể nhanh hơn một chút cho **đồ thị dày đặc** (số cạnh E gần với V²), vì không có overhead của priority queue. Tuy nhiên, với đồ thị lớn, priority queue thường vẫn là lựa chọn tốt hơn do sự khác biệt đáng kể về độ phức tạp khi V lớn. Trong competitive programming, Dijkstra với priority queue là phiên bản phổ biến và thường được ưu tiên sử dụng.

## 6\. 📝 Ví dụ Minh họa - Bài toán MEGA và "Tìm Cảng Trung Tâm"

Để hiểu rõ hơn về ứng dụng của thuật toán Dijkstra, chúng ta sẽ xem xét hai ví dụ minh họa:

### 6.1. Bài toán MEGA

**Đề bài:**

Đất nước Mega được mệnh danh là vùng đất có rất nhiều đảo đẹp và yên bình. Hàng năm có rất nhiều tàu thuyền khắp nơi trên thế giới ghé thăm đất nước Mega để tham quan, du lịch và kinh doanh. Để phát triển kinh tế, giao thương và thu hút đầu tư nước Mega đã kêu gọi sự đầu tư của nhiều công ty lớn trên thế giới đến xây dựng các cảng biển. Đến thời điểm hiện tại đã xây dựng được n cảng biển, các cảng này được kết nối với nhau với hệ thống giao thông đường thủy gồm m đường 2 chiều, đảm bảo sự giao thương giữa 2 cảng bất kỳ (trực tiếp hoặc gián tiếp thông qua cảng trung gian). Giữa 2 cảng bất kỳ có không quá một đường đi trực tiếp.

Việc đầu tư, vận hành, bảo trì các cảng này được giao cho 2 công ty lớn là Greek (G) và Yamato (Y) độc quyền đảm nhận. Các tàu thuyền hoạt động trên các cảng này đều thuộc quyền sở hữu của 2 công ty trên thực hiện. Các tàu thuyền khi vận chuyển hàng và người từ cảng này sang cảng khác thì chủ thuyền phải trả chi phí là 1 đơn vị tiền tệ, ngoài ra tàu thuyền khi đi qua cảng mà không phải do công ty mình quản lý thì chủ thuyền phải trả thêm 3 đơn vị tiền tệ. Tất nhiên, khi vận chuyển hàng hóa và người, chủ thuyền bao giờ cũng chọn con đường ứng với tổng chi phí nhỏ nhất.

**Yêu cầu**: Cho biết 𝑛, 𝑚 và mạng giao thông trong Mega, hãy giúp công ty G và Y tính tổng chi phí vận chuyển hàng giữa tất cả các cảng biển thuộc tập đoàn của họ. 

**Input:**
* Dòng đầu tiên chứa hai số nguyên 𝑛, 𝑚
* Dòng thứ hai chứa xâu gồm 𝑛 ký tự, mỗi ký tự là 𝐺 hoặc 𝑌, ký tự thứ 𝑖 cho biết cảng 𝑖 thuộc tập đoàn 𝐺 hay 𝑌. 
* Tiếp theo là 𝑚 dòng, mỗi dòng chứa hai số nguyên 𝑖, 𝑗 xác định đường nối cảng 𝑖 với cảng 𝑗. 

**Output:**
* Gồm một dòng chứa hai số tương ứng là tổng chi phí vận chuyển hàng giữa tất cả các cảng thuộc tập đoàn G và Y.

**Ví dụ:**
```
Input:
5 5 
YGYGY 
1 2 
2 3 
3 4 
4 5 
5 1

Ouput:
5 11
```

**Ứng dụng Dijkstra:**

Trong bài toán MEGA, chúng ta sử dụng thuật toán Dijkstra để tìm đường đi ngắn nhất giữa các cặp cảng, với chi phí vận chuyển được tính dựa trên cả khoảng cách đường đi và việc đi qua cảng của công ty khác.  Sau khi tính toán ma trận khoảng cách bằng Dijkstra, chúng ta dễ dàng tính tổng chi phí cho từng công ty.

### 6.2. Bài toán Ví dụ 2: "Tìm Cảng Trung Tâm"

**Đề bài:**

Đất nước XYZ có hệ thống giao thông đường biển kết nối `N` cảng biển với nhau. Ma trận `M[i][j]` cho biết khoảng cách trực tiếp giữa cảng `i` và cảng `j`. Nếu `M[i][j] = -1`, nghĩa là không có đường đi trực tiếp giữa cảng `i` và `j`. Hãy tìm một cảng biển **"trung tâm"**, sao cho **tổng khoảng cách từ cảng trung tâm này đến tất cả các cảng biển khác là nhỏ nhất**. Nếu có nhiều cảng thỏa mãn, hãy chọn cảng có chỉ số nhỏ nhất.

**Input:**

  * Dòng đầu tiên: Số nguyên dương `N` (số lượng cảng, `1 <= N <= 100`).
  * `N` dòng tiếp theo: Ma trận `M[i][j]` kích thước `N x N`, với `M[i][j]` là khoảng cách giữa cảng `i` và `j` (`M[i][j] = -1` nếu không có đường đi trực tiếp).

**Output:**

  * Chỉ số của cảng trung tâm (1-based index).

**Ví dụ:**

```
Input:
5
0 10 5 -1 -1
10 0 6 8 -1
5 6 0 3 7
-1 8 3 0 2
-1 -1 7 2 0

Output:
3
```

**Giải thích ví dụ:**

Cảng 3 là cảng trung tâm, vì tổng khoảng cách từ cảng 3 đến các cảng khác là nhỏ nhất:

  * Cảng 3 -\> Cảng 1: 5
  * Cảng 3 -\> Cảng 2: 6
  * Cảng 3 -\> Cảng 4: 3
  * Cảng 3 -\> Cảng 5: 7
    **Tổng khoảng cách: 5 + 6 + 3 + 7 = 21**

Các cảng khác có tổng khoảng cách lớn hơn.

**Hướng dẫn giải (sử dụng Dijkstra):**

1.  **Xây dựng đồ thị:**  Từ ma trận khoảng cách `M`, xây dựng đồ thị có `N` đỉnh (cảng). Nếu `M[i][j] != -1`, thì có cạnh giữa đỉnh `i` và `j` với trọng số `M[i][j]`. Nếu `M[i][j] == -1`, không có cạnh trực tiếp.

2.  **Tính tổng khoảng cách từ mỗi cảng đến các cảng khác:**

      * Lặp qua từng cảng `i` từ 1 đến `N`.
      * Chạy thuật toán Dijkstra với đỉnh nguồn là cảng `i`.
      * Tính tổng khoảng cách từ cảng `i` đến tất cả các cảng `j` khác (với `j != i`), sử dụng mảng `distance` trả về từ Dijkstra.
      * Lưu tổng khoảng cách này cho cảng `i`.

3.  **Tìm cảng trung tâm:**  Sau khi tính tổng khoảng cách cho mỗi cảng, tìm cảng có tổng khoảng cách nhỏ nhất. Nếu có nhiều cảng có cùng tổng khoảng cách nhỏ nhất, chọn cảng có chỉ số nhỏ nhất (theo yêu cầu đề bài).

4.  **In kết quả:** In chỉ số của cảng trung tâm tìm được.

**Code C++ (cho bài toán "Tìm Cảng Trung Tâm"):**

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e18;

int32_t main(void) {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != -1 && i != j) {
                adj[i].push_back({j, matrix[i][j]});
            }
        }
    }

    ll min_total_distance = INF;
    int center_port = -1;

    for (int start_node = 0; start_node < n; ++start_node) {
        vector<ll> distance(n, INF);
        distance[start_node] = 0;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        pq.push({0, start_node});

        while (!pq.empty()) {
            ll d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > distance[u]) continue;

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    pq.push({distance[v], v});
                }
            }
        }

        ll current_total_distance = 0;
        for (int i = 0; i < n; ++i) {
            if (i != start_node && distance[i] != INF) {
                current_total_distance += distance[i];
            }
        }

        if (current_total_distance < min_total_distance) {
            min_total_distance = current_total_distance;
            center_port = start_node + 1; // 1-based indexing
        }
    }

    cout << center_port << '\n;

    return 0;
}
```

**Giải thích code (Cảng Trung Tâm):**

  * Code này tương tự như code Dijkstra trước đó, nhưng được điều chỉnh để giải bài toán "Cảng Trung Tâm".
  * **Đọc ma trận khoảng cách `matrix`** và xây dựng danh sách kề `adj`.
  * **Vòng lặp ngoài:** Duyệt qua từng cảng `start_node` để thử làm cảng trung tâm.
  * **Chạy Dijkstra từ `start_node`** để tính khoảng cách đến tất cả các cảng khác.
  * **Tính `current_total_distance`:** Tổng khoảng cách từ `start_node` đến các cảng khác.
  * **Cập nhật `min_total_distance` và `center_port`:** Tìm cảng có tổng khoảng cách nhỏ nhất.

## 7\. 🎉 Kết luận

Thuật toán Dijkstra là một công cụ **vô cùng mạnh mẽ** 💪 và **đa năng** ✨ cho các bài toán liên quan đến đường đi ngắn nhất trên đồ thị có trọng số không âm. Hiểu rõ thuật toán Dijkstra, cách cài đặt hiệu quả với priority queue, và các ứng dụng của nó là một kỹ năng **quan trọng** 🔑 cho bất kỳ lập trình viên nào, đặc biệt trong lĩnh vực competitive programming và khoa học máy tính. Hãy **luyện tập** 🏋️‍♀️ thêm với nhiều bài tập khác nhau để nắm vững thuật toán này\! 

## 8\. 🔗 Tham khảo và Tài nguyên Hữu ích 📚

  * [Dijkstra's Algorithm - GeeksforGeeks](https://www.google.com/url?sa=E&source=gmail&q=https://www.geeksforgeeks.org/dijkstra-algorithm/)
  * [Dijkstra's Algorithm - Wikipedia](https://www.google.com/url?sa=E&source=gmail&q=https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

🚀 **Happy Coding\!** 🎯
