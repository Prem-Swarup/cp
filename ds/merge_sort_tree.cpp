#include<bits/stdc++.h>
using namespace std;

#define ll long long


template<typename T, typename treeType>
class MergeSortTree {
private:
    std::vector<std::vector<treeType>> tree;
    int n;

    void build(const std::vector<treeType>& arr, int node, int start, int end) {
        if (start == end) {
            
            tree[node] = {arr[start]};
        } else {
            int mid = (start + end) / 2;
            
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            
            tree[node].resize(tree[2 * node + 1].size() + tree[2 * node + 2].size());
            std::merge(tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
                       tree[2 * node + 2].begin(), tree[2 * node + 2].end(),
                       tree[node].begin());
        }
    }

public:
    MergeSortTree(const std::vector<treeType>& arr) {
        n = arr.size();
        tree.resize(4 * n); 
        build(arr, 0, 0, n - 1);
    }

    T queryUtil(int pos, treeType x, treeType y) {
        return std::lower_bound(tree[pos].begin(), tree[pos].end(), y + 1) -
                   std::lower_bound(tree[pos].begin(), tree[pos].end(), x);
    }

    T query(int node, int start, int end, int l, int r, treeType x, treeType y) {
        if (start > r || end < l) {
            return 0;
        }
        if (start >= l && end <= r) {
            return queryUtil(node, x, y);
        }
        int mid = (start + end) / 2;
        treeType left_query = query(2 * node + 1, start, mid, l, r, x, y);
        treeType right_query = query(2 * node + 2, mid + 1, end, l, r, x, y);
        return left_query + right_query;
    }

    T query(int l, int r, treeType x, treeType y) {
        return query(0, 0, n - 1, l, r, x, y);
    }

    void clear() {
        tree.clear();
    }
};


//example usage
void solve() {
    int n, q;
    cin>>n>>q;
    vector<int> arr(n);
    for(auto &x:arr) cin>>x;

    MergeSortTree<int, int> tree(arr);

    for(int i=0; i<q; ++i) {
        int l, r, x, y;
        cin>>l>>r>>x>>y;
        cout<<tree.query(l,r,x,y)<<endl;
    }

    return;
}


signed main() {
  int t;
  cin>>t;
  while(t--) {
    solve();
  }
  
  return 0;
}
