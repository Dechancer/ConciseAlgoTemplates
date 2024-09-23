struct VBCC {
  int n;
  int cur, cnt;
  vector<int> stk;
  vector<int> dfn, low, cut;
  vector<vector<int>> adj, comp;

  VBCC() {}
  VBCC(int n) { init(n); }

  void init(int n) {
    this->n = n;
    cur = cnt = 0;
    stk.clear();
    dfn.assign(n, -1);
    low.resize(n);
    cut.assign(n, false);
    comp.assign(0, {});
    adj.assign(n, {});
  }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void dfs(int u, int fa) {
    dfn[u] = low[u] = cur++;
    stk.push_back(u);

    int son = 0;
    for (auto& v : adj[u]) {
      if (dfn[v] == -1) {
        dfs(v, u);
        low[u] = min(low[u], low[v]);
        son++;
        if (low[v] >= dfn[u]) {
          if (fa != -1 or son > 1) {
            cut[u] = true;
          }
          int w;
          comp.push_back({u});
          do {
            w = stk.back();
            stk.pop_back();
            comp[cnt].push_back(w);
          } while (w != v);
          cnt++;
        }
      } else {
        low[u] = min(low[u], dfn[v]);
      }
    }

    if (adj[u].empty()) {
      comp.push_back({u});
      stk.pop_back();
      cnt++;
    }
  }

  auto& run() {
    for (int u = 0; u < n; u++) {
      if (dfn[u] == -1)
        dfs(u, -1);
    }
    return comp;
  }
  struct Graph {
    int n;
    vector<pair<int, int>> edge;
  };
  Graph compress() {
    Graph g;
    g.n = n + cnt;
    for (int v = 0; v < cnt; v++) {
      for (int& u : comp[v]) {
        g.edge.emplace_back(u, v + n);
      }
    }
    return g;
  }
};