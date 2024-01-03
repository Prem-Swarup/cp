#include<bits/stdc++.h>
using namespace std ;





template<typename T=long long>
T func(T a, T b) {
    return __gcd(a, b) ;
}


template<typename T=long long>
class SegmentTree {
    vector<T> tree;
    int size;
    T mnVal;
 
public:
    SegmentTree(vector<T>& array, T val) {
        size = array.size();
        tree.resize(4 * size);
        mnVal = val;
        buildTree(array, 0, 0, size - 1);
    }
 
private:
    void buildTree(vector<T>& array, int treeIndex, int left, int right) {
        if (left == right) {
            tree[treeIndex] = array[left];
            return;
        }
        int mid = left + (right - left) / 2;
        buildTree(array, 2 * treeIndex + 1, left, mid);
        buildTree(array, 2 * treeIndex + 2, mid + 1, right);
        tree[treeIndex] = func<T>(tree[2 * treeIndex + 1], tree[2 * treeIndex + 2]);
    }
 
    T query(int treeIndex, int left, int right, int queryLeft, int queryRight) {
        if (queryLeft <= left && right <= queryRight)
            return tree[treeIndex];
        int mid = left + (right - left) / 2;
        T value = mnVal ;
        if (queryLeft <= mid)
            value = func<T>(value, query(2 * treeIndex + 1, left, mid, queryLeft, queryRight));
        if (queryRight > mid)
            value = func<T>(value, query(2 * treeIndex + 2, mid + 1, right, queryLeft, queryRight));
        return value;
    }
    T update(int treeIndex, int left, int right, int pos, T val){
        if(left==pos && right==pos) {
            tree[treeIndex] = val ;
            return val;
        }
        int mid = left + (right-left)/2 ;
        T value = mnVal ;
        if(pos<=mid) {
            value = func<T>(value, update(2 * treeIndex + 1, left, mid, pos, val));
            value = func<T>(value, tree[2 * treeIndex + 2]);
        }else {
            value = func<T>(value, update(2 * treeIndex + 2, mid+1, right, pos, val));
            value = func<T>(value, tree[2 * treeIndex + 1]);
        }
        tree[treeIndex] = value ;
        return value ;
    }
 
public:
    T query(int left, int right) {
        return query(0, 0, size - 1, left, right);
    }
    void update(int pos, T val) {
        update(0, 0, size-1, pos, val) ;
    }
};



int main(int argc, char const *argv[])
{
    vector<int> array = {1, 12, 6, 4, 4, 6};
    SegmentTree<int> st(array);
    cout << st.query(1, 5) << endl; 
    cout << st.query(1, 1) << endl;
    cout << st.query(5, 5) << endl; 
    cout << st.query(1, 3) << endl;  
    return 0;
}  
