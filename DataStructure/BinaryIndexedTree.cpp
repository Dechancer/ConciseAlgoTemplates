template <class T>
struct BIT {
  int n;
  vector<T> bit;
  BIT(int n) : n(n) { bit.resize(n + 1); }
  BIT(const vector<T>& a) : BIT(a.size()) {
    for (int i = 1; i <= n; i++) {
      bit[i] += a[i - 1];
      int fa = i + lowbit(i) > n ? 0 : i + lowbit(i);
      bit[fa] += bit[i];
    }
  }

  int lowbit(int i) { return i & -i; }

  void update(int i, T v) {
    while (i <= n) {
      bit[i] += v;
      i += lowbit(i);
    }
  }

  T query(int i) {
    T res = 0;
    while (i) {
      res += bit[i];
      i -= lowbit(i);
    }
    return res;
  }

  int select(T k) {
    int x = 0;
    for (int i = 1 << __lg(n); i; i /= 2) {
      if (x + i <= n && bit[x + i] <= k) {
        x += i;
        k -= bit[x];
      }
    }
    return x;
  }
};