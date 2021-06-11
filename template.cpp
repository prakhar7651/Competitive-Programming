/*
 
                       _oo0oo_ 
                      o8888888o 
                      88" . "88 
                      (| -_- |) 
                      0\  =  /0 
                    ___/`---'\___ 
                  .' \\|     |// '. 
                 / \\|||  :  |||// \ 
                / _||||| -:- |||||- \ 
               |   | \\\  -  /// |   | 
               | \_|  ''\---/''  |_/ | 
               \  .-\__  '-'  ___/-. / 
             ___'. .'  /--.--\  `. .'___ 
          ."" '<  `.___\_<|>_/___.' >' "". 
         | | :  `- \`.;`\ _ /`;.`/ - ` : | | 
         \  \ `_.   \_ __\ /__ _/   .-` /  / 
     =====`-.____`.___ \_____/___.-`___.-'===== 
                       `=---=' 
keep calm and don't hurt the computer.
created by -> prakhar
Fri Jun 11 2021
*/
#include"bits/stdc++.h"
using namespace std;

#define int ll
#ifdef int
#define INF LLONG_MAX
#define negINF LLONG_MIN
#else
#define INF INT_MAX
#define negINF INT_MIN
#endif

#define ll long long
#define ull unsigned ll
#define REP(i,k,n) for(int i=k;i<n;i++)
#define rep(i,n) REP(i,0,n)
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define clr(x) memset(x,0,sizeof(x))
#define PI 3.1415926535897932384626
map<int,int> Factorize(int n){map<int,int> result;int i=2;while(i*i<=n){while(n%i==0)result[i]++,n/=i;i++;}if(n>1)result[n]++;return result;}
int bin_exp(int a,int b){int result = 1;while(b){if(b&1)result*=a;a*=a;b>>=1;}return result;}
const int mod = 1'000'000'007; //1e9+7
const int N = 2e5+5;

int solve()
{
    return 0;
}
int32_t main()
{
    cin.tie(nullptr) -> sync_with_stdio(false);
    //freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
    int tc = 1;
    cin >> tc;
    while(tc--)
    {
        solve();
    }
    return 0;
}