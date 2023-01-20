// https://codeforces.com/contest/1555/problem/E
// Submitted on Sep/10/2021

#include <bits/stdc++.h>
using namespace std;

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
      int m = (l + r) >> 1;
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
      int m = (l + r) >> 1;
      update(left(x), l, m, ll, rr, val);
      update(right(x), m + 1, r, ll, rr, val);
      tree[x] = merge(tree[left(x)], tree[right(x)], lazy[x]);
   }

   int get(int x, int l, int r, int ll, int rr) {
      if (r < ll or rr < l)
         return E;
      if (ll <= l and r <= rr)
         return tree[x];
      int m = (l + r) >> 1;
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
   int n, m;
   cin >> n >> m;
   vector<tuple<int, int, int>> v(n);
   for (int i = 0; i < n; ++i) {
      int l, r, w;
      cin >> l >> r >> w;
      --l, --r;
      --r;
      v[i] = {w, l, r};
   }
   sort(v.begin(), v.end());
   SegTree tree(vector<int>(m - 1, 0));
   int ans = 1e9;
   int i = 0, j = 0;
   for (;;) {
      while (j < n and tree.get(0, m - 2) == 0) {
         auto [ignore, l, r] = v[j];
         tree.update(l, r, 1);
         ++j;
      }
      if (tree.get(0, m - 2) == 0)
         break;
      do {
         ans = min(ans, get<0>(v[j - 1]) - get<0>(v[i]));
         auto [ignore, l, r] = v[i];
         tree.update(l, r, -1);
         ++i;
      } while (tree.get(0, m - 2) > 0);
      if (j == n)
         break;
   }
   cout << ans << '\n';
}
