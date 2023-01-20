#include <bits/stdc++.h>
using namespace std;


// Finds index of minimum element in array
// builds in O(nlogn) queries in O(1)
// the other version returns value instead of index
// can use any idempotent operation (min, max, gcd...)
struct sparse {
	int n;
	vector<int> v;
	vector<vector<int>> sp;
	int log2(int num) {
		return 31 - __builtin_clz(num);		
	}
	sparse(const vector<int>& _v) {
		v = _v;
		n = v.size();
		sp = vector<vector<int>>(n, vector<int>(log2(n) + 1, 0));
		for (int i = 0; i < n; ++i)
			sp[i][0] = i;
		for (int j = 1; (1 << j) <= n; ++j) {
			for (int i = 0; i + (1 << j) <= n; ++i) {
				if (v[sp[i][j - 1]] < v[sp[i + (1 << (j - 1))][j - 1]]) {
					sp[i][j] = sp[i][j - 1];
				}
				else {
					sp[i][j] = sp[i + (1 << (j - 1))][j - 1];
				}
			}
		}
	}
	int find(int i, int j) {
		int k = log2(j - i + 1);
		if (v[sp[i][k]] <= v[sp[j - (1 << k) + 1][k]])
			return sp[i][k];
		return sp[j - (1 << k) + 1][k];
	}
};

struct sparse {
	int n;
	vector<vector<int>> sp;

	int log2(int num) {
		return 31 - __builtin_clz(num);		
	}

	sparse(const vector<int>& v) : n(v.size()) {
		sp = vector<vector<int>>(log2(n), vector<int>(n));
		sp[0] = v;
      for (int l = 0; l < log2(n) - 1; ++l)
         for (int i = 0; i + (2 << l) <= n; ++i)
            sp[l + 1][i] = min(sp[l][i], sp[l][i + (1 << l)]);
	}

	int find(int l, int r) {
		int k = log2(r - l);
      return min(sp[l][k], sp[r - (1 << k)][k]);
	}
};

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	sparse sp(v);
	while (1) {
		int a, b;
		cin >> a >> b;
		cout << sp.find(a, b) << endl;
	}
}
