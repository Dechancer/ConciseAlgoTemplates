template <class Info>
struct SegmentTree {
  int n;
  int ql, qr;
  Info v;
  vector<Info> seg;

  SegmentTree(int n, Info v = Info()) { init(vector(n, v)); }
  SegmentTree(const vector<Info>& a) { init(a); }

  void init(const vector<Info>& a) {
    n = a.size();
    seg.assign(n * 4, Info());
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

  void modify(int i, const Info& v) {
    ql = i;
    qr = i + 1;
    this->v = v;
    modify(0, n, 1);
  }
  void modify(int l, int r, int p) {
    if (qr <= l or r <= ql)
      return;
    if (l + 1 == r)
      return seg[p].apply(v);

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
    return query(l, mid, p * 2) + query(mid, r, p * 2 + 1);
  }
};

struct Info {
  void apply(Info& v) {}
};

Info operator+(Info a, Info b) {
  return a;
}