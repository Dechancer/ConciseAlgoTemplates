struct HLD {
  int cur;
  vector<int> fa, sz, dep;
  vector<int> top, dfn, seq;
  vector<vector<int>> adj;

  HLD() {}
  HLD(int n) { init(n); }

  void init(int n) {
    cur = 0;
    fa.resize(n);
    sz.resize(n);
    dep.resize(n);
    top.resize(n);
    dfn.resize(n);
    seq.resize(n);
    adj.assign(n, {});
  }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void dfs0(int u) {
    if (fa[u] != -1)
      adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));

    sz[u] = 1;
    for (auto& v : adj[u]) {
      fa[v] = u;
      dep[v] = dep[u] + 1;
      dfs0(v);
      sz[u] += sz[v];
      if (sz[v] > sz[adj[u][0]])
        swap(v, adj[u][0]);
    }
  }

  void dfs1(int u) {
    dfn[u] = cur++;
    seq[dfn[u]] = u;
    for (auto& v : adj[u]) {
      top[v] = v == adj[u][0] ? top[u] : v;
      dfs1(v);
    }
  }

  void run(int root = 0) {
    top[root] = root;
    dep[root] = 0;
    fa[root] = -1;
    dfs0(root);
    dfs1(root);
  }

  int lca(int u, int v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]])
        swap(u, v);
      u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
  }

  int dist(int u, int v) { return dep[u] + dep[v] - dep[lca(u, v)] * 2; }

  int jump(int u, int k) {
    if (dep[u] < k)
      return -1;

    int d = dep[u] - k;
    while (dep[top[u]] > d) {
      u = fa[top[u]];
    }
    return seq[dfn[u] - dep[u] + d];
  }

  bool isAncestor(int anc, int u) {
    return dfn[anc] <= dfn[u] and dfn[u] < dfn[anc] + sz[anc];
  }

  bool isIntersect(int u, int v, int s, int t) {
    return dist(u, v) + dist(s, t) >= dist(u, s) + dist(v, t);
  }

  int rootedParent(int root, int u) {
    if (root == u)
      return u;
    if (!isAncestor(u, root))
      return fa[u];

    auto it = upper_bound(adj[u].begin(), adj[u].end(), root,
                          [&](int x, int y) { return dfn[x] < dfn[y]; });
    return *prev(it);
  }

  int rootedSize(int root, int u) {
    if (root == u)
      return cur;
    if (!isAncestor(u, root))
      return sz[u];
    return cur - sz[rootedParent(root, u)];
  }

  int rootedLca(int root, int u, int v) {
    return lca(root, u) ^ lca(root, v) ^ lca(u, v);
  }
};