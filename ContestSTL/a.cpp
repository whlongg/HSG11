#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    cin.ignore();
    string s, data;
    int k = 0;
    vector<int> v;
    for (int i = 1; i <= n; i++)
    {
        getline(cin, data);
        stringstream ss(data);
        ss >> s;
        if (s != "size")
            ss >> k;
        // cout << '\n' << i << '\n' << s << ' ' << k << '\n';
        if (s == "push")
        {
            v.push_back(k);
        }
        else if (s == "pop")
        {
            if(!v.empty())
                v.pop_back();
        }
        else if (s == "index")
        {
            //cout << "v.size:" << v.size() << '\n' << '\n';
            int res = k <= v.size() && k >= 0 ? v[k - 1] : -1;
            cout << res << '\n';
        }
        else
        {
            cout << v.size() << '\n';
        }
        
    }
    return 0;
}
