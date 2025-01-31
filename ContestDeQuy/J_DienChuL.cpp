#include <iostream>
#include <vector>

using namespace std;

int cnt = 1;

void fill(int n, int x, int y, int rs, int cs, vector<vector<int>> &b)
{
    if (n == 1)
    {
        for (int i = rs; i < rs + 2; ++i)
            for (int j = cs; j < cs + 2; ++j)
                if (!(i == rs + x - 1 && j == cs + y - 1))
                    b[i][j] = cnt;
        cnt++;
        return;
    }
    int mr = rs + (1 << (n - 1)) - 1;
    int mc = cs + (1 << (n - 1)) - 1;
    int s = 1 << (n - 1);
    int hq;
    if (x <= s && y <= s)
        hq = 1;
    else if (x <= s && y > s)
        hq = 2;
    else if (x > s && y <= s)
        hq = 3;
    else
        hq = 4;
    if (hq != 1)
        b[mr][mc] = cnt;
    if (hq != 2)
        b[mr][mc + 1] = cnt;
    if (hq != 3)
        b[mr + 1][mc] = cnt;
    if (hq != 4)
        b[mr + 1][mc + 1] = cnt;
    cnt++;
    fill(n - 1, (hq == 1) ? x : s, (hq == 1) ? y : s, rs, cs, b);
    fill(n - 1, (hq == 2) ? x : s, (hq == 2) ? y - s : 1, rs, mc + 1, b);
    fill(n - 1, (hq == 3) ? x - s : 1, (hq == 3) ? y : s, mr + 1, cs, b);
    fill(n - 1, (hq == 4) ? x - s : 1, (hq == 4) ? y - s : 1, mr + 1, mc + 1, b);
}

int main()
{
    ios_base::sync_with_stdio(00);
    cin.tie(0);
    int n, x, y;
    cin >> n >> x >> y;
    int s = 1 << n;
    vector<vector<int>> b(s, vector<int>(s, 0));
    fill(n, x, y, 0, 0, b);
    for (int i = 0; i < s; ++i)
    {
        for (int j = 0; j < s; ++j)
            cout << b[i][j] << " ";
        cout << "\n";
    }
    return 0;
}