#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    string s; 
    int k;
    map <int, int> mp;
    for(int i = 1; i <= n; ++i){
        cin >> s;
        if(s != "size")
            cin >> k;
        cin.ignore();
        //cout << '\n' << "index: " << i << '\n' << s << ' ' << k << '\n';
        if(s == "add"){
            mp[k]++;
            //cout << "data: " << mp[k] << '\n';
        } 
        if(s == "del"){
            if (mp[k] >= 2) {
                mp[k]--;
            }
            else
                mp.erase(k);
        } 
        if(s == "count"){
            if(mp.count(k)==0)
                cout << "0" << '\n';
            else
                cout << mp[k] << '\n';
        } 
        if(s == "size"){
            cout << mp.size() << '\n';
        }
        
    }
    return 0;
}