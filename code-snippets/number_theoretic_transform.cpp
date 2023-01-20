#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mod = 998244353;
const int LOG = 22;
const int g = 3;

int pw(int b, int n) {
	int ans = 1;
	while (n > 0) {
		if (n & 1) ans = (ll)ans*b % mod;
		b = (ll)b*b % mod;
		n >>= 1;
	}
	return ans;
}

inline int inv(int n) {
	return pw(n, mod - 2);
}

vector<int> w[LOG], iw[LOG], r[LOG + 1];

void precalc() {
	int root = pw(g, (mod - 1)/(1 << LOG));
	for (int st = 0; st < LOG; ++st) {
		w[st].resize(1 << st);
		iw[st].resize(1 << st);
		int wl = pw(root, 1 << (LOG - st - 1)), iwl = inv(wl);
		int cw = 1, ciw = 1;
		for (int k = 0; k < (1 << st); ++k) {
			w[st][k] = cw;
			iw[st][k] = ciw;
			cw = (ll)cw*wl % mod;
			ciw = (ll)ciw*iwl % mod;
		}
	}
	for (int st = 0; st <= LOG; ++st) {
		r[st].resize(1 << st);
		if (st == 0) {
			r[st][0] = 0;
			continue;
		}
		int h = 1 << (st - 1);
		for (int k = 0; k < (1 << st); k++)
			r[st][k] = (r[st - 1][k & (h - 1)] << 1) | (k >= h);
	}
}

void fft(vector<int>& a, bool invert) {
	int n = a.size(), lg = 0;
	while ((1 << lg) < n) ++lg;
	for (int i = 0; i < n; ++i) {
		if (i < r[lg][i]) swap(a[i], a[r[lg][i]]);
	}
	for (int st = 0; st < lg; ++st) {
		int len = 1 << st;
		for (int i = 0; i < n; i += (len << 1)) {
			for (int j = i; j < i + len; ++j) {
				int u = a[j], v;
				if (invert) v = (ll)iw[st][j - i]*a[j + len] % mod;
				else v = (ll)w[st][j - i]*a[j + len] % mod;
				a[j] = u + v;
				a[j + len] = u - v;
				if (a[j] >= mod) a[j] -= mod;
				if (a[j + len] < 0) a[j + len] += mod;
			}
		}
	}
	if (invert) {
		int inv_n = inv(n);
		for (int i = 0; i < n; ++i) {
			a[i] = (ll)a[i]*inv_n % mod;
		}
	}
}

vector<int> multiply(vector<int> a, vector<int> b) {
	int sz = 1;
	while (sz < int(a.size() + b.size())) 
		sz <<= 1;
	a.resize(sz);
	b.resize(sz);
	fft(a, false);
	fft(b, false);
	vector<int> c(sz);
	for (int i = 0; i < sz; ++i) {
		c[i] = (ll)a[i]*b[i] % mod;
	}
	fft(c, true);
	return c;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    precalc();
    string s;
    cin >> s;
    int n = s.size();
    vector<int> v(n, 0), iv(n, 1);
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'B') v[i] = 1, iv[i] = 0;
    }
    reverse(v.begin(), v.end());
    vector<int> ans = multiply(v, iv);
    for (int i = n; i < 2*n - 1; ++i)
        cout << ans[i] << endl;
}
