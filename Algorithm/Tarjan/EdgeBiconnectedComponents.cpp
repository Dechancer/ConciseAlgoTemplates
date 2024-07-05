struct EBCC {
  int n;
  int cur, cnt;
  vector<int> stk;
  vector<int> dfn, low, bel;
  vector<vector<int>> adj;

  EBCC() {}
  EBCC(int n) { init(n); }

  void init(int n) {
    this->n = n;
    cur = cnt = 0;
    stk.clear();
    dfn.assign(n, -1);
    low.resize(n);
    bel.assign(n, -1);
    adj.assign(n, {});
  }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void dfs(int u, int fa) {
    if (fa != -1) {
      adj[u].erase(find(adj[u].begin(), adj[u].end(), fa));
    }
    dfn[u] = low[u] = cur++;
    stk.push_back(u);

    for (auto v : adj[u]) {
      if (dfn[v] == -1) {
        dfs(v, u);
        low[u] = min(low[u], low[v]);
      } else if (bel[v] == -1) {
        low[u] = min(low[u], dfn[v]);
      }
    }

    if (dfn[u] == low[u]) {
      int v;
      do {
        v = stk.back();
        stk.pop_back();
        bel[v] = cnt;
      } while (v != u);
      cnt++;
    }
  }

  vector<int>& run() {
    for (int u = 0; u < n; u++) {
      if (dfn[u] == -1) {
        dfs(u, -1);
      }
    }
    return bel;
  }
};
