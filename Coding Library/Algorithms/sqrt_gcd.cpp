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
Sun Jul 11 2021
*/
#include"bits/stdc++.h"
using namespace std;

#define int ll
#ifdef int
#define INF 1000000000000000000 //1e18
#else
#define INF 1000000000  //1e9
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

int n;
int a[N];
int s;
vector<int>blocks;

void sqrt_decompose()
{
    blocks = vector<int>(s , 0);
    for(int i = 0; i < n; i++)
    {
        blocks[i/s] = __gcd(blocks[i/s] , a[i]);
    }
}

int getGCD(int l , int r)
{
    int ans = 0;
    int c_l = l / s , c_r = r / s;
    if(c_l == c_r)
    {
        for(int i = l; i <= r; i++)ans = __gcd(ans , a[i]);
    }
    else{
        for (int i=l, end=(c_l+1)*s-1; i<=end; ++i)
            ans = __gcd(ans , a[i]);
        for (int i=c_l+1; i<=c_r-1; ++i)
            ans = __gcd(ans , blocks[i]);
        for (int i=c_r*s; i<=r; ++i)
            ans = __gcd(ans , a[i]);
    }
    return ans;
}

bool possible(int mid)
{
    int val = getGCD(0 , mid - 1);
    for(int i = 1; i < n; i++)
    {
        if(i + mid - 1 < n)
        {
            if(getGCD(i , i + mid - 1) != val)return false;
        }
        else{
            int end = (i + mid - 1) % n;
            int temp = __gcd(getGCD(i , n-1) , getGCD(0 , end));
            if(temp != val)return false;
        }
        
    }   
    return true;
}

int solve()
{
    cin >> n;
    s = sqrt(n) + 1;
    rep(i,n)cin >> a[i];
    sqrt_decompose();
    int l = 1 , r = n , ans = n;
    while(l <= r)
    {
        int mid = l + (r-l)/2;
        if(possible(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    cout << ans - 1 << "\n";
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