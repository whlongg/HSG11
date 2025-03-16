#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t,n ; cin>>t;
    for (int i=1 ; i<=t ; i++)
    {
        int n; cin>>n;
        //int a[n];int b[n];
        int t;
        set <int> seta ;
        set <int> setb ;
        for (int j=1;j<=n;j++)
        {
            cin>>t; seta.insert(t);
        }
        for (int j=1;j<=n;j++)
        {
            cin>>t; setb.insert(t);
        }

        if (seta.size() >=2 && setb.size() >= 2)
        {
            cout<<"YES"<<"\n";
        }
        else
        {
            if (seta.size() >= 3 || setb.size() >= 3)
            {
                cout<<"YES"<<"\n";
            }
            else cout<<"NO"<<"\n";
        }
    }
}