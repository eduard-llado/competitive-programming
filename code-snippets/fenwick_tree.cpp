

class FenwickTree {

private:

   int n;
   vector<int> ft;

   int get(int r) {
      int sum = 0;
      while (r >= 0) {
         sum += ft[r];
         r = (r & (r + 1)) - 1;
      }
      return sum;
   }

public:

   FenwickTree(int n) : n(n) {
      ft.assign(n, 0);
   }

   FenwickTree(const vector<int>& a) : n(a.size()) {
      ft.assign(n, 0);

      ft[0] = a[0];
      for (int i = 1; i < n; ++i)
         ft[i] = ft[i - 1] + a[i];

      for (int i = (int)a.size() - 1; i; --i) {
         int li = (i & (i + 1)) - 1;
         if (li >= 0)
            ft[i] -= ft[li];
      }
   }

   int get(int l, int r) {
      return get(r) - get(l - 1);
   }

   int update(int i, int delta) {
      while (i < n) {
         ft[i] += delta;
         i |= i + 1;
      }
   }

}