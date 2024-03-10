struct Dijkstra {
  using pii = pair<int, int>;
  vector<int> dis;
  vector<vector<pii>> adj;

  Dijkstra(int n) {
    dis.resize(n, -1);
    adj.resize(n);
  }

  void add_edge(int u, int v, int w) { adj[u].push_back({v, w}); }

  void run(int s) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, s});
    while (pq.size()) {
      auto [d, u] = pq.top();
      pq.pop();

      if (dis[u] != -1) {
        continue;
      }
      dis[u] = d;

      for (auto& [v, w] : adj[u]) {
        pq.push({d + w, v});
      }
    }
  }
};