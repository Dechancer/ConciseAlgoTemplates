template <class T>
struct Dijkstra {
  using pti = pair<T, int>;
  vector<T> dist;
  vector<vector<pti>> adj;

  Dijkstra(int n) { init(n); }

  void init(int n) {
    dist.assign(n, -1);
    adj.assign(n, vector(0, {}));
  }

  void add_edge(int u, int v, T w) { adj[u].push_back({w, v}); }

  void run(int s) {
    priority_queue<pti, vector<pti>, greater<pti>> q;
    q.push({0, s});
    while (q.size()) {
      auto [d, u] = q.top();
      q.pop();

      if (dist[u] != -1) {
        continue;
      }
      dist[u] = d;

      for (auto& [w, v] : adj[u]) {
        q.push({d + w, v});
      }
    }
  }
};