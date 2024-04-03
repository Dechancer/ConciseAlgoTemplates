struct Matrix : vector<vector<ll>> {
  int r, c;
  Matrix(int r, int c) : r(r), c(c) { init(r, c); }

  void init(int r, int c) { this->assign(r, vector<ll>(c, 0)); }
};

Matrix operator*(const Matrix& a, const Matrix& b) {
  Matrix c(a.r, b.c);
  for (int i = 0; i < a.r; i++) {
    for (int j = 0; j < b.c; j++) {
      for (int k = 0; k < a.c; k++) {
        c[i][j] = (c[i][j] + a[i][k] * b[k][j]);
      }
    }
  }
  return c;
}
Matrix operator^(Matrix base, ll exp) {
  Matrix res(base.r, base.r);
  for (int i = 0; i < base.r; i++) {
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