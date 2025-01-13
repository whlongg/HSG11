#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n; cin >> n;
    int x;
    map <int, vector<int>> mp;
    for(int i = 1; i <= n; ++i){
        cin >> x;
        mp[x].push_back(i);
    }
    for(auto [value, indexs]: mp){
        cout << value << '\n';
        for(int index:indexs)    cout << index << ' ';
        cout << '\n';
    }
}