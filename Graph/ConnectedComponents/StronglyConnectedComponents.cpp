struct SCC {
  int n;
  int cur, cnt;
  vector<int> stk;
  vector<int> dfn, low, bel;
  vector<vector<int>> adj;

  SCC() {}
  SCC(int n) { init(n); }

  void init(int n) {
    this->n = n;
    cur = cnt = 0;
    stk.clear();
    dfn.assign(n, -1);
    low.resize(n);
    bel.assign(n, -1);
    adj.assign(n, {});
  }

  void addEdge(int u, int v) { adj[u].push_back(v); }

  void dfs(int u) {
    dfn[u] = low[u] = cur++;
    stk.push_back(u);

    for (auto& v : adj[u]) {
      if (dfn[v] == -1) {
        dfs(v);
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
      if (dfn[u] == -1)
        dfs(u);
    }
    return bel;
  }
  struct Graph {
    int n;
    vector<int> sz;
    vector<pair<int, int>> edge;
  };
  Graph compress() {
    Graph g;
    g.n = cnt;
    g.sz.resize(cnt);
    for (int u = 0; u < n; u++) {
      g.sz[bel[u]]++;
      for (int& v : adj[u]) {
        if (bel[u] != bel[v])
          g.edge.emplace_back(bel[u], bel[v]);
      }
    }
    sort(g.edge.begin(), g.edge.end());
    g.edge.erase(unique(g.edge.begin(), g.edge.end()), g.edge.end());
    return g;
  }
};