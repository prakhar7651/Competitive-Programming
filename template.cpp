#include<bits/stdc++.h>
#include<random>
#include<chrono>
using namespace std;
#define eb emplace_back
#define mp make_pair
#define ll long long
#define ull unsigned ll
#define rep(i,n) for(int i = 0;i<n;i++)
#define REP(i,k,n) for(int i=k;k<n?i<n:i>n;k<n?i++:i--)
#define sz(x) ((int)x.size())
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define b_search binary_search
#define largest *max_element
#define smallest *min_element
#define all(x) x.begin(),x.end()
#define PI 3.1415926535897932384626
ll int Min(ll a,ll b){return a<b?a:b;}
ll int Max(ll a,ll b){return a>b?a:b;}
ll int Abs(ll a){ return a<0?-a:a;}
ll int GIF(ll a,ll b){return a/b+(a%b!=0);}
mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
int rng(int lim) {
	uniform_int_distribution<int> uid(0,lim-1);
	return uid(rang);
}
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
