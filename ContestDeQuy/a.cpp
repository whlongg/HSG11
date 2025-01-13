#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        string s = "";
        if (n == 0)
        {
            s = "0";
        }
        else
        {
            while (n > 0)
            {
                s = (n % 2 == 0 ? "0" : "1") + s;
                n /= 2;
            }
        }
        cout << s << '\n';
    }
    return 0;
}