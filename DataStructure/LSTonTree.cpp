struct HLD : LazySegmentTree<Info, Tag> {
  int idx;
  vector<int> fa, sz, dep, top, dfn;
  vector<vector<int>> adj;

  HLD() {}
  HLD(int n) { init(n); }

  void init(int n) {
    fa.resize(n);
    sz.resize(n);
    dep.resize(n);
    top.resize(n);
    dfn.resize(n);
    adj.assign(n, {});
  }
  void init(const vector<Info>& a) {
    vector b(a.size(), Info());
    for (int i = 0; i < a.size(); i++) {
      b[dfn[i]] = a[i];
    }
    LazySegmentTree::init(b);
  }

  void addEdge(int u, int v) { adj[u].push_back(v); }

  void dfs0(int u) {
    if (fa[u] != -1) {
      adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));
    }
    sz[u] = 1;
    for (auto& v : adj[u]) {
      fa[v] = u;
      dep[v] = dep[u] + 1;
      dfs0(v);
      sz[u] += sz[v];
      if (sz[v] > sz[adj[u][0]]) {
        swap(v, adj[u][0]);
      }
    }
  }

  void dfs1(int u) {
    dfn[u] = idx++;
    for (auto& v : adj[u]) {
      top[v] = v == adj[u][0] ? top[u] : v;
      dfs1(v);
    }
  }

  void run(int root) {
    idx = 0;
    top[root] = root;
    dep[root] = 0;
    fa[root] = -1;
    dfs0(root);
    dfs1(root);
  }

  void modifyPath(int u, int v, Tag value) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) {
        swap(u, v);
      }
      modify(dfn[top[u]], dfn[u] + 1, value);
      u = fa[top[u]];
    }
    if (dep[u] > dep[v]) {
      swap(u, v);
    }
    modify(dfn[u], dfn[v] + 1, value);
  }

  void modifySubtree(int u, Tag value) {
    modify(dfn[u], dfn[u] + sz[u], value);
  }

  Info queryPath(int u, int v) {
    Info res;
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) {
        swap(u, v);
      }
      res = res + query(dfn[top[u]], dfn[u] + 1);
      u = fa[top[u]];
    }
    if (dep[u] > dep[v]) {
      swap(u, v);
    }
    return res + query(dfn[u], dfn[v] + 1);
  }

  Info querySubtree(int u) { return query(dfn[u], dfn[u] + sz[u]); }
};