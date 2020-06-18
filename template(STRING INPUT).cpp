#include<bits/stdc++.h>
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
using namespace std;
ll int Min(ll a,ll b){return a<b?a:b;}
ll int Max(ll a,ll b){return a>b?a:b;}
ll int Abs(ll a){ return a<0?-a:a;}
ll int GIF(ll a,ll b){return a/b+(a%b!=0);}
template<typename T> void scan(T &x)
{
    x = 0;
    bool neg = 0;
    register T c = getchar();

    if (c == '-')
        neg = 1, c = getchar();

    while ((c < 48) || (c > 57))
        c = getchar();

    for ( ; c < 48||c > 57 ; c = getchar());

    for ( ; c > 47 && c < 58; c = getchar() )
        x= (x << 3) + ( x << 1 ) + ( c & 15 );

    if (neg) x *= -1;
}
template<typename T>void scan(T&x,T&y){scan(x);scan(y);}
template<typename T>void scan(T&x,T&y,T&z){scan(x,y);scan(z);}
template<typename T>void print(T n)
{
    bool neg = 0;

    if (n < 0)
        n *= -1, neg = 1;

    char snum[65];
    int i = 0;
    do
    {
        snum[i++] = n % 10 + '0';
        n /= 10;
    }

    while (n);
    --i;

    if (neg)
        putchar('-');

    while (i >= 0)
        putchar(snum[i--]);
    putchar(' ');
}
template<typename T>void print(T n,T m){print(n);print(m);};
template<typename T> void println(T n)

{
    bool neg = 0;

    if (n < 0)
        n *= -1, neg = 1;

    char snum[65];
    int i = 0;
    do
    {
        snum[i++] = n % 10 + '0';
        n /= 10;
    }

    while (n);
    --i;

    if (neg)
        putchar('-');

    while (i >= 0)
        putchar(snum[i--]);

    putchar('\n');
}
template<typename T>void println(T n,T m){print(n);println(m);}
void solve()
{

}
int32_t main()

{
    IOS;
    //freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
    int tc = 1;
    cin>>tc;
    while(tc--)
    {
        solve();
    }
    return 0;
}