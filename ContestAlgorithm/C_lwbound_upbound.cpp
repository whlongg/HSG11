#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int &x : a)
    {
        cin >> x;
    }
    while (q--)
    {
        int t, x;
        cin >> t >> x;

        if (t == 1)
        {
            auto it = lower_bound(a.begin(), a.end(), x);
            if (it == a.end())
            {
                cout << -1 << "\n";
            }
            else
            {
                cout << *it << "\n";
            }
        }
        else if (t == 2)
        {
            auto it = upper_bound(a.begin(), a.end(), x);
            if (it == a.end())
            {
                cout << -1 << "\n";
            }
            else
            {
                cout << *it << "\n";
            }
        }
        else if (t == 3)
        {
            auto it = upper_bound(a.begin(), a.end(), x);
            if (it == a.begin())
            {
                if (binary_search(a.begin(), a.end(), x))
                {
                    cout << x << "\n";
                }
                else
                {
                    cout << -1 << "\n";
                }
            }
            else
            {
                it--;
                if (*it > x)
                {
                    cout << -1 << "\n";
                }
                else
                {
                    cout << *it << "\n";
                }
            }
        }
        else if (t == 4)
        {
            auto it = lower_bound(a.begin(), a.end(), x);
            if (it == a.begin())
            {
                cout << -1 << "\n";
            }
            else
            {
                it--;
                cout << *it << "\n";
            }
        }
        else if (t == 5)
        {
            auto it1 = lower_bound(a.begin(), a.end(), x);
            auto it2 = upper_bound(a.begin(), a.end(), x);
            cout << (it2 - it1) << "\n";
        }
    }

    return 0;
}