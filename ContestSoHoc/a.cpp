#include <bits/stdc++.h>
using namespace std;

int ptich(long long n) {
    int cnt = 1;
    for (long long i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            int exp = 0;
            while (n % i == 0) {
                exp++;
                n /= i;
            }
            cnt *= (exp + 1);
        }
    if (n > 1)
        cnt *= 2;
    return cnt;
}

int main() {
    long long n;cin >> n;
    cout << ptich(n);
    return 0;
}