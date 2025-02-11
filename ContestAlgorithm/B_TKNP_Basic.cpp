#include <bits/stdc++.h>
using namespace std;

int lower_bound_tknp(int left, int right, int target, int a[]){
    int ans = -2;
    while(left <= right){
        int mid = ((left+right)>>1);
        if (a[mid]== target){
            ans = mid;
            right = mid-1;
        }  
        if(a[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return ans;
}

int upper_bound_tknp(int left, int right, int target, int a[]){
    int ans = -2;
    while (left <= right){
        int mid = ((left+right) >> 1);
        if (a[mid]==target){
            ans = mid;
            left=mid+1;
        }
        else if( a[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return ans;
}


void solve(int n, int a[]){
    int t, x;
    cin >> t >> x;
    if(t == 1){
        cout << ((lower_bound_tknp(0, n-1, x, a) != -2)?"YES\n":"-1\n");
    }
    else if(t == 2)
        cout << lower_bound_tknp(0,n-1,x,a)+1 << '\n';
    else 
        cout << upper_bound_tknp(0,n-1,x,a)+1 << '\n';
    
}

int main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, q;
    cin >> n >> q;
    int a[n];
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    while (q--)
        solve(n, a);
}