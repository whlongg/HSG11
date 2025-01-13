#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> solve(int n) {
    vector<int> res;
    while(n%2==0){
        res.push_back(2);
        n/=2;
    }
    for(int d=3;d*d<=n;d+=2)
        while(n%d==0){
            res.push_back(d);
            n /= d;
        }
    if(n>1) res.push_back(n);
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;cin >> n;
    vector<int> factors = solve(n);
    map<int, int> counts;
    for (int factor : factors)
        counts[factor]++;
    cout << counts.size() << '\n';
    for (auto const& [factor, count] : counts)
        cout << factor << " " << count << "\n";
    return 0;
}