struct Dijkstra {
  int n;
  const ll inf;
  vector<bool> out;
  vector<ll> dist;
  vector<vector<ll>> adj;

  Dijkstra(int n, ll inf) : inf(inf) { init(n); }

  void init(int n) {
    this->n = n;
    out.assign(n, true);
    dist.assign(n, inf);
    adj.assign(n, vector(n, inf));
  }

  void addEdge(int u, int v, ll w) { adj[u][v] = min(adj[u][v], w); }

  void run(int u) {
    dist[u] = 0;
    for (int k = 0; k < n; k++) {
      out[u] = false;
      int next = u;
      ll mn = inf;
      for (int v = 0; v < n; v++) {
        dist[v] = min(dist[v], dist[u] + adj[u][v]);
        if (out[v] and dist[v] < mn) {
          mn = dist[v];
          next = v;
        }
      }
      u = next;
    }
  }
};