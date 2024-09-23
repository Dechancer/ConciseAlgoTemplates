template <class Info>
struct SparseTable {
  vector<vector<Info>> seg;

  SparseTable() {}
  SparseTable(const vector<Info>& a) { init(a); }

  void init(const vector<Info>& a) {
    int n = a.size();
    int log = __lg(n);
    seg.assign(log + 1, vector(n, Info()));
    seg[0] = a;
    for (int i = 0; i < log; i++) {
      for (int j = 0; j + (1 << i) <= n; j++) {
        seg[i + 1][j] = seg[i][j] + seg[i][j + (1 << i)];
      }
    }
  }

  Info query(int l, int r) {
    int log = __lg(r - l);
    return seg[log][l] + seg[log][r - (1 << log)];
  }
};

struct Info {
  friend Info operator+(const Info& a, const Info& b) { return Info(); }
};