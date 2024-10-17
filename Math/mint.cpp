using u32 = unsigned;
using u64 = unsigned long long;
template <class T, T mod>
struct mint {
  static T smod;
  T x = 0;
  mint() {}
  mint(auto x) : x(norm(x % (signed)Mod())) {}

  static void setMod(T smod) { mint::smod = smod; }
  T Mod() { return mod ? mod : smod; }
  T norm(T x) {
    x += x >> (8 * sizeof(T) - 1) & 1 ? Mod() : 0;
    x -= x >= Mod() ? Mod() : 0;
    return x;
  }
  u32 mul(u32 a, u32 b) { return 1ull * a * b % Mod(); }
  u64 mul(u64 a, u64 b) {
    return (a * b - u64(1.l * a * b / Mod() - 0.5l) * Mod()) % Mod();
  }
  mint inv() { return (*this) ^ Mod() - 2; }
  mint& operator+=(mint r) { return x = norm(x + r.x), *this; }
  mint& operator-=(mint r) { return x = norm(x - r.x), *this; }
  mint& operator*=(mint r) { return x = mul(x, r.x), *this; }
  mint& operator/=(mint r) { return *this *= r.inv(); }
  mint& operator^=(auto exp) {
    mint res(1);
    for (mint& base = *this; exp > 0; base *= base, exp /= 2) {
      if (exp & 1)
        res *= base;
    }
    return *this = res;
  }
  friend mint operator+(mint l, mint r) { return l += r; }
  friend mint operator-(mint l, mint r) { return l -= r; }
  friend mint operator*(mint l, mint r) { return l *= r; }
  friend mint operator/(mint l, mint r) { return l /= r; }
  friend mint operator^(mint l, auto exp) { return l ^= exp; }
  friend ostream& operator<<(ostream& os, mint r) { return os << r.x; }
  friend istream& operator>>(istream& is, mint& r) {
    return is >> r.x, r = r.x, is;
  }
};
template <class T, T mod>
T mint<T, mod>::smod;