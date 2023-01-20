// https://codeforces.com/contest/1679/problem/D
// Submitted on May/22/2022

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) x.begin(), x.end()

int n, m;
ll k, t;
vector<int> v, cur, done, len;
vector<vector<int>> adj;

bool has_cycle(int i) {
   if (v[i] > t) return false;
   if (cur[i]) return true;
   if (done[i]) return false;
   cur[i] = 1;
   for (int u: adj[i]) {
      if (has_cycle(u))
         return true;
   }
   cur[i] = 0;
   done[i] = 1;
   return false;
}

int length(int i) {
   if (v[i] > t) return 0;
   if (len[i] != 0)
      return len[i];
   len[i] = 1;
   for (int u: adj[i]) {
      len[i] = max(len[i], 1 + length(u));
   }
   return len[i];
}

bool can(ll w) {
   t = w;
   cur = done = vector<int>(n, 0);
   for (int i = 0; i < n; ++i)
      if (has_cycle(i)) {
         return true;
      }
   len = vector<int>(n, 0);
   for (int i = 0; i < n; ++i)
      if (length(i) >= k)
         return true;
   return false;
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   cin >> n >> m >> k;
   v = vector<int>(n);
   adj = vector<vector<int>>(n);
   for (int &i: v)
      cin >> i;
   for (int i = 0; i < m; ++i) {
      int u, e;
      cin >> u >> e;
      --u, --e;
      adj[u].push_back(e);
   }
   if (!can(1e9)) {
      cout << "-1\n";
      return 0;
   }
   int l = 1, r = 1e9;
   while (l < r) {
      int w = (l + r) / 2;
      if (can(w)) {
         r = w;
      }
      else {
         l = w + 1;
      }
   }
   cout << l << '\n';
}
