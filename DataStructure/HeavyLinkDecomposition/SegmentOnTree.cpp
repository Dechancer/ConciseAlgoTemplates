template <class Info, class Tag>
struct SegmentOnTree : HLD, LazySegmentTree<Info, Tag> {
  using Seg = LazySegmentTree<Info, Tag>;
  SegmentOnTree() {}
  SegmentOnTree(int n) { init(n); }

  void init(int n) { HLD::init(n); }

  void run(int root, auto&& a) {
    HLD::run(root);
    vector b(a.size(), Info());
    for (int i = 0; i < a.size(); i++) {
      b[dfn[i]] = a[i];
    }
    Seg::init(b);
  }

  void modifyPath(int u, int v, auto&& t) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]])
        swap(u, v);
      Seg::modify(dfn[top[u]], dfn[u] + 1, t);
      u = fa[top[u]];
    }
    if (dep[u] > dep[v])
      swap(u, v);
    Seg::modify(dfn[u], dfn[v] + 1, t);
  }
  void modifySubtree(int u, auto&& t) {
    Seg::modify(dfn[u], dfn[u] + sz[u], t);
  }

  Info queryPath(int u, int v) {
    Info l, r;
    while (top[u] != top[v]) {
      if (dep[top[u]] > dep[top[v]]) {
        l = Seg::query(dfn[top[u]], dfn[u] + 1) + l;
        u = fa[top[u]];
      } else {
        r = Seg::query(dfn[top[v]], dfn[v] + 1) + r;
        v = fa[top[v]];
      }
    }

    if (dep[u] > dep[v]) {
      l = Seg::query(dfn[v], dfn[u] + 1) + l;
      l.reverse();
    } else {
      l.reverse();
      l = l + Seg::query(dfn[u], dfn[v] + 1);
    }
    return l + r;
  }
  Info querySubtree(int u) { return Seg::query(dfn[u], dfn[u] + sz[u]); }
};

struct Tag {
  void apply(Tag& t) {}
};

struct Info {
  void apply(Tag& t) {}
  void reverse() {}
  friend Info operator+(auto&& a, auto&& b) {
    Info c;
    return c;
  }
};