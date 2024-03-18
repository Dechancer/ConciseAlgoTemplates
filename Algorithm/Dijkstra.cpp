template <class T>
struct Dijkstra {
  using pti = pair<T, int>;
  vector<T> dis;
  vector<vector<pti>> adj;

  Dijkstra(int n) { init(n); }

  void init(int n) {
    dis.assign(n, T{-1});
    adj.assign(n, vector(0, pti{}));
  }

  void add_edge(int u, int v, T w) { adj[u].push_back({w, v}); }

  void run(int s) {
    priority_queue<pti, vector<pti>, greater<pti>> pq;
    pq.push({T{}, s});
    while (pq.size()) {
      auto [d, u] = pq.top();
      pq.pop();

      if (dis[u] != -1) {
        continue;
      }
      dis[u] = d;

      for (auto& [w, v] : adj[u]) {
        pq.push({d + w, v});
      }
    }
  }
};