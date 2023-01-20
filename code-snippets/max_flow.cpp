#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

struct edge {
	int x, y, c, f;
	edge(int _x, int _y, int _c, int _f) :
		x(_x), y(_y), c(_c), f(_f) {}
};

int n, s, t;
vector<int> dist, curr;
vector<vector<int>> AdjList;
vector<edge> E;

void addEdge(int x, int y, int c) {
	AdjList[x].push_back(E.size());
	E.push_back(edge(x, y, c, 0));
	AdjList[y].push_back(E.size());
	E.push_back(edge(y, x, 0, 0));
}

bool bfs() {
	dist = vector<int>(n, -1);
	dist[s] = 0;
	queue<int> q;
	q.push(s);
	while (!q.empty() and dist[t] == -1) {
		int u = q.front();
		q.pop();
		for (size_t i = 0; i < AdjList[u].size(); ++i) {
			int id = AdjList[u][i], v = E[id].y;
			if (dist[v] == -1 and E[id].f < E[id].c) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
	return dist[t] != -1;
}

int dfs(int u, int flow) {
	if (!flow) return 0;
	if (u == t) return flow;
	for (; curr[u] < (int)AdjList[u].size(); ++curr[u]) {
		int id = AdjList[u][curr[u]], v = E[id].y;
		if (dist[v] != dist[u] + 1) continue;
		int sent = dfs(v, min(flow, E[id].c - E[id].f));
		if (sent) {
			E[id].f += sent;
			E[id ^ 1].f -= sent;
			return sent;
		}
	}
	return 0;
}

int max_flow() {
	int flow = 0, sent;
	while (1) {
		if (!bfs()) break;
		curr = vector<int>(n, 0);
		while (sent = dfs(s, INF))
			flow += sent;
	}
	return flow;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int m, x, y, c;
	cin >> n >> m;
	AdjList = vector<vector<int>>(n);
	while (m--) {
		cin >> x >> y >> c;
		addEdge(x, y, c);
	}
	s = 0, t = n - 1;
	cout << max_flow() << endl;
}
