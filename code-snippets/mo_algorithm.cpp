#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int K = 447, MAX = 1e6 + 10;

struct query {
	int idx, l, r;
	bool operator<(const query& other) const {
		return r < other.r;
	}
};

ll res = 0;
int cur[MAX];

void add(int v) {
	int &cnt = cur[v];
	res += (ll)v*(2*cnt + 1);
	++cnt;
}

void del(int v) {
	int &cnt = cur[v];
	res -= (ll)v*(2*cnt - 1);
	--cnt;
}

int main() {
	int n, t;
	cin >> n >> t;
	vector<int> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	vector<vector<query>> blocks(n/K + 2);
	for (int i = 0; i < t; ++i) {
		int l, r;
		cin >> l >> r;
		--l, --r;
		blocks[l/K].push_back(query{i, l, r});
	}
	vector<ll> ans(t);
	int l = 0, r = -1;
	for (int i = 0; i <= n/K; ++i) {
		vector<query> &block = blocks[i];
		if (i & 1)  sort(block.rbegin(), block.rend());
		else sort(block.begin(), block.end());
		for (query& q: block) {
			while (r < q.r) {
				++r;
				add(a[r]);
			}
			while (r > q.r) {
				del(a[r]);
				--r;
			}
			while (l < q.l) {
				del(a[l]);
				++l;
			}
			while (l > q.l) {
				--l;
				add(a[l]);
			}
			ans[q.idx] = res;
		}
	}
	for (int i = 0; i < t; ++i)
		cout << ans[i] << '\n';
}
