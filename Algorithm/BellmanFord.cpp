struct BF {
  const ll inf;
  vector<ll> dist;
  vector<tuple<int, int, ll>> edge;

  BF(int n, ll inf) : inf(inf) { init(n); }

  void init(int n) { dist.assign(n, inf); }

  void addEdge(int u, int v, ll w) { edge.push_back({u, v, w}); }

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

  void run(int s) {
    dist[s] = 0;
    for (int i = 0; i < dist.size(); i++) {
      if (!relax()) {
        break;
      }
    }
  }
};