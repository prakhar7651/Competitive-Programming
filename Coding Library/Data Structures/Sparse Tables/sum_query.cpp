#include<algorithm>
#include<iostream>
using namespace std;
struct Sparse_Table{
    public:
            #define MAXN (int)1e3
            long long st[MAXN][26];
            long long fsum(long long  a,long long b)
            {
                return a+b;
            }
            void buildTable(int* array,int N)
            {
                for (int  i = 0; i < N; i++)
                {
                    st[i][0] = *(array+i);
                }
                for (int j = 1 ; j < 26 ; j++)
                {
                    for (int i = 0 ; i + (1<<j) <= N; i++)
                    {
                        st[i][j] = fsum(st[i][j-1],st[i+(1<<(j-1))][j-1]);
                    }
                    
                }
                
            }
            long long int query(int l,int r)
            {
                long long sum = 0;
                for (int  i = 25; i >= 0; i--)
                {
                    if((1<<i)<=(r-l+1)){
                        sum += st[l][i];
                        l += (1<<i);
                    }
                }
                return sum;
            }
};
int main()
{
    int a[10];
    for (int  i = 0; i < 10; i++)
    {
        a[i] = i+1;
    }
    Sparse_Table obj;
    obj.buildTable(a,10);
    cout<<obj.query(0,9);
    return 0;
}