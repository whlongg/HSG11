#include <bits/stdc++.h>
using namespace std;

int main(){
    int n ; cin >> n;
    for(int i = 1; i <(1<<n); ++i)
        cout << (i&i-1)%3 << ' ' << ((i|i-1)+1)%3 << '\n';
}