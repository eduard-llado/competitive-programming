#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;

struct pt {
   int x, y;
   bool operator<(const pt& p) {
      return x < p.x or (x == p.x and y < p.y);
   }
   pt() {}
   pt(int _x, int _y) : x(_x), y(_y) {}
};

bool ccw(const pt& O, const pt& a, const pt& b) {
   return (ll)(a.x - O.x)*(b.y - O.y) <= (ll)(a.y - O.y)*(b.x - O.x);
}

vector<pt> CH(vector<pt> P) {
   int n = P.size(), k = 0;
   if (n <= 3) return P;
   vector<pt> H(2*n);
   sort(P.begin(), P.end());
   for (int i = 0; i < n; ++i) {
      while (k >= 2 and ccw(H[k - 2], H[k - 1], P[i]))
         --k;
      H[k++] = P[i];
   }
   for (int i = n - 2, t = k + 1; i >= 0; --i) {
      while (k >= t and ccw(H[k - 2], H[k - 1], P[i]))
         --k;
      H[k++] = P[i];
   }
   H.resize(k - 1);
   return H;
}

int main() {
   int n;
   cin >> n;
   vector<pt> p(n);
   for (int i = 0; i < n; ++i) {
      int x, y;
      cin >> x >> y;
      p[i] = pt(x, y);
   }
   p = CH(p);
   for (int i = 0; i < p.size(); ++i)
      cout << p[i].x << ' ' << p[i].y << endl;
}
