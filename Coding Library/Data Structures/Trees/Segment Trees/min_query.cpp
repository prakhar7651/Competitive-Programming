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
  void fill(int* a,int index,int l,int r)
  {
    if(l==(r-1))
    {
      arr[index] = *(a+l);
      return;
    }
    int m = l + (r-l)/2;
    fill(a,2*index+1,l,m);
    fill(a,2*index+2,m,r);
    arr[index] =  min(arr[2*index+1],arr[2*index+2]);
  }
  int getMin(int l,int r,int low,int high,int index)
  {
    if(low<=l && (r-1) <= high)
      return arr[index];
    if(l > high || (r-1) < low)
      return INT_MAX;
    int m = l + (r-l)/2;
    return min(getMin(l,m,low,high,2*index+1),getMin(m,r,low,high,2*index+2));
  }
  void update(int i,int new_val,int l,int r,int index)
  {
    if ( i < l || i >= r)
      return;
    if(i>=l && i < r)
      {
        if(l == (r-1))
          {
            arr[index] = new_val;
            return;
          }
        int m = l + ((r-l)>>1);
        if(i < m)
          update(i,new_val,l,m,2*index+1);
        else update(i,new_val,m,r,2*index+2);
        arr[index]  = min(arr[2*index+1],arr[2*index+2]);
      }
  }
};