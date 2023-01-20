

struct UnionFind {
	vector<int> p, rank;

	UnionFind() {}
	UnionFind(int n) {
		p = rank = vector<int>(n, 0);
		for (int i = 0; i < n; ++i)
			p[i] = i;
	}
	int find(int i) {
		if (p[i] == i)
         return i;
		return p[i] = find(p[i]);
	}
	void join(int i, int j) {
		int x = find(i), y = find(j);
		if (x == y)
         return;
		if (rank[x] == rank[y])
			++rank[y];
		if (rank[x] > rank[y])
			p[y] = x;
		else
			p[x] = y;
	}
   bool equal(int i, int j) {
      return find(i) == find(j);
   }
};

