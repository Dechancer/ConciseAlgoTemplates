template <class T>
struct Floyd {
  int n;
  const T inf = numeric_limits<T>::max() / 2;
  vector<vector<T>> adj;

  Floyd(int n) { init(n); }

  void init(int n) {
    this->n = n;
    adj.assign(n, vector(n, inf));
  }

  void addEdge(int u, int v, T w) { adj[u][v] = min(adj[u][v], w); }

  void relax(int k) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
      }
    }
  }

  void run() {
    for (int k = 0; k < n; k++) {
      relax(k);
    }
  }
};