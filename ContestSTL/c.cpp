#include <bits/stdc++.h>
using namespace std;

int32_t main(){
    map <char, int> mp;
    string s; cin >> s;
    for(int i = 0; i < s.size(); ++i)
        mp[s[i]]++;
    for(auto it : mp)
        cout << it.first << ' ' << it.second << '\n';
}