struct Hungarian {
  int n, m;
  int matchs;
  vector<bool> vis;
  vector<int> matchL, matchR;
  vector<vector<int>> adj;

  Hungarian() {}
  Hungarian(int n, int m) { init(n, m); }

  void init(int n, int m) {
    this->n = n;
    this->m = m;
    vis.resize(m);
    matchL.assign(n, -1);
    matchR.assign(m, -1);
    adj.assign(n, {});
  }

  void addEdge(int u, int v) { adj[u].push_back(v); }

  bool dfs(int u) {
    for (auto& v : adj[u]) {
      if (vis[v])
        continue;

      vis[v] = true;
      if (matchR[v] == -1 or dfs(matchR[v])) {
        matchR[v] = u;
        return true;
      }
    }
    return false;
  }

  int run() {
    matchs = 0;
    for (int u = 0; u < n; u++) {
      vis.assign(n, false);
      matchs += dfs(u);
    }
    for (int v = 0; v < m; v++) {
      if (matchR[v] != -1)
        matchL[matchR[v]] = v;
    }
    return matchs;
  }

  auto& game() {
    vis.assign(n, false);
    auto dfs = [&](auto&& self, int u) -> void {
      vis[u] = true;
      for (auto& v : adj[u]) {
        if (matchR[v] == -1 or vis[matchR[v]])
          continue;
        self(self, matchR[v]);
      }
    };

    for (int u = 0; u < n; u++) {
      if (vis[u] or matchL[u] != -1)
        continue;
      dfs(dfs, u);
    }
    return vis;
  }

  int maxMatch() { return matchs; }
  int minVertexCover() { return matchs; }
  int minEdgeCover() { return n + m - matchs; }
  int maxIndependentSet() { return n + m - matchs; }
  int minPathCover() { return n - matchs; }
};