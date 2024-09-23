template <class Info, class Tag>
struct LazySegmentTree {
  int n, ql, qr;
  Tag t;
  vector<Tag> tag;
  vector<Info> seg;

  LazySegmentTree() {}
  LazySegmentTree(const vector<Info>& a) { init(a); }

  void init(const vector<Info>& a) {
    n = a.size();
    seg.assign(4 << __lg(n), Info());
    tag.assign(4 << __lg(n), Tag());
    function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (l + 1 == r)
        return void(seg[p] = a[l]);

      int mid = (l + r) / 2;
      build(p * 2, l, mid);
      build(p * 2 + 1, mid, r);
      pull(p);
    };
    build(1, 0, n);
  }

  void pull(int p) { seg[p] = seg[p * 2] + seg[p * 2 + 1]; }
  void push(int p) {
    apply(p * 2, tag[p]);
    apply(p * 2 + 1, tag[p]);
    tag[p] = Tag();
  }
  void apply(int p, const Tag& t) {
    seg[p].apply(t);
    tag[p].apply(t);
  }

  void modify(int l, int r, const Tag& t) {
    ql = l, qr = r;
    this->t = t;
    modify(1, 0, n);
  }
  void modify(int p, int l, int r) {
    if (qr <= l or r <= ql)
      return;
    if (ql <= l and r <= qr)
      return apply(p, t);

    push(p);
    int mid = (l + r) / 2;
    modify(p * 2, l, mid);
    modify(p * 2 + 1, mid, r);
    pull(p);
  }

  Info query(int l, int r) {
    ql = l, qr = r;
    return query(1, 0, n);
  }
  Info query(int p, int l, int r) {
    if (qr <= l or r <= ql)
      return Info();
    if (ql <= l and r <= qr)
      return seg[p];

    push(p);
    int mid = (l + r) / 2;
    return query(p * 2, l, mid) + query(p * 2 + 1, mid, r);
  }

  int lowerBound(int l, int r, auto&& pred) {
    ql = l, qr = r;
    return min(r, lowerBound(1, 0, n, pred));
  }
  int lowerBound(int p, int l, int r, auto&& pred) {
    if (qr <= l or r <= ql or !pred(seg[p]))
      return r;
    if (l + 1 == r)
      return l;

    push(p);
    int mid = (l + r) / 2;
    int res = lowerBound(p * 2, l, mid, pred);
    if (res == mid)
      res = lowerBound(p * 2 + 1, mid, r, pred);
    return res;
  }
};

struct Tag {
  void apply(const Tag& t) {}
};

struct Info {
  void apply(const Tag& t) {}
  friend Info operator+(const Info& a, const Info& b) {
    Info c;
    return c;
  }
};
