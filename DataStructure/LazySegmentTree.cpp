template <class Info, class Tag>
struct LazySegmentTree {
  int n;
  int ql, qr;
  Tag v;
  vector<Tag> tag;
  vector<Info> seg;
  function<bool(Info)> pred;

  LazySegmentTree() {}
  LazySegmentTree(int n, Info v = Info()) { init(vector(n, v)); }
  LazySegmentTree(const vector<Info>& a) { init(a); }

  void init(const vector<Info>& a) {
    n = a.size();
    seg.assign(n * 4, Info());
    tag.assign(n * 4, Tag());
    function<void(int, int, int)> build = [&](int l, int r, int p) {
      if (l + 1 == r)
        return void(seg[p] = a[l]);

      int mid = (l + r) / 2;
      build(l, mid, p * 2);
      build(mid, r, p * 2 + 1);
      pull(p);
    };
    build(0, n, 1);
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

  void modify(int ql, int qr, const Tag& v) {
    this->ql = ql;
    this->qr = qr;
    this->v = v;
    modify(0, n, 1);
  }
  void modify(int l, int r, int p) {
    if (qr <= l or r <= ql)
      return;
    if (ql <= l and r <= qr)
      return apply(p, v);

    push(p);
    int mid = (l + r) / 2;
    modify(l, mid, p * 2);
    modify(mid, r, p * 2 + 1);
    pull(p);
  }

  Info query(int ql, int qr) {
    this->ql = ql;
    this->qr = qr;
    return query(0, n, 1);
  }
  Info query(int l, int r, int p) {
    if (qr <= l or r <= ql)
      return Info();
    if (ql <= l and r <= qr)
      return seg[p];

    int mid = (l + r) / 2;
    push(p);
    return query(l, mid, p * 2) + query(mid, r, p * 2 + 1);
  }

  int lowerBound(int ql, int qr, auto pred) {
    this->ql = ql;
    this->qr = qr;
    this->pred = pred;
    return lowerBound(0, n, 1);
  }
  int lowerBound(int l, int r, int p) {
    if (qr <= l or r <= ql or !pred(seg[p]))
      return -1;
    if (l + 1 == r)
      return l;

    int mid = (l + r) / 2;
    int res = lowerBound(l, mid, p * 2);
    if (res == -1) {
      res = lowerBound(mid, r, p * 2 + 1);
    }
    return res;
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