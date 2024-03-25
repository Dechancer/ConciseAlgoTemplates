template <class T>
struct BIT {
  int n;
  vector<T> bit;

  BIT(int n) { init(n); }

  void init(int n) {
    this->n = n;
    bit.assign(n + 1, 0);
  }

  int lowbit(int i) { return i & -i; }

  void modify(int x, const T& v) {
    for (int i = x + 1; i <= n; i += lowbit(i)) {
      bit[i] = bit[i] + v;
    }
  }

  T query(int x) {
    T res = 0;
    for (int i = x; i; i -= lowbit(i)) {
      res = res + bit[i];
    }
    return res;
  }
  T query(int l, int r) { return query(r) - query(l); }

  int select(const T& k) {
    int x = 0;
    T cur;
    for (int i = 1 << __lg(n); i; i >>= 1) {
      if (x + i <= n && cur + bit[x + i] <= k) {
        x += i;
        cur = cur + bit[x];
      }
    }
    return x;
  }
};