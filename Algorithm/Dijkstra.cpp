struct Dijkstra {
  using pli = pair<ll, int>;
  const ll inf;
  vector<ll> dist;
  vector<vector<pli>> adj;

  Dijkstra(int n, ll inf) : inf(inf) { init(n); }

  void init(int n) {
    dist.assign(n, inf);
    adj.assign(n, vector(0, {}));
  }

  void addEdge(int u, int v, ll w) { adj[u].push_back({w, v}); }

  void run(int s) {
    priority_queue<pli, vector<pli>, greater<pli>> q;
    q.push({0, s});
    while (q.size()) {
      auto [d, u] = q.top();
      q.pop();

      if (dist[u] != inf) {
        continue;
      }
      dist[u] = d;

      for (auto& [w, v] : adj[u]) {
        q.push({d + w, v});
      }
    }
  }
};