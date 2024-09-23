template <class T>
struct DSU {
  vector<int> f, sz;
  vector<T> wt;

  DSU(int n) { init(n); }

  void init(int n) {
    f.resize(n);
    iota(f.begin(), f.end(), 0);
    sz.assign(n, 1);
    wt.assign(n, 0);
  }

  auto maintain(int u) {
    T w = 0;
    while (u != f[u]) {
      w += wt[u] += wt[f[u]];
      u = f[u] = f[f[u]];
    }
    return pair{u, w};
  }
  int find(int u) { return maintain(u).first; }
  bool merge(int u, int v, T w) {
    T wu = 0, wv = 0;
    tie(u, wu) = maintain(u);
    tie(v, wv) = maintain(v);
    if (u == v)
      return false;

    f[u] = v;
    sz[v] += sz[u];
    wt[u] = wv - wu + w;
    return true;
  }

  bool same(int u, int v) { return find(u) == find(v); }
  int size(int u) { return sz[find(u)]; }
  T weight(int u) { return maintain(u).second; }
};