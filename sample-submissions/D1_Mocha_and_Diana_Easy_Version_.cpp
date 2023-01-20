// https://codeforces.com/contest/1559/problem/D1
// Submitted on Sep/08/2021

#include <bits/stdc++.h>
using namespace std;

struct UF {
	vector<int> p, rank;

	UF() {}
	UF(int n) {
		p = rank = vector<int>(n, 0);
		for (int i = 0; i < n; ++i)
			p[i] = i;
	}
	int find(int i) {
		if (p[i] == i) return i;
		return p[i] = find(p[i]);
	}
	void join(int i, int j) {
		int x = find(i), y = find(j);
		if (x == y) return;
		if (rank[x] == rank[y])
			++rank[y];
		if (rank[x] > rank[y]) {
			p[y] = x;
		}
		else {
			p[x] = y;
		}
	}
   bool equal(int i, int j) {
      return find(i) == find(j);
   }
};

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   int n, m1, m2;
   cin >> n >> m1 >> m2;
   UF uf1(n), uf2(n);
   for (int i = 0; i < m1; ++i) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      uf1.join(u, v);
   }
   for (int i = 0; i < m2; ++i) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      uf2.join(u, v);
   }
   vector<pair<int, int>> ans;
   if (m1 > m2)
      for (int i = 1; i < n; ++i) {
         int f1 = uf1.find(0), f2 = uf1.find(i);
         if (f1 == f2)
            continue;
         vector<int> a, b;
         for (int j = 0; j < n; ++j)
            if (uf1.find(j) == f1)
               a.push_back(j);
            else if (uf1.find(j) == f2)
               b.push_back(j);
         int g = 0;
         for (int j: a) {
            if (g) break;
            for (int k: b) {
               if (!uf2.equal(j, k)) {
                  ans.emplace_back(j, k);
                  uf1.join(j, k);
                  uf2.join(j, k);
                  g = 1;
                  break;
               }
            }
         }
      }
   else
      for (int i = 1; i < n; ++i) {
         int f1 = uf2.find(0), f2 = uf2.find(i);
         if (f1 == f2)
            continue;
         vector<int> a, b;
         for (int j = 0; j < n; ++j)
            if (uf2.find(j) == f1)
               a.push_back(j);
            else if (uf2.find(j) == f2)
               b.push_back(j);
         int g = 0;
         for (int j: a) {
            if (g) break;
            for (int k: b) {
               if (!uf1.equal(j, k)) {
                  ans.emplace_back(j, k);
                  uf1.join(j, k);
                  uf2.join(j, k);
                  g = 1;
                  break;
               }
            }
         }
      }
   cout << ans.size() << "\n";
   for (auto [u, v]: ans)
      cout << u + 1 << " " << v + 1 << "\n";
}
