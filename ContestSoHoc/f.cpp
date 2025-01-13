#include <bits/stdc++.h>
using namespace std;
long long x, y, d;

void egcd(long long a, long long b) {
    if (b == 0) {
        x = 1;
        y = 0;
        d = a;
        return;
    }
    egcd(b, a % b);
    long long x1 = y;
    long long y1 = x - (a / b) * y;
    x = x1;
    y = y1;
}

int main() {
    long long a, b;
    cin >> a >> b;
    egcd(a, b);
    cout << x << " " << y << '\n';
    return 0;
}