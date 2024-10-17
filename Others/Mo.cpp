template <class T>
struct Mo {
  int l, r, len;
  T cur;
  vector<T> ans;
  vector<array<int, 3>> q;
  Mo() {}
  Mo(int n, int m) { init(n, m); }

  void init(int n, int m) {
    l = 0, r = 0, len = sqrt(n);
    cur = {};
    ans.resize(m);
    q.clear();
  }
  void addQuery(int l, int r) { q.push_back({l, r, (int)q.size()}); }

  void run(auto&& add, auto&& del) {
    sort(q.begin(), q.end(), [&](auto& a, auto& b) {
      if (a[0] / len != b[0] / len)
        return a[0] < b[0];
      return a[0] / len % 2 ? a[1] > b[1] : a[1] < b[1];
    });

    for (auto& [ql, qr, i] : q) {
      while (l > ql)
        add(--l);
      while (r < qr)
        add(r++);
      while (l < ql)
        del(l++);
      while (r > qr)
        del(--r);
      ans[i] = cur;
    }
  }
};