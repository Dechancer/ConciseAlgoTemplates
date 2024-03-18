template <class T>
struct BIT {
  int n;
  vector<T> pre;

  BIT(int n) { init(n); }

  void init(int n) {
    this->n = n;
    pre.assign(n, T{});
  }

  int lowbit(int i) { return i & -i; }

  void update(int x, const T& v) {
    for (int i = x + 1; i <= n; i += lowbit(i)) {
      pre[i - 1] = pre[i - 1] + v;
    }
  }

  T query(int x) {
    T res = 0;
    for (int i = x; i; i -= lowbit(i)) {
      res = res + pre[i - 1];
    }
    return res;
  }
  T query(int l, int r) { return query(r) - query(l); }

  int select(const T& k) {
    int x = 0;
    T cur{};
    for (int i = 1 << __lg(n); i; i /= 2) {
      if (x + i <= n && cur + pre[x + i - 1] <= k) {
        x += i;
        cur = cur + pre[x - 1];
      }
    }
    return x;
  }
};