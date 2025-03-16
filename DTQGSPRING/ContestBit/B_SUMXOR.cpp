#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ll b;
    cin >> b;
    ll temp = b;
    int bit = 0;
    while (temp > 0) {
        bit++;
        temp >>= 1;
    }
    int cnt = 0;
    for (int i = 0; i < bit; ++i) {
        if (((b >> i) & 1) == 0) {
            cnt++;
        }
    }
    ll ans = 1LL << cnt;
    cout << ans;
    return 0;
}