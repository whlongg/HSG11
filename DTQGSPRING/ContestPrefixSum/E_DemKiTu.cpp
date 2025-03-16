#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 6;
int prefix[N][26];

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); ++i)
    {
        for (int j = 0; j < 26; ++j)
            prefix[i + 1][j] = prefix[i ][j];
        prefix[i + 1][s[i] - 'a']++;
    }
    while (q--)
    {
        char c;
        int l, r;
        cin >> c >> l >> r;
        int ans = prefix[r][c - 'a'] - prefix[l - 1][c - 'a'];
        cout << ans << '\n';
    }
}