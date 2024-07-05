template <int mod>
struct mint {
  ll x;
  mint() {}
  mint(ll x) : x(norm(x % mod)) {}

  ll norm(ll x) {
    x += x < 0 ? mod : 0;
    x -= x >= mod ? mod : 0;
    return x;
  }
  friend mint operator+(mint lhs, mint rhs) { return lhs.x + rhs.x; }
  friend mint operator-(mint lhs, mint rhs) { return lhs.x - rhs.x; }
  friend mint operator*(mint lhs, mint rhs) { return lhs.x * rhs.x; }
  friend mint operator/(mint lhs, mint rhs) { return lhs * (rhs ^ (mod - 2)); }
  friend mint operator^(mint lhs, ll exp) {
    mint res = 1;
    for (mint base = lhs; exp > 0; base *= base, exp >>= 1) {
      if (exp & 1)
        res *= base;
    }
    return res;
  }
  mint& operator+=(mint rhs) { return *this = *this + rhs; }
  mint& operator-=(mint rhs) { return *this = *this - rhs; }
  mint& operator*=(mint rhs) { return *this = *this * rhs; }
  mint& operator/=(mint rhs) { return *this = *this / rhs; }
  mint& operator^=(ll exp) { return *this = *this ^ exp; }
  friend ostream& operator<<(ostream& os, mint rhs) { return os << rhs.x; }
  friend istream& operator>>(istream& is, mint& rhs) {
    is >> rhs.x;
    rhs = mint(rhs.x);
    return is;
  }
};