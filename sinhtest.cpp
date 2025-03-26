#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define file(inp, out) freopen((inp), "r", stdin);freopen((out), "w", stdout);
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(nullptr);
const int N = 1000;

int Rand(int l, int r){
    return l + rand() % (r - l + 1);
}

void sinhtest(){    //tuong tac voi file ngoai (inp)
    ofstream cout("testcs.inp");
    int n = Rand(1, N);
    int k = Rand(1, n);
    cout << n << ' ' << k << '\n';
    for(int i = 1; i <= n; ++i)
        cout << Rand(1, N) << ' ';
}

int32_t main(){
    srand(time(0));
    for(int i = 1; i <= 100; i++){
        sinhtest();
        if(i == 10){
            ofstream cout("testcs.inp");
            cout << 4 << ' ' << 2 << ' ' << 0 << ' ' << 0 << ' ' << 0 << ' ' << 0;
        }
        system("./test");
        system("./main");    
        //diff cho macos/linux, fc cho windows
        if(system("diff testcs.out testcs.ans")==0){
            cout << "CORRECT\n";
        }
        else{
            cout << "WRONG\n";
            return 0;
        }
    } 
}