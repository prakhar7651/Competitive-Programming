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

// To store segment tree
int *st;
  
  
/*  A recursive function to get gcd of given
    range of array indexes. The following are parameters for
    this function.
  
    st    --> Pointer to segment tree
    si --> Index of current node in the segment tree. Initially
               0 is passed as root is always at index 0
    ss & se  --> Starting and ending indexes of the segment
                 represented by current node, i.e., st[index]
    qs & qe  --> Starting and ending indexes of query range */
int findGcd(int ss, int se, int qs, int qe, int si)
{
    if (ss>qe || se < qs)
        return 0;
    if (qs<=ss && qe>=se)
        return st[si];
    int mid = ss+(se-ss)/2;
    return __gcd(findGcd(ss, mid, qs, qe, si*2+1),
               findGcd(mid+1, se, qs, qe, si*2+2));
}
  
//Finding The gcd of given Range
int findRangeGcd(int ss, int se, int arr[],int n)
{
    if (ss<0 || se > n-1 || ss>se)
    {
        assert(false);
    }
    return findGcd(0, n-1, ss, se, 0);
}
  
// A recursive function that constructs Segment Tree for
// array[ss..se]. si is index of current node in segment
// tree st
int constructST(int arr[], int ss, int se, int si)
{
    if (ss==se)
    {
        st[si] = arr[ss];
        return st[si];
    }
    int mid = ss+(se-ss)/2;
    st[si] = __gcd(constructST(arr, ss, mid, si*2+1),
                 constructST(arr, mid+1, se, si*2+2));
    return st[si];
}
  
/* Function to construct segment tree from given array.
   This function allocates memory for segment tree and
   calls constructSTUtil() to fill the allocated memory */
int *constructSegmentTree(int arr[], int n)
{
   int height = (int)(ceil(log2(n)));
   int size = 2*(int)pow(2, height)-1;
   st = new int[size];
   constructST(arr, 0, n-1, 0);
   return st;
}

bool possible(int mid)
{
    int val = findRangeGcd(0 , mid - 1 , a , n);
    for(int i = 1; i < n; i++)
    {
        if(i + mid - 1 < n)
        {
            if(findRangeGcd(i , i + mid - 1 , a , n) != val)return false;
        }
        else{
            int end = (i + mid - 1) % n;
            int temp = __gcd(findRangeGcd(i , n-1 , a , n) , findRangeGcd(0 , end , a , n));
            if(temp != val)return false;
        }
        
    }   
    return true;
}

int solve()
{
    cin >> n;
    rep(i,n)cin >> a[i];
    constructSegmentTree(a , n);
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