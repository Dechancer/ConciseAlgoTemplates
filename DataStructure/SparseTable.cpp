template <class Info>
struct SparseTable {
  vector<vector<Info>> seg;
  SparseTable(const vector<Info>& a) {
    int n = a.size();
    int lg = __lg(n);
    seg.assign(lg + 1, vector(n, Info()));
    seg[0] = a;
    for (int i = 0; i < lg; i++) {
      for (int j = 0; j + (1 << i) <= n; j++) {
        seg[i + 1][j] = seg[i][j] + seg[i][(1 << i) + j];
      }
    }
  }

  Info query(int l, int r) {
    int lg = __lg(r - l);
    return seg[lg][l] + seg[lg][r - (1 << lg)];
  }
};

struct Info {};

Info operator+(Info a, Info b) {
  return a;
}