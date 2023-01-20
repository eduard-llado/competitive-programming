// https://jutge.org/problems/P21214_en
// Submitted on 2019-06-24, was part of a UPC contest but I solved it later at my leisure. Was first person to solve

#include <bits/stdc++.h>
using namespace std;

// https://cp-algorithms.com/string/aho_corasick.html
const int K = 26;

struct Vertex {
    int next[K];
    int leaf = -1;
    int p = -1;
    char pch;
    int link = -1;
    int leaf_link = -1;
    int go[K];

    Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

vector<Vertex> t(1);

int cnt = 0;
void add_string(string const& s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (t[v].next[c] == -1) {
            t[v].next[c] = t.size();
            t.emplace_back(v, ch);
        }
        v = t[v].next[c];
    }
    t[v].leaf = cnt++;
}

int go(int v, char ch);

int get_link(int v) {
    if (t[v].link == -1) {
        if (v == 0 || t[v].p == 0)
            t[v].link = 0;
        else
            t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
}

int go(int v, char ch) {
    int c = ch - 'a';
    if (t[v].go[c] == -1) {
        if (t[v].next[c] != -1)
            t[v].go[c] = t[v].next[c];
        else
            t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
    }
    return t[v].go[c];
}

int get_leaf_link(int v) {
	if (t[v].leaf_link == -1) {
		if (v == 0)
			t[v].leaf_link = 0;
		else {
			int p = get_link(v);
			if (t[p].leaf != -1)
				t[v].leaf_link = p;
			else t[v].leaf_link = get_leaf_link(p);
		}
	}
	return t[v].leaf_link;
}

int main() {
	int n;
	cin >> n;
	vector<string> w(n);
	for (int i = 0; i < n; ++i) {
		cin >> w[i];
		add_string(w[i]);
	}
	int m;
	cin >> m;
	string line;
	getline(cin, line);
	while (m--) {
		getline(cin, line);
		int cur = 0, wh = 0, is = 0;
		vector<pair<int, int>> ans(line.size(), {-1, 0});
		for (int i = (int)line.size() - 1; i >= 0; --i) {
			char c = line[i];
			if (c != '/' and c != ' ') {
				cur = go(cur, c);
				int tmp = cur;
				do {
					int id = t[tmp].leaf;
					if (id != -1) {
						int j = (int)line.size() - i - wh - (int)w[id].size();
						if (ans[j].first < (int)w[id].size()) 
							ans[j] = {w[id].size(), id}, is = 1;
					}
					tmp = get_leaf_link(tmp);
				} while (tmp);
			}
			else ++wh;
		}
		if (!is) cout << "-\n";
		else {
			int j = 0, first = 1;
			while (j < (int)ans.size()) {
				while (j < (int)ans.size() and ans[j].first == -1) ++j;
				if (j == (int)ans.size()) break;
				cout << (first ? "" : " ") << w[ans[j].second];
				first = 0;
				j += ans[j].first;
			}
			cout << '\n';
		}
	}
}
