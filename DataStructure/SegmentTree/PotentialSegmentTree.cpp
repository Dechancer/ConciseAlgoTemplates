template <class Info>
struct PotentialSegmentTree {
  int n;
  int ql, qr;
  Info v;
  vector<Info> seg;

  PotentialSegmentTree(const vector<Info>& a) : PotentialSegmentTree(a.size()) {
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

  PotentialSegmentTree(int n) : n(n) { seg.resize(n * 4); }

  void pull(int p) { seg[p] = seg[p * 2] + seg[p * 2 + 1]; }

  void update(int ql, int qr, const Info& v) {
    this->ql = ql;
    this->qr = qr;
    this->v = v;
    update(1, n, 1);
  }
  void update(int l, int r, int p) {
    if (seg[p].check(v))
      return;
    if (qr < l or r < ql)
      return;
    if (l == r)
      return seg[p].apply(v);

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
    return query(l, mid, p * 2) + query(mid + 1, r, p * 2 + 1);
  }
};

struct Info {
  void apply(Info& v) {}

  bool check(Info& v) {}
};

Info operator+(Info a, Info b) {
  return a;
}