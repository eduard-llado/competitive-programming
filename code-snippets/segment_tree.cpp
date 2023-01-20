#include <bits/stdc++.h>
using namespace std;

// static
// min, sum, gcd ...
template <class T>
class SegTree {
private:
   int n;
   vector<T> tree;

   T merge(T a, T b) {
      return gcd(a, b);
   }

   int right(int x) {
      return x << 1;
   }

   int left(int x) {
      return x << 1 | 1;
   }

   void build(int x, int l, int r, const vector<T>& v) {
      if (l == r) {
         tree[x] = v[l];
         return;
      }
      int m = (l + r) / 2;
      build(right(x), l, m, v);
      build(left(x), m + 1, r, v);
      tree[x] = merge(tree[right(x)], tree[left(x)]);
   }

   T get(int x, int l, int r, int ll, int rr) {
      if (ll <= l and r <= rr)
         return tree[x];
      if (r < ll or rr < l)
         return 0;
      int m = (l + r) / 2;
      return merge(get(left(x), l, m, ll, rr), get(right(x), m + 1, r, ll, rr));
   }

public:
   SegTree(const vector<T>& v) : n(v.size), tree(4 * n) {
      build(1, 0, n - 1, v);
   }

   T get(int l, int r) {
      return get(1, 0, n - 1, l, r);
   }
};


// lazy, no propagation
// updates are sums, queries are min
class SegTree {
private:
   int n;
   const int E = 1e9;  // identity for pull
   vector<int> tree, lazy;

   int merge(int a, int b, int lz=0) {
      return min(a, b) + lz;
   }

   int left(int x) {
      return x << 1;
   }

   int right(int x) {
      return x << 1 | 1;
   }

   void build(int x, int l, int r, const vector<int>& v) {
      if (l == r) {
         tree[x] = v[l];
         return;
      }
      int m = (l + r) / 2;
      build(left(x), l, m, v);
      build(right(x), m + 1, r, v);
      tree[x] = merge(tree[left(x)], tree[right(x)]);
   }

   void update(int x, int l, int r, int ll, int rr, int val) {
      if (r < ll or rr < l)
         return;
      if (ll <= l and r <= rr) {
         tree[x] += val;
         lazy[x] += val;
         return;
      }
      int m = (l + r) / 2;
      update(left(x), l, m, ll, rr, val);
      update(right(x), m + 1, r, ll, rr, val);
      tree[x] = merge(tree[left(x)], tree[right(x)], lazy[x]);
   }

   int get(int x, int l, int r, int ll, int rr) {
      if (r < ll or rr < l)
         return E;
      if (ll <= l and r <= rr)
         return tree[x];
      int m = (l + r) / 2;
      return merge(get(left(x), l, m, ll, rr), get(right(x), m + 1, r, ll, rr), lazy[x]);
   }

public:
   SegTree(const vector<int>& v) : n(v.size()), tree(4 * n), lazy(4 * n, 0) {
      build(1, 0, n - 1, v);
   }

   void update(int l, int r, int val) {
      update(1, 0, n - 1, l, r, val);
   }

   int get(int l, int r) {
      return get(1, 0, n - 1, l, r);
   }
};

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   vector<int> v = {1,2,3,4,5,6,7,8};
   SegTree s(v);
   cout << s.get(0, 7) << endl;
   s.update(0, 7, 5);
   s.update(0, 3, 10);
   cout << s.get(0, 7) << endl;
   cout << s.get(1, 1) << endl;
   cout << s.get(7, 7) << endl;
}