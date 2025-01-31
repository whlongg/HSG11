#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    string s;
    int k = 0;
    vector<int> v;
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        if (s != "size")
            cin >> k;
        cin.ignore();
        cout << '\n' << "index: " << i << '\n' << s << ' ' << k << '\n';
        if (s == "push")
        {
            v.push_back(k);
        }
        else if (s == "pop")
        {
            v.pop_back();
        }
        else if (s == "index")
        {
            int res = k < v.size()-1 && k >= 0 ? k : -1;
            cout << res << '\n';
        }
        else
        {
            cout << v.size();
        }
    }
    return 0;
}

