//ContestCodeforces/2092/D.cpp
//https://codeforces.com/contest/2092/problem/D
#include <bits/stdc++.h>
using namespace std;

bool check(const string &s)
{
    int n = s.length();
    if (n == 0 || n % 3 != 0)
    {
        return false;
    }
    int target = n / 3;
    map<char, int> cnts;
    for (char c : s)
    {
        cnts[c]++;
    }
    return (cnts.count('L') && cnts['L'] == target &&
            cnts.count('I') && cnts['I'] == target &&
            cnts.count('T') && cnts['T'] == target);
}

map<char, int> get_cnts(const string &s)
{
    map<char, int> cnts;
    for (char c : s)
    {
        cnts[c]++;
    }
    cnts.try_emplace('L', 0);
    cnts.try_emplace('I', 0);
    cnts.try_emplace('T', 0);
    return cnts;
}

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (check(s))
    {
        cout << 0 << "\n";
        return;
    }
    vector<int> ans;
    int limit = 2 * n;
    for (int k = 0; k < limit; ++k)
    {
        if (check(s))
        {
            break;
        }
        int len = s.length();
        int best_pos = -1;
        char best_ch = ' ';
        bool possible_op = false;
        map<char, int> c_cnts = get_cnts(s);
        int min_cnt = min({c_cnts['L'], c_cnts['I'], c_cnts['T']});
        int p_pos = -1;
        char p_ch = ' ';
        int fall_pos = -1;
        char fall_ch = ' ';
        for (int i = 0; i < len - 1; ++i)
        {
            if (s[i] != s[i + 1])
            {
                possible_op = true;
                char ch_to_insert = (char)(233 - s[i] - s[i + 1]);
                if (fall_pos == -1)
                {
                    fall_pos = i;
                    fall_ch = ch_to_insert;
                }
                if (c_cnts[ch_to_insert] == min_cnt)
                {
                    if (p_pos == -1)
                    {
                        p_pos = i;
                        p_ch = ch_to_insert;
                    }
                }
            }
        }
        if (p_pos != -1)
        {
            best_pos = p_pos;
            best_ch = p_ch;
        }
        else if (fall_pos != -1)
        {
            best_pos = fall_pos;
            best_ch = fall_ch;
        }
        else
        {
            break;
        }
        s.insert(best_pos + 1, 1, best_ch);
        ans.push_back(best_pos + 1);
    }
    if (check(s))
    {
        cout << ans.size() << "\n";
        for (int x : ans)
        {
            cout << x << "\n";
        }
    }
    else
    {
        cout << -1 << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
