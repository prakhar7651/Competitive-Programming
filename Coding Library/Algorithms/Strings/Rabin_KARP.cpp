/*
Rabin Karp Algorithm.
Finds occurences of pattern in text using rolling hash values.
Fast but not hundred percent reliable because of collisions.
*/
#include<vector>
#include<climits>
#include<algorithm>
#include <cmath>
#include<map>
#define loop(n) for(int i=0;i<n;i++)
#define temp_input(x) int x;cin>>x;
#define eb emplace_back
#define mp make_pair
#define ll long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
int getVal(char c)
{
    if(c>=65&&c<=90)
        return c-65+26;
    else
        return c-97;
}
ll unsigned int binary_exp_mod_n(ll int a, ll int b, ll int p)
{
    ll unsigned int res = 1;
    while(b)
    {
        if(b&1)
            res = res * a%p;
        a = a*a%p;
        b>>=1;
    }
    return res;
}
ll unsigned int computeHashCode(string s, const int x, const ll int p)
{
    ll unsigned int result = 0;
    for(int i=0;i<s.length();i++)
    {
        result+= ((getVal(s.at(i))) * binary_exp_mod_n(x, i, p)) % p;
        result%=p;
    }
    return (result%p);
}
void preComputeHash(ll unsigned int hash_values[],string* text,int t_len,int p_len,const int x,const ll int p)
{
    const ll int fact = binary_exp_mod_n(x, p_len, p);
    hash_values[t_len - p_len] = computeHashCode(text->substr(t_len - p_len, p_len), x, p);
    for (int i = t_len - p_len - 1; i >= 0; i--) {
        hash_values[i] = (((x * hash_values[i + 1]) % p + getVal(text->at(i)) - (fact * getVal(text->at(i + p_len))) % p % p) + p) % p;
    }

}
vector<int> patterns_in_text(string*text,string * pattern,const int x,const ll int p)//x = 31 p = 1000000007 for most cases
{
    vector<int> result;
    int p_len = pattern->length();
    int t_len = text->length();
    ll unsigned int hash_values[t_len - p_len + 1];
    preComputeHash(hash_values,text,t_len,p_len,x,p);
    ll unsigned p_hash = computeHashCode(*pattern, x, p);
    for (int i = 0; i <= text->length() - p_len; i++) {
        if (hash_values[i] == p_hash) {
            if (text->substr(i, p_len) == (*pattern))
                result.eb(i);

        }
    }
    return result;
}