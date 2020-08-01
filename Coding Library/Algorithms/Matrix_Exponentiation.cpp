#include <vector>
using namespace std;
const long long mod = 1e9+7;
struct Matrix
{
    int size;
    vector<vector<long long int>>a;
    public:
    Matrix(int SIZE)
    {
        size = SIZE;
        a = vector<vector<long long int>>(size,vector<long long int>(size));
    }
    Matrix operator*(const Matrix& other)
    {
        Matrix product(size);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    product.a[i][j] = (product.a[i][j] + other.a[i][k]*a[k][j])%mod;
                }
                
            }
            
        }
        return product;
    }
};
Matrix mat_expo(Matrix a,long long int n)
{
    Matrix result(a.size);
    for (int i = 0; i < a.size; i++)
    {
        result.a[i][i] = 1;
    }
    while(n)
    {
        if(n&1)result = result * a;
        a = a*a;
        n>>=1;
    }
    return result;
}
