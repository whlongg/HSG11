#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);
    string s;
    cin >> s;
    int n = s.length();
    int q;
    cin >> q;
    vector<int> k(q);
    for (int i = 0; i < q; ++i)
        cin >> k[i];
    vector<bool> flip(n / 2 + 1, false);
    for (int i = 0; i < q; i++)
        flip[k[i]] = !flip[k[i]];
    for (int i = 1; i <= n / 2; i++)
        flip[i] = flip[i] ^ flip[i - 1];
    for (int i = 1; i <= n / 2; i++)
        if (flip[i])
            swap(s[i - 1], s[n - i]);
    cout << s << '\n';
    return 0;
}