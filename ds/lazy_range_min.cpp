#include <bits/stdc++.h>
using namespace std;


template<typename T=long long>
T comp(T a, T b) {
  
  return min(a, b);
}

template<typename T=long long>
class LazySegmentTree {
public:
  LazySegmentTree(const std::vector<T>& arr, T initl) {
    n = arr.size();
    tree.resize(3 * n);
    lazy.resize(3 * n);
    initial = initl; 
    
    build(arr, 0, n - 1, 1);
  }

  // Queries the minimum value in the range [l, r]
  T query(int l, int r) { return query(l, r, 0, n - 1, 1); }

  // Updates all elements in the range [l, r] to min(arr[i], x)
  void update(int l, int r, int x) { update(l, r, x, 0, n - 1, 1); }
  void print() {
    for(auto x:tree) cout<<x<<' ';
    cout<<endl;
  }
private:
  int n;
  vector<T> tree, lazy;
  T initial;

  void build(const std::vector<T>& arr, int s, int e, int pos) {
    if (s == e) {
      tree[pos] = arr[s];
      lazy[pos] = initial;
      return;
    }
    int mid = (s + e) / 2;
    build(arr, s, mid, 2 * pos);
    build(arr, mid + 1, e, 2 * pos + 1);
    tree[pos] = comp(tree[2 * pos], tree[2 * pos + 1]);
    lazy[pos] = initial;
  }

  void propagate(int node, int l, int r) {
    // Update the minimum value in the node with the lazy value
    tree[node] = comp(tree[node], lazy[node]);
    if (l != r) {
      // Propagate the lazy value to children
      lazy[2*node] = comp(lazy[2*node], lazy[node]);
      lazy[2*node+1] = comp(lazy[2*node+1], lazy[node]);
    }
    // Reset the lazy value of the current node after propagation
    lazy[node] = initial;
  }


  T query(int l, int r, int s, int e, int pos) {
    if(lazy[pos]!=initial) 
      propagate(pos, s, e);
    if (l > e || r < s) {
      return initial;
    }
    if (l <= s && r >= e) {
      return tree[pos];
    }
    int mid = (s + e) / 2;
    return comp(query(l, r, s, mid, 2 * pos), query(l, r, mid + 1, e, 2 * pos + 1));
  }

  void update(int l, int r, T x, int s, int e, int pos) {
    if(lazy[pos]!=initial) 
      propagate(pos, s, e);
    if (l > e || r < s) {
      return;
    }
    if (l <= s && r >= e) {
      tree[pos] = comp(tree[pos], x);
      lazy[pos] = comp(lazy[pos], x);
      return;
    }
    int mid = (s + e) / 2;
    update(l, r, x, s, mid, 2 * pos);
    update(l, r, x, mid + 1, e, 2 * pos + 1);
    tree[pos] = comp(tree[2*pos], tree[2*pos+1]);
  }
};

void test() {
  int n;
  cin>>n;
  vector<long long> arr(n);
  for(int i=0; i<n; ++i)cin>>arr[i];
  int q;cin>>q;
  int x, l, r, type;
  LazySegmentTree tree(arr, (long long)(INT_MAX));
  // tree.print();cout<<endl;
  for(int i=0; i<q; ++i) {
    cin>>type;
    // cout<<i<<"i\n";
    if(type) {
      cin>>l>>r>>x;
      tree.update(l, r, x);
      // tree.print(); cout<<endl;
    } else {
      cin>>l>>r;
      cout<<tree.query(l, r)<<endl;
    }
  }


  return;
}
int main() {
  // std::vector<int> arr = {10, 20, 30, 40, 50};
  // LazySegmentTree st(arr);

  // std::cout << st.query(2, 4) << std::endl; // Output: 30
  // st.update(1, 3, 5);  // Update arr[1] to 5, arr[2] to 5, arr[3] to 5
  // std::cout << st.query(0, 4) << std::endl; // Output: 10
  test();
  return 0;
}
