struct Dijkstra {
  const ll inf;
  vector<ll> dist;
  vector<vector<pair<int, ll>>> adj;

  Dijkstra(int n, ll inf) : inf(inf) { init(n); }

  void init(int n) {
    dist.assign(n, inf);
    adj.assign(n, {});
  }

  void addEdge(int u, int v, ll w) { adj[u].push_back({v, w}); }

  void run(int s) {
    priority_queue q{greater<pair<ll, int>>(), vector{pair(0ll, s)}};
    while (q.size()) {
      auto [d, u] = q.top();
      q.pop();

      if (dist[u] != inf) {
        continue;
      }
      dist[u] = d;

      for (auto& [v, w] : adj[u]) {
        q.push({d + w, v});
      }
    }
  }
};