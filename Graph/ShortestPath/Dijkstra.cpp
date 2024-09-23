template <class T>
struct Dijkstra {
  const T inf = numeric_limits<T>::max() / 2;
  vector<T> dist;
  vector<vector<pair<int, T>>> adj;

  Dijkstra(int n) { init(n); }

  void init(int n) {
    dist.assign(n, inf);
    adj.assign(n, {});
  }

  void addEdge(int u, int v, T w) { adj[u].emplace_back(v, w); }

  void run(int s, auto&& pred) {
    priority_queue q{greater(), vector{pair(T(), s)}};
    while (q.size()) {
      auto [d, u] = q.top();
      q.pop();

      if (!pred(u))
        continue;
      dist[u] = d;
      for (auto& [v, w] : adj[u]) {
        if (pred(v))
          q.emplace(d + w, v);
      }
    }
  }
  // h must be updated by starting with end point
  T kth(int s, int t, int k, auto&& h) {
    vector cnt(dist.size(), 0);
    priority_queue q{greater(), vector{tuple(T(), T(), s)}};
    while (q.size()) {
      auto [f, g, u] = q.top();
      q.pop();

      if (cnt[u] == k)
        continue;
      cnt[u]++;
      dist[u] = cnt[u] == k ? f : inf;
      if (cnt[t] == k)
        return dist[t];

      for (auto& [v, w] : adj[u]) {
        q.emplace(g + w + h[v], g + w, v);
      }
    }
    return dist[t];
  }
};