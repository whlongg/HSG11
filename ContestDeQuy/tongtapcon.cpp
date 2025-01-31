#include <bits/stdc++.h>
using namespace std;
int result = 0;

void backtrack(int i, int sum, int count, int n, int s, int a[])
{
    if (i == n)
    {
        if (sum == s && count > 0)
            result++;
        return;
    }
    backtrack(i + 1, sum + a[i], count + 1, n, s, a);
    backtrack(i + 1, sum, count, n, s, a);
}

int main()
{
    int n, s;
    cin >> n >> s;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    backtrack(0, 0, 0, n, s, a);
    cout << result << endl;

    return 0;
}