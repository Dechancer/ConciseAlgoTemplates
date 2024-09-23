using u32 = unsigned;
using u64 = unsigned long long;
template <class U, U mod>
struct mint {
  static U smod;
  U x = 0;
  mint() {}
  template <class T>
  mint(T x) : x(norm(x % T(Mod()))) {}

  static void setMod(U smod) { mint::smod = smod; }
  U Mod() { return mod ? mod : smod; }
  U norm(U x) {
    x += x >> (8 * sizeof(U) - 1) & 1 ? Mod() : 0;
    x -= x >= Mod() ? Mod() : 0;
    return x;
  }
  u32 mul(u32 a, u32 b) { return 1ull * a * b % Mod(); }
  u64 mul(u64 a, u64 b) {
    return u64(a * b - u64(1.l * a * b / Mod() - 0.5l) * Mod()) % Mod();
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
};
template <class U, U mod>
U mint<U, mod>::smod;