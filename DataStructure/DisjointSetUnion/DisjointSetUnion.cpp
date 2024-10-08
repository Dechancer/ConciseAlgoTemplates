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
  bool merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) {
      return false;
    }
    f[u] = v;
    sz[v] += sz[u];
    return true;
  }

  bool same(int u, int v) { return find(u) == find(v); }
  int size(int u) { return sz[find(u)]; }
};