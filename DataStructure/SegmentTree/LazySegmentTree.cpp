template <class Info, class Tag>
struct LazySegmentTree {
  int n;
  int ql, qr;
  Tag v;
  vector<Info> seg;
  vector<Tag> tag;

  LazySegmentTree(const vector<Info>& a) : LazySegmentTree(a.size()) {
    function<void(int, int, int)> build = [&](int l, int r, int p) {
      if (l == r)
        return void(seg[p] = a[l - 1]);

      int mid = (l + r) / 2;
      build(l, mid, p * 2);
      build(mid + 1, r, p * 2 + 1);
      pull(p);
    };
    build(1, n, 1);
  }

  LazySegmentTree(int n) : n(n) {
    seg.resize(n * 4);
    tag.resize(n * 4);
  }

  void pull(int p) { seg[p] = seg[p * 2] + seg[p * 2 + 1]; }
  void push(int p) {
    apply(p * 2, tag[p]);
    apply(p * 2 + 1, tag[p]);
    tag[p] = Tag();
  }
  void apply(int p, Tag& v) {
    seg[p].apply(v);
    tag[p].apply(v);
  }

  void update(int ql, int qr, const Tag& v) {
    this->ql = ql;
    this->qr = qr;
    this->v = v;
    update(1, n, 1);
  }
  void update(int l, int r, int p) {
    if (qr < l or r < ql)
      return;
    if (ql <= l and r <= qr)
      return apply(p, v);

    push(p);
    int mid = (l + r) / 2;
    update(l, mid, p * 2);
    update(mid + 1, r, p * 2 + 1);
    pull(p);
  }

  Info query(int ql, int qr) {
    this->ql = ql;
    this->qr = qr;
    return query(1, n, 1);
  }
  Info query(int l, int r, int p) {
    if (qr < l or r < ql)
      return Info();
    if (ql <= l and r <= qr)
      return seg[p];

    int mid = (l + r) / 2;
    push(p);
    return query(l, mid, p * 2) + query(mid + 1, r, p * 2 + 1);
  }
};

struct Tag {
  void apply(Tag& v) {}
};

struct Info {
  void apply(Tag& v) {}
};

Info operator+(Info a, Info b) {
  return a;
}