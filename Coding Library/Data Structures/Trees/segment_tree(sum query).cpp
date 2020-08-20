#include<bits/stdc++.h>

using namespace std;

struct SegTree{
  int size;
  vector<long long>arr;
  SegTree(int n)
  {
    size = 1;
    while(size <= n)size <<= 1;
    size <<= 1;
    arr.assign(size,0);   
  }
  void fill(int* a,int x,int l,int r)
  {
    if(l==(r-1))
    {
      arr[x] = *(a+l);
      return;
    }
    int m = l + (r-l)/2;
    fill(a,2*x+1,l,m);
    fill(a,2*x+2,m,r);
    arr[x] = arr[2*x+1] + arr[2*x+2];
  }
  long long getSum(int l,int r,int low,int high,int x)
  {
    if(low<=l && (r-1) <= high)
      return arr[x];
    if(l > high || (r-1) < low)
      return 0;
    int m = l + (r-l)/2;
    return getSum(l,m,low,high,2*x+1) + getSum(m,r,low,high,2*x+2);
  }
  void update(int i,int del,int l,int r,int x)
  {
    if ( i < l || i >= r)
      return;
    if(i>=l && i < r)
      {
        arr[x] += del;
        if(l == (r-1))
          return;
        int m = l + ((r-l)>>1);
        if(i < m)
          update(i,del,l,m,2*x+1);
        else update(i,del,m,r,2*x+2);
      }
  }
};
int main()
{
  freopen("input.txt","r",stdin);
  int n,m;
  cin>>n>>m;
  int a[n];
  for (int i = 0; i < n; i++)
  {
    cin>>a[i];
  }
  SegTree stt(n);
  cout<<"\n";
  stt.fill(a,0,0,n);
  for (int i = 0; i < m; i++)
  {
    int op,l,r;
    cin>>op>>l>>r;
    if(op == 1)
    {
      stt.update(l,r-a[l],0,n,0);
      a[l]=r;
    }else
    {
      cout<<stt.getSum(0,n,l,r-1,0)<<"\n";
    }
    
  }
  
}