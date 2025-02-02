#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a[7] = {1, 2, 3, 4, 5, 6, 7};
    set<int> st(a, a + 7);
    auto it = st.find(4);
    advance(it, -2);
    cout << *it;
}