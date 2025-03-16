#include <bits/stdc++.h>
using namespace std;

int n;
int a[10];
bool used[10];

void rec(int i)
{
    for (int j = 1; j <= n; j++)
        if (!used[j])
        {
            a[i] = j;
            used[j] = 1;
            if (i == n)
            {
                for (int i = 1; i <= n; i++)
                    cout << a[i];
                cout << '\n';
            }
            else
                rec(i + 1);
            used[j] = 0;
        }
}

int main()
{
    cin >> n;
    rec(1);
    return 0;
}