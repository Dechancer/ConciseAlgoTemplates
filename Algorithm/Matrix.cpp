template <class T>
struct Matrix {
  int r, c;
  const T mod;
  const T init;
  vector<vector<T>> a;

  Matrix(int r, int c, T mod, T init) : r(r), c(c), mod(mod), init(init) {
    a = vector(r, vector(c, init));
  }

  Matrix(int r, int c, T mod, vector<vector<T>> init)
      : r(r), c(c), mod(mod), init(T()), a(init) {}

  vector<T>& operator[](int i) { return a[i]; }

  void operator=(const Matrix& b) {
    r = b.r, c = b.c;
    a = b.a;
  }

  Matrix operator*(Matrix b) {
    Matrix res(r, b.c, mod, init);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < b.c; j++) {
        for (int k = 0; k < c; k++) {
          res[i][j] = (res[i][j] + 1ll * a[i][k] * b[k][j]) % mod;
        }
      }
    }
    return res;
  }

  template <class EXP>
  Matrix operator^(EXP exp) {
    Matrix res(r, c, mod, init);
    Matrix base = *this;
    for (int i = 0; i < r; i++) {
      res[i][i] = 1;
    }
    while (exp) {
      if (exp & 1) {
        res = res * base;
      }
      base = base * base;
      exp >>= 1;
    }
    return res;
  }
};