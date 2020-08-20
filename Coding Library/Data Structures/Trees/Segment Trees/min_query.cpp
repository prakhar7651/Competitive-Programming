#include<vector>
#include<climits>

using namespace std;

struct SegTree{
  int size;
  vector<int>arr;
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
    arr[x] =  min(arr[2*x+1],arr[2*x+2]);
  }
  int getMin(int l,int r,int low,int high,int x)
  {
    if(low<=l && (r-1) <= high)
      return arr[x];
    if(l > high || (r-1) < low)
      return INT_MAX;
    int m = l + (r-l)/2;
    return min(getMin(l,m,low,high,2*x+1),getMin(m,r,low,high,2*x+2));
  }
  void update(int i,int new_val,int l,int r,int x)
  {
    if ( i < l || i >= r)
      return;
    if(i>=l && i < r)
      {
        if(l == (r-1))
          {
            arr[x] = new_val;
            return;
          }
        int m = l + ((r-l)>>1);
        if(i < m)
          update(i,new_val,l,m,2*x+1);
        else update(i,new_val,m,r,2*x+2);
        arr[x]  = min(arr[2*x+1],arr[2*x+2]);
      }
  }
};