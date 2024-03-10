template <class T>
struct Comb {
  const int n;
  const T mod;
  vector<T> fac, finv;
  Comb(int n, T mod) : n(n), mod(mod) {
    fac.resize(n + 1);
    finv.resize(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
      fac[i] = fac[i - 1] * i % mod;
    }

    finv[n] = qpow(fac[n], mod - 2);
    for (int i = n; i; i--) {
      finv[i - 1] = finv[i] * i % mod;
    }
  }

  T qpow(T base, T exp) {
    T res = 1;
    while (exp) {
      if (exp & 1) {
        res = res * base % mod;
      }
      base = base * base % mod;
      exp >>= 1;
    }
    return res;
  }

  T inv(T base) { return qpow(base, mod - 2); }

  T A(int n, int m) { return fac[n] * finv[n - m] % mod; }

  T C(int n, int m) { return fac[n] * finv[n - m] % mod * finv[m] % mod; }

  T S(int n, int m) {
    T res = 0;
    int sign = -1;
    for (int k = 0; k <= m; k++) {
      sign *= -1;
      T term = sign * C(m, k) * qpow(m - k, n) % mod;
      res = (res + term + mod) % mod;
    }
    return res * finv[m] % mod;
  }
};