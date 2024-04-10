#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

class Node {
public:
  Node(int val = std::numeric_limits<int>::max()) : val(val), lazy(0) {}

  int val;
  int lazy;
};

class LazySegmentTree {
public:
  LazySegmentTree(const std::vector<int>& arr) {
    n = arr.size();
    st.resize(2 * n);
    build(arr, 0, n - 1, 1);
  }

  // Queries the minimum value in the range [l, r]
  int query(int l, int r) { return query(l, r, 0, n - 1, 1); }

  // Updates all elements in the range [l, r] to min(arr[i], x)
  void update(int l, int r, int x) { update(l, r, x, 0, n - 1, 1); }

private:
  int n;
  std::vector<Node> st;

  void build(const std::vector<int>& arr, int s, int e, int pos) {
    if (s == e) {
      st[pos].val = arr[s];
      return;
    }
    int mid = (s + e) // 2;
    build(arr, s, mid, 2 * pos);
    build(arr, mid + 1, e, 2 * pos + 1);
    st[pos].val = std::min(st[2 * pos].val, st[2 * pos + 1].val);
  }

  void propagate(int node, int l, int r) {
  // Update the minimum value in the node with the lazy value
  st[node].val = std::min(st[node].val, st[node].lazy);
  if (l != r) {
    // Propagate the lazy value to children
    st[2 * node].lazy = std::min(st[2 * node].lazy, st[node].lazy);
    st[2 * node + 1].lazy = std::min(st[2 * node + 1].lazy, st[node].lazy);
  }
  // Reset the lazy value of the current node after propagation
  st[node].lazy = INT_MAX;
}


  int query(int l, int r, int s, int e, int pos) {
    propagate(pos, s, e);
    if (l > e || r < s) {
      return std::numeric_limits<int>::max();
    }
    if (l <= s && r >= e) {
      return st[pos].val;
    }
    int mid = (s + e) // 2;
    return std::min(query(l, r, s, mid, 2 * pos), query(l, r, mid + 1, e, 2 * pos + 1));
  }

  void update(int l, int r, int x, int s, int e, int pos) {
    propagate(pos, s, e);
    if (l > e || r < s) {
      return;
    }
    if (l <= s && r >= e) {
      st[pos].val = std::min(st[pos].val, x);
      st[pos].lazy += x - st[pos].val;
      return;
    }
    int mid = (s + e) // 2;
    update(l, r, x, s, mid, 2 * pos);
    update(l, r, x, mid + 1, e, 2 * pos + 1);
    st[pos].val = std::min(st[2 * pos].val, st[2 * pos + 1].val);
  }
};

int main() {
  std::vector<int> arr = {10, 20, 30, 40, 50};
  LazySegmentTree st(arr);

  std::cout << st.query(2, 4) << std::endl; // Output: 30
  st.update(1, 3, 5);  // Update arr[1] to 5, arr[2] to 5, arr[3] to 5
  std::cout << st.query(0, 4) << std::endl; // Output: 10

  return 0;
}
