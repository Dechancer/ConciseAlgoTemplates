template <class T>
struct Matrix {
  int r, c;
  const T mod;
  vector<vector<T>> mat;

  Matrix(int r, int c, T mod) : r(r), c(c), mod(mod) {
    mat = vector(r, vector(c, T()));
  }

  vector<T>& operator[](int i) { return mat[i]; }

  void operator=(const Matrix& b) {
    r = b.r, c = b.c;
    mat = b.mat;
  }

  Matrix operator*(const Matrix& b) {
    Matrix res(r, b.c, mod);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < b.c; j++) {
        for (int k = 0; k < c; k++) {
          res[i][j] = (res[i][j] + 1ll * mat[i][k] * b.mat[k][j]) % mod;
        }
      }
    }
    return res;
  }

  template <class EXP>
  Matrix operator^(EXP exp) {
    Matrix res(r, c, mod);
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