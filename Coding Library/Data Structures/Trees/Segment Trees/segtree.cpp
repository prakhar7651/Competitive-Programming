#include <vector>
#include <cstdlib>
#include <cassert>

template<class T> class SegmentTree{
    
    public:
        SegmentTree(std::vector<T> data , T (*combine)(T , T));
        SegmentTree(T data[] , int n , T (*combine)(T obj1 , T obj2));
        T query(int l , int r);
        void update(int idx , T val);

    private:
        T* m_tree;
        int m_n;
        T (*m_combine)(T , T);
        void build(int v , int tl , int tr , T* arr);
        T queryHelper(int v , int tl , int tr , int l , int r);
        void updateHelper(int v , int tl , int tr , int idx , T val);
};

template<class T> SegmentTree<T>::SegmentTree(std::vector<T> data , T (*combine)(T , T))
{
    m_combine = combine;
    m_n = data.size();
    m_tree = (T*)malloc(sizeof(T) * 4 * m_n);
    build(0 , 0 , m_n - 1, data.data());
}

template<class T> SegmentTree<T>::SegmentTree(T* data , int n , T (*combine)(T obj1 , T obj2))
{
    m_combine = combine;
    m_n = n;
    m_tree = (T*)malloc(sizeof(T) * 4 * m_n);
    build(0 , 0 , m_n - 1, data);
}

template<class T> T SegmentTree<T>::query(int l , int r)
{
    return queryHelper(0 , 0 , m_n - 1 , l , r);
}

template<class T> void SegmentTree<T>::update(int idx , T val)
{
    return updateHelper(0 , 0 , m_n - 1 , idx , val);
}

template<class T> void SegmentTree<T>::build(int v , int tl , int tr , T* arr)
{
    if(tl == tr)
    {
        m_tree[v] = arr[tl];
    }
    else
    {
        int tm = tl + (tr - tl) / 2;
        build(2 * v + 1 ,  tl , tm , arr);
        build(2 * v + 2 , tm+1 , tr , arr);
        m_tree[v] = m_combine(m_tree[2*v + 1] , m_tree[2*v + 2]);
    }
    return;
}

template<class T> T SegmentTree<T>::queryHelper(int v , int tl , int tr , int l , int r)
{
    if(l == tl && r == tr)
        return m_tree[v];
    int tm = tl + (tr - tl) / 2;
    if(l <= std::min(tm , tr) && std::max(l , tm + 1) <= r)
        return m_combine(queryHelper(2 * v + 1, tl , tm , l , std::min(tm , r)) , queryHelper(2 * v + 2 , tm + 1 , tr , std::max(l , tm + 1) , r));
    else if(l <= std::min(tm , r))
            return queryHelper(2 * v + 1, tl , tm , l , std::min(tm , r));
        else if(std::max(l , tm + 1) <= r)
            return queryHelper(2 * v + 2 , tm + 1 , tr , std::max(l , tm + 1) , r);
    assert(false);
}

template<class T> void SegmentTree<T>::updateHelper(int v , int tl , int tr , int idx , T val)
{
    if(tl == tr)
    {
        m_tree[v] = val;
    }
    else{
        int tm = tl + (tr - tl) / 2;
        if(idx <= tm)
            updateHelper(2 * v + 1 , tl , tm , idx , val);
        else
            updateHelper(2 * v + 2 , tm + 1 , tr , idx , val);
        m_tree[v] = m_combine(m_tree[2 * v + 1] , m_tree[2 * v + 2]);
    }
    return;
}