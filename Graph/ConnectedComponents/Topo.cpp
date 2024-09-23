struct Topo {
  int n;
  queue<int> q;
  vector<int> deg;
  vector<vector<int>> adj;

  Topo() {}
  Topo(int n) { init(n); };

  void init(int n) {
    this->n = n;
    deg.assign(n, 0);
    adj.assign(n, {});
  }
  void addEdge(int u, int v) {
    deg[v]++;
    adj[u].emplace_back(v);
  }

  void resetDeg() {
    deg.assign(n, 0);
    for (int u = 0; u < n; u++) {
      for (int& v : adj[u]) {
        deg[v]++;
      }
    }
  }

  bool run(auto&& pred, auto&& maintain) {
    for (int u = 0; u < n; u++) {
      if (pred(u))
        q.emplace(u);
    }
    int vis = 0;
    while (q.size()) {
      int u = q.front();
      q.pop();
      vis++;
      for (int& v : adj[u]) {
        deg[v]--;
        maintain(u, v);
        if (pred(v))
          q.emplace(v);
      }
    }
    return vis == n;
  }
};