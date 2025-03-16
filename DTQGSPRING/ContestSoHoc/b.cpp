#include <bits/stdc++.h>
using namespace std;
int prime[1000006];
vector<int> primes;
void sangnguyento(){
    for(int i = 1; i <= 1000006; ++i) prime[i] = 1;
    prime[0]=prime[1]=0;
    for(int i = 2; i <= sqrt(1000006); ++i)
        if(prime[i]){
            for(int j = i*i; j <= 1000006; j+=i)
                prime[j]=0;
            primes.push_back(i);
        }
}

int countDiv(long long n) {
    int cnt = 1;
    for (int p : primes) {
        
        if (p * p > n)
            break;
        if (n % p == 0) {
            int exp = 0;
            while (n % p == 0) {
                exp++;
                n /= p;
            }
            cnt *= (exp + 1);
        }
    }
    if (n > 1) {
        cnt *= 2;
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    sangnguyento();
    int t;cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        cout << countDiv(n) << '\n';
    }
    return 0;
}