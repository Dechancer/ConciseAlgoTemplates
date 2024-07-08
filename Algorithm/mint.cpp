template <int mod>
struct mint {
  int x = 0;
  mint() {}
  mint(ll x) : x(norm(x % mod)) {}

  int norm(int x) {
    x += x < 0 ? mod : 0;
    x -= x >= mod ? mod : 0;
    return x;
  }
  mint& operator+=(mint rhs) { return x = norm(x + rhs.x), *this; }
  mint& operator-=(mint rhs) { return x = norm(x - rhs.x), *this; }
  mint& operator*=(mint rhs) { return x = 1ll * x * rhs.x % mod, *this; }
  mint& operator/=(mint base) { return *this *= base ^= mod - 2; }
  mint& operator^=(ll exp) {
    mint res(1);
    for (mint& base = *this; exp > 0; base *= base, exp /= 2) {
      if (exp & 1)
        res *= base;
    }
    return *this = res;
  }
  friend mint operator+(mint lhs, mint rhs) { return lhs += rhs; }
  friend mint operator-(mint lhs, mint rhs) { return lhs -= rhs; }
  friend mint operator*(mint lhs, mint rhs) { return lhs *= rhs; }
  friend mint operator/(mint lhs, mint rhs) { return lhs /= rhs; }
  friend mint operator^(mint lhs, ll exp) { return lhs ^= exp; }
  friend ostream& operator<<(ostream& os, mint rhs) { return os << rhs.x; }
  friend istream& operator>>(istream& is, mint& rhs) {
    ll x;
    cin >> x;
    rhs = mint(x);
    return is;
  }
};