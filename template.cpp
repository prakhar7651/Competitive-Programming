#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define mp make_pair
#define ll long long
#define ull unsigned ll
#define rep(i,n) for(int i = 0;i<n;i++)
#define REP(i,k,n) for(int i=k;i<n;i++)
#define sz(x) ((int)x.size())
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define b_search binary_search
#define largest *max_element
#define smallest *min_element
#define all(x) x.begin(),x.end()
#define clr(x) memset(x,0,sizeof(x))
#define PI 3.1415926535897932384626
ll int GIF(ll a,ll b){return a/b+(a%b!=0);}
vector<ull int> Factorize(ull int n){vector<ull int>result;int i=2;while(i*i<=n){while(n%i==0)result.eb(i),n/=i;i++;}if(n)result.eb(n);return result;}
ll unsigned int bin_exp(ll int a,ll int b){ll unsigned result = 1;while(b){if(b&1)result*=a;a*=a;b>>=1;}return result;}
mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
int rng(int lim) {uniform_int_distribution<int> uid(0,lim-1);return uid(rang);}
const int mod = 1'000'000'007; //1e9+7
const int N = 1e5+5;
void solve()
{
       
}
int32_t main()
{
    IOS;
    //freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    int tc = 1;
    cin >> tc;
    while(tc--)
    {
        solve();
    }
    return 0;
}