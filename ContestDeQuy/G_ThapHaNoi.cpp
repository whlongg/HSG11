#include <bits/stdc++.h>
using namespace std;

int n;
vector<pair<int, int>> moves;
void rec(int n, int src, int des, int axa)
{
    if (n == 1)
    {
        moves.push_back({src, des});
        return;
    }
    rec(n - 1, src, axa, des);
    moves.push_back({src, des});
    rec(n - 1, axa, des, src);
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    rec(n, 1, 3, 2);
    cout << moves.size() << '\n';
    for (auto &move : moves)
    {
        cout << move.first << " " << move.second << '\n';
    }
    return 0;
}