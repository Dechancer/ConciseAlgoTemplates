struct Comb {
  int n;
  const ll mod;
  vector<ll> fac, inv_fac;
  Comb(int n, ll mod) : n(n), mod(mod) {
    fac.resize(n + 1, 1);
    inv_fac.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      fac[i] = fac[i - 1] * i % mod;
    }

    inv_fac[n] = pow(fac[n], mod - 2);
    for (int i = n; i; i--) {
      inv_fac[i - 1] = inv_fac[i] * i % mod;
    }
  }

  ll pow(ll base, ll exp) {
    ll res = 1;
    while (exp) {
      if (exp & 1) {
        res = res * base % mod;
      }
      base = base * base % mod;
      exp >>= 1;
    }
    return res;
  }

  ll A(int n, int m) { return fac[n] * inv_fac[n - m] % mod; }

  ll C(int n, int m) {
    return fac[n] * inv_fac[n - m] % mod * inv_fac[m] % mod;
  }

  ll C(int n) { return C(n * 2, n) - C(n * 2, n + 1); }

  ll s(int n, int m) {
    vector res(m + 1, 0);
    res[0] = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = min(i, m); j > 0; j--) {
        res[j] = (res[j - 1] + (i - 1) * res[j]) % mod;
      }
      res[0] = 0;
    }
    return res[m];
  }

  ll S(int n, int m) {
    ll res = 0;
    int sign = -1;
    for (int i = 0; i <= m; i++) {
      sign *= -1;
      ll term = sign * C(m, i) * pow(m - i, n) % mod;
      res = (res + term + mod) % mod;
    }
    return res * inv_fac[m] % mod;
  }
};