struct EulerPath {
  int n;
  vector<int> in, out;
  vector<int> cur, path;
  vector<vector<int>> adj;

  EulerPath() {}
  EulerPath(int n) { init(n); };

  void init(int n) {
    this->n = n;
    cur.assign(n, 0);
    path.clear();
    in.assign(n, 0);
    out.assign(n, 0);
    adj.assign(n, {});
  }

  void addEdge(int u, int v) {
    in[v]++, out[u]++;
    adj[u].emplace_back(v);
  }
  void sortEdge(auto&& pred) {
    for (auto& i : adj) {
      sort(i.begin(), i.end(), pred);
    }
  }

  bool isConnected() {
    vector vis(n, false);
    auto dfs = [&](auto&& self, int u) -> int {
      int cnt = 1;
      vis[u] = true;
      for (int& v : adj[u]) {
        if (vis[v])
          continue;
        cnt += self(self, v);
      }
      return cnt;
    };
    return n == 0 or dfs(dfs, 0) == n;
  }
  int dcheck() {
    int s = 0;
    int scnt = 0, tcnt = 0;
    for (int u = 0; u < n; u++) {
      if (out[u] - in[u] == 1)
        s = u, scnt++;
      else if (in[u] - out[u] == 1)
        tcnt++;
      else if (in[u] != out[u])
        return -1;
    }
    return scnt == tcnt and scnt < 2 ? s : -1;
  }
  int ucheck() {
    int s = 0;
    int cnt = 0;
    for (int u = n - 1; u >= 0; u--) {
      if (out[u] % 2) {
        cnt++;
        s = u;
      }
    }
    return cnt == 0 or cnt == 2 ? s : -1;
  }

  void ddfs(int u) {
    while (cur[u] < adj[u].size()) {
      ddfs(adj[u][cur[u]++]);
    }
    path.emplace_back(u);
  }
  void udfs(int u) {
    while (cur[u] < adj[u].size()) {
      int v = adj[u][cur[u]];
      adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
      udfs(adj[u][cur[u]++]);
    }
    path.emplace_back(u);
  }

  auto& run(int s) {
    udfs(s);
    reverse(path.begin(), path.end());
    return path;
  }
};