template <class T>
struct BF {
  const T inf = numeric_limits<T>::max() / 2;
  vector<T> dist;
  vector<tuple<int, int, T>> edge;

  BF(int n) { init(n); }

  void init(int n) { dist.assign(n, inf); }

  void addEdge(int u, int v, T w) { edge.push_back({u, v, w}); }

  bool relax() {
    bool ok = false;
    for (auto& [u, v, w] : edge) {
      if (dist[u] != inf and dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        ok = true;
      }
    }
    return ok;
  }

  bool run(int s) {
    bool ok = false;
    dist[s] = 0;
    for (int i = 0; i < dist.size(); i++) {
      ok |= relax() == false;
      if (ok)
        break;
    }
    return ok;
  }
};