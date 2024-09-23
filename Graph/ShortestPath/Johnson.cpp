template <class T>
struct Johnson {
  const T inf = numeric_limits<T>::max() / 2;
  int n;
  vector<T> h;
  vector<vector<T>> dist;
  vector<vector<pair<int, T>>> adj;

  Johnson() {}
  Johnson(int n) { init(n); }

  void init(int n) {
    this->n = n;
    h.resize(n);
    dist.assign(n, vector(n, inf));
    adj.assign(n, {});
  }

  void addEdge(int u, int v, T w) { adj[u].emplace_back(v, w); }

  bool relax() {
    bool ok = false;
    for (int u = 0; u < n; u++) {
      for (auto& [v, w] : adj[u]) {
        if (h[u] + w < h[v]) {
          h[v] = h[u] + w;
          ok = true;
        }
      }
    }
    return ok;
  }

  bool BF() {
    bool ok = false;
    h.assign(n, 0);
    for (int i = 0; i < n; i++) {
      ok |= relax() == false;
      if (ok)
        break;
    }
    return ok;
  }

  bool run() {
    if (BF() == false)
      return false;

    for (int s = 0; s < n; s++) {
      priority_queue q{greater(), vector{pair(T(), s)}};
      while (q.size()) {
        auto [d, u] = q.top();
        q.pop();

        if (dist[s][u] != inf)
          continue;
        dist[s][u] = d;
        for (auto& [v, w] : adj[u]) {
          if (dist[s][v] == inf)
            q.emplace(d + w + h[u] - h[v], v);
        }
      }
      for (int v = 0; v < n; v++) {
        if (dist[s][v] != inf)
          dist[s][v] -= h[s] - h[v];
      }
    }
    return true;
  }
};