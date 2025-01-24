#include <bits/stdc++.h>
using namespace std;
char a[9][9];
bool ok(int r, int c, char v)
{
    for (int i = 0; i < 9; ++i)
        if (a[r][i] == v || a[i][c] == v)
            return false;
    int br = (r / 3) * 3, bc = (c / 3) * 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (a[br + i][bc + j] == v)
                return false;
    return true;
}
bool rec()
{
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            if (a[r][c] == '.')
            {
                for (char v = '1'; v <= '9'; ++v)
                    if (ok(r, c, v))
                    {
                        a[r][c] = v;
                        if (rec())
                            return true;
                        a[r][c] = '.';
                    }
                return false;
            }
    return true;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            cin >> a[i][j];
    rec();
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
            cout << a[i][j];    
        cout << '\n';
    }
    return 0;
}