#include<vector>
#include<iostream>
using namespace std;
struct SegmentTree
{
    int size;
    vector<int>arr;
    vector<int>tree;
    SegmentTree(int n)
    {
        size = n;
        arr = decltype(arr)(n);
        tree = decltype(tree)(4*n);
    }
    void ip_array()
    {
        for (int i = 0; i < size; i++)
        {
            cin>>arr[i];
        }

    }
    void build(int v,int tl,int tr)
    {
        if(tl==tr)
            tree[v] = arr[tl];
        else
        {
            int tm = (tl+tr)>>1;
            build(2*v+1,tl,tm);
            build(2*v+2,tm+1,tr);
            tree[v] = tree[2*v+1]+tree[2*v+2];
        }
    }
    int sum(int v,int tl,int tr,int l,int r)
    {
        if(l>r)
            return 0;
        if((l==tl)&&(r==tr))
            return tree[v];
        else
        {
            int tm = (tl+tr)>>1;
            return sum(v*2+1,tl,tm,l,min(r,tm)) + sum(v*2+2,tm+1,tr,max(l,tm+1),r);
        }
    }
    void update(int v,int tl,int tr,int pos,int new_Val)
    {
        if(tl==tr)
            tree[v] = new_Val;
        else
        {
            int tm = (tl+tr)>>1;
            if(tm>=pos)
                update(2*v+1,tl,tm,pos,new_Val);
            else
                update(2*v+2,tm+1,tr,pos,new_Val);
            tree[v] = tree[2*v+1]+tree[2*v+2];
        }

    }
};