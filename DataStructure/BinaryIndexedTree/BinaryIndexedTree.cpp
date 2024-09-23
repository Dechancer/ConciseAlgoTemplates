template <class T>
struct BIT {
  int n;
  vector<T> bit;

  BIT(int n = 0) { init(n); }

  void init(int n) {
    this->n = n;
    bit.assign(n + 1, T{});
  }

  int lowbit(int i) { return i & -i; }

  void modify(int x, T v) {
    for (int i = x + 1; i <= n; i += lowbit(i)) {
      bit[i] = bit[i] + v;
    }
  }

  T query(int x) {
    T res{};
    for (int i = x; i > 0; i -= lowbit(i)) {
      res = res + bit[i];
    }
    return res;
  }
  T query(int l, int r) { return query(r) - query(l); }
  // when BIT maintains bucket, rank could search the k-th smallest element,
  // rank starts with 0.
  int rank(T k) {
    T cur{};
    int x = 0;
    for (int i = 1 << __lg(n); i > 0; i /= 2) {
      if (x + i <= n and cur + bit[x + i] <= k) {
        x += i;
        cur = cur + bit[x];
      }
    }
    return x;
  }
};