template <class T>
struct SPFA {
  const T inf = numeric_limits<T>::max() / 2;
  vector<int> cnt;
  vector<bool> out;
  vector<T> dist;
  vector<vector<pair<int, T>>> adj;

  SPFA(int n) { init(n); }

  void init(int n) {
    cnt.assign(n, 0);
    out.assign(n, true);
    dist.assign(n, inf);
    adj.assign(n, {});
  }

  void addEdge(int u, int v, T w) { adj[u].push_back({v, w}); }

  bool run(int s) {
    queue q(deque(1, s));
    dist[s] = 0;
    while (q.size()) {
      int u = q.front();
      q.pop();
      out[u] = true;
      for (auto& [v, w] : adj[u]) {
        if (dist[v] <= dist[u] + w)
          continue;
        dist[v] = dist[u] + w;

        cnt[v] = cnt[u] + 1;
        if (cnt[v] == dist.size())
          return false;

        if (out[v]) {
          out[v] = false;
          q.push(v);
        }
      }
    }
    return true;
  }
};