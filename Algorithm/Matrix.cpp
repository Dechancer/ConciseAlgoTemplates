template <class T, int ord>
struct Matrix : vector<vector<T>> {
  Matrix() { init(vector(ord, vector(ord, T{}))); }
  Matrix(vector<vector<T>> a) { init(a); }
  void init(vector<vector<T>> a) { this->assign(a.begin(), a.end()); }

  Matrix operator*(const Matrix& a) {
    Matrix res;
    for (int i = 0; i < ord; i++) {
      for (int k = 0; k < ord; k++) {
        for (int j = 0; j < ord; j++) {
          res[i][j] = (res[i][j] + 1ll * (*this)[i][k] * a[k][j]) % mod;
        }
      }
    }
    return res;
  }

  Matrix operator^(ll exp) {
    Matrix base = *this;
    Matrix res;
    for (int i = 0; i < ord; i++) {
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