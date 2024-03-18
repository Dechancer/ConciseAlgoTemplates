struct DSU {
  vector<int> f, sz;

  DSU(int n) { init(n); }

  void init(int n) {
    f.resize(n);
    iota(f.begin(), f.end(), 0);
    sz.assign(n, 1);
  }

  int find(int u) {
    while (u != f[u]) {
      u = f[u] = f[f[u]];
    }
    return u;
  }

  bool same(int u, int v) { return find(u) == find(v); }

  bool merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) {
      return false;
    }
    sz[u] += sz[v];
    f[v] = u;
    return true;
  }

  int size(int u) { return sz[find(u)]; }
};