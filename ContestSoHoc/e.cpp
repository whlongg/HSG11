#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    long long n, p;
    cin >> n >> p;
    long long m = 0;
    long long powp = p;
    while (powp <= n) {
        m += n / powp;
        if (powp > n / p) break;
        powp *= p;
    }
    cout << m << '\n';
    return 0;
}