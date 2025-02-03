#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,x; cin >> n; vector <int> a;
    for(int i = 1; i <= n; ++i) cin >> x, a.push_back(x);
    for(int i : a)  cout << ((i&1)?"so le\n":"so chan\n"), cout << '\n';
}