#include  <bits/stdc++.h>

class SegTree{
    int n;
    int* segtree;
    int (*fun)(int , int);

    public:
    SegTree(std::vector<int>arr , int(*_fun)(int , int))
    {
        n = (int)arr.size();
        segtree = (int*)malloc(sizeof(int) * 4 * n);
        fun = _fun;
        build(0 , 0 , n-1 , arr.data());
    }
    SegTree(int* arr , int size , int(*_fun)(int , int))
    {
        n = size;
        segtree = (int*)malloc(sizeof(int) * 4 * n);
        fun = _fun;
        build(0 , 0 , n-1 , arr);
    }

    ///@param vertex Default value 0
    ///@param segStart Default value 0
    ///@param segEnd Default value n-1
    void build(int vertex , int segStart , int segEnd , int* arr)
    {
        if(segStart == segEnd)
        {
            segtree[vertex] = arr[segStart];
        }
        else
        {
            int segMid = segStart + (segEnd - segStart) / 2;
            build(2 * vertex + 1 , segStart , segMid , arr);
            build(2 * vertex + 2 , segMid + 1 , segEnd , arr);
            segtree[vertex] = fun(segtree[2 * vertex + 1] , segtree[2 * vertex + 2]);
        }
        return;
    }
    
    ///@param vertex Default value 0
    ///@param segStart Default value 0
    ///@param segEnd Default value n-1
    void update(int vertex , int segStart , int segEnd , int pos , int newVal)
    {
        if(segStart == segEnd)
        {
            segtree[vertex] = newVal;
            return;
        }
        else
        {
            int segMid = segStart + (segEnd - segStart) / 2;
            if(pos <= segMid)
                update(2 * vertex + 1 , segStart , segMid , pos , newVal);
            else
                update(2 * vertex + 2 , segMid + 1 , segEnd , pos , newVal);
            segtree[vertex] = fun(segtree[2 * vertex + 1] , segtree[2 * vertex + 2]);
            return;
        }
    }

    ///@param vertex Default value 0
    ///@param segStart Default value 0
    ///@param segEnd Default value n-1
    int eval(int vertex , int segStart , int segEnd , int left , int right)
    {
        if(left > right)
            return 0;
        if(left == segStart && right == segEnd)
            return segtree[vertex];
        int segMid = segStart + (segEnd - segStart) / 2;
        return fun(
            eval(2 * vertex + 1 , segStart , segMid , left , std::min(right , segMid)) ,
            eval(2 * vertex + 2 , segMid + 1 , segEnd , std::max(left , segMid + 1) , right));
    }

};