/*
Code to get n'th fibonacci number in logarithmic time.
*/
unsigned long long int target[2][2] = {{1,0},{0,1}};
unsigned long long int F[2][2] = {{1,1},{1,0}};
const int mod = 1e9+7;
void multiply1()
{
    auto a = target[0][0],b = target[0][1],c = target[1][0],d = target[1][1];
    target[0][0] = ((a*F[0][0])%mod + (b*F[1][0])%mod)%mod;
    target[0][1] = ((a*F[0][1])%mod + (b*F[1][1])%mod)%mod;
    target[1][0] = ((c*F[0][0])%mod + (d*F[0][1])%mod)%mod;
    target[1][1] = ((c*F[0][1])%mod + (d*F[1][1])%mod)%mod;
}
void multiply2()
{
    auto a = F[0][0],b = F[0][1],c = F[1][0],d = F[1][1];
    F[0][0] = ((a*a)%mod + (b*c)%mod)%mod;
    F[0][1] = ((a*b)%mod + (b*d)%mod)%mod;
    F[1][0] = ((c*a)%mod + (d*c)%mod)%mod;
    F[1][1] = ((c*b)%mod + (d*d)%mod)%mod;  
}
unsigned long long int getFibo(unsigned long long int n)
{
    while(n)
    {
        if(n&1)multiply1();
        multiply2();

        n>>=1;
    }
    return target[0][1];
}