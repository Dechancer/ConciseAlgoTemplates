template <class T, int ord>
struct Matrix : array<array<T, ord>, ord> {
  Matrix() { init({}); }
  Matrix(array<array<T, ord>, ord> a) { init(a); }

  void init(array<array<T, ord>, ord> a) { swap(*this, a); }
  void norm() {
    for (int i = 0; i < ord; i++) {
      (*this)[i][i] = 1;
    }
  }

  Matrix& operator*=(const Matrix& rhs) {
    Matrix res;
    for (int i = 0; i < ord; i++) {
      for (int k = 0; k < ord; k++) {
        for (int j = 0; j < ord; j++) {
          res[i][j] += (*this)[i][k] * rhs[k][j];
        }
      }
    }
    return *this = res;
  }
  Matrix& operator^=(auto exp) {
    Matrix res;
    res.norm();
    for (auto& base = *this; exp > 0; base *= base, exp >>= 1) {
      if (exp & 1)
        res *= base;
    }
    return *this = res;
  }
  friend Matrix operator*(Matrix lhs, const Matrix& rhs) { return lhs *= rhs; }
  friend Matrix operator^(Matrix lhs, auto exp) { return lhs ^= exp; }
};