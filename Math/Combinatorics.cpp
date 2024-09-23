template <class T>
struct Comb {
  int n;
  vector<T> fac, inv;
  Comb(int n) : n(n) {
    fac.resize(n + 1, 1);
    inv.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      fac[i] = fac[i - 1] * i;
    }

    inv[n] = 1 / fac[n];
    for (int i = n; i; i--) {
      inv[i - 1] = inv[i] * i;
    }
  }

  T A(int n, int m) { return fac[n] * inv[n - m]; }

  T C(int n, int m) { return A(n, m) * inv[m]; }

  T D(int n) {
    vector d(n + 1, T(1));
    for (int i = 1, sign = -1; i <= n; i++, sign = -sign) {
      d[i] = i * d[i - 1] + sign;
    }
    return d[n];
  }

  T C(int n) { return C(n * 2, n) - C(n * 2, n + 1); }

  T s(int n, int m) {
    vector res(m + 1, T(1));
    for (int i = 0; i < n; i++) {
      for (int j = min(i + 1, m); j > 0; j--) {
        res[j] = res[j - 1] + i * res[j];
      }
      res[0] = 0;
    }
    return res[m];
  }

  T S(int n, int m) {
    T res = 0;
    for (int i = 0, sign = 1; i <= m; i++, sign = -sign) {
      res += sign * C(m, i) * (T(m - i) ^ n);
    }
    return res * inv[m];
  }
};