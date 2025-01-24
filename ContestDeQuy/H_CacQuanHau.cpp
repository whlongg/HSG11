#include <bits/stdc++.h>
using namespace std;
char board[8][8];
int ans = 0;

bool ok(int row, int col, vector<int> &loc)
{
    for (int prev_row = 0; prev_row < row; ++prev_row)
    {
        int diff = row - prev_row;
        if (loc[prev_row] == col || loc[prev_row] == col - diff || loc[prev_row] == col + diff)
            return false;
    }
    return true;
}

void rec(int row, vector<int> &loc)
{
    if (row == 8)
    {
        ans++;
        return;
    }
    for (int col = 0; col < 8; ++col)
        if (board[row][col] == '.' && ok(row, col, loc))
        {
            loc[row] = col;
            rec(row + 1, loc);
        }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("queens.inp", "r", stdin);freopen("queens.out", "w", stdout);
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            cin >> board[i][j];
    vector<int> loc(8, -1);
    rec(0, loc);
    cout << ans << '\n';
    return 0;
}