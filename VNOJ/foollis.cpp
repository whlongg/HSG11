//VNOJ/foollis.cpp
//https://oj.vnoi.info/problem/fc146_foollis

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
const int MAX_VAL = 100001; 
vector<int> tree(4 * MAX_VAL, 0); 

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = max(tree[node], val);
        return;
    }
    int mid = (start + end) / 2;
    if (start <= idx && idx <= mid)
        update(2 * node, start, mid, idx, val);
    else
        update(2 * node + 1, mid + 1, end, idx, val);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

int query(int node, int start, int end, int l, int r) {
    if (r < start || end < l)
        return 0;
    if (l <= start && end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    int p1 = query(2 * node, start, mid, l, r);
    int p2 = query(2 * node + 1, mid + 1, end, l, r);
    return max(p1, p2);
}

int solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    if (n == 0)
        return 0;
    fill(tree.begin(), tree.end(), 0);
    vector<int> dp(n, 1);
    int max_len = 1;
    for (int i = 0; i < n; ++i) {
        int startr = max(1, a[i] - k);
        int endr = a[i] - 1;
        if (startr <= endr) {
            int max_prev = query(1, 1, MAX_VAL - 1, startr, endr);
            dp[i] = max_prev + 1;
        }
        update(1, 1, MAX_VAL - 1, a[i], dp[i]);
        max_len = max(max_len, dp[i]);
    }
    return max_len;
}


int32_t main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);
    //file("input.txt", "output.txt");
    int q = 1;
    //cin >> q;
    while(q--)
        cout << solve() << '\n';
    return 0;
}