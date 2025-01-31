#include <bits/stdc++.h>
using namespace std;
#define int long long

int solve(int a, int b, int c) {
    int res = 0;
    a %= c;
    while (b > 0){
        if (b % 2 == 1)
            res = (res + a) % c;
        a = (a * 2) % c;
        b /= 2;
    }
    return res;
}

int32_t main() {
    int a, b, c;
    cin >> a >> b >> c;
    cout << solve(a, b, c);
    return 0;
}