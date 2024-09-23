struct TwoSat {
  int n;
  vector<bool> ans;
  vector<vector<int>> adj;

  TwoSat() {}
  TwoSat(int n) { init(n); }

  void init(int n) {
    this->n = n;
    ans.resize(n);
    adj.assign(n * 2, {});
  }

  void addClause(int u, bool f, int v, bool g) {
    adj[u * 2 + !f].push_back(v * 2 + g);
    adj[v * 2 + !g].push_back(u * 2 + f);
  }

  bool satisfiable() {
    vector<int> stk;
    int cur = 0, cnt = 0;
    vector<int> bel(n * 2, -1), dfn(n * 2, -1), low(n * 2, -1);

    function<void(int)> scc = [&](int u) {
      stk.push_back(u);
      dfn[u] = low[u] = cur++;
      for (auto& v : adj[u]) {
        if (dfn[v] == -1) {
          scc(v);
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
    };

    for (int u = 0; u < n * 2; u++) {
      if (dfn[u] == -1)
        scc(u);
    }

    for (int u = 0; u < n; u++) {
      if (bel[u * 2] == bel[u * 2 + 1])
        return false;
      ans[u] = bel[u * 2] > bel[u * 2 + 1];
    }
    return true;
  }
  vector<bool>& answer() { return ans; }
};