template <class T>
struct StringHash {
  T base;
  const T mod;
  vector<T> hash;
  vector<T> pw;

  StringHash(T base) : base(base), mod(find_prime()) { pw.assign(1, 1); }
  StringHash(const string& s, T base) : StringHash(base) { init(s); }

  auto& init(const string& s) {
    int n = s.size();
    if (n + 1 > pw.size()) {
      for (int i = pw.size() - 1; i < n; i++) {
        pw.push_back(pw[i] * base % mod);
      }
    }

    hash.resize(n + 1);
    for (int i = 0; i < n; i++) {
      hash[i + 1] = (hash[i] * base + s[i]) % mod;
    }
    return hash;
  }

  T& operator[](int i) { return hash[i]; }
  bool operator==(auto& b) { return hash.back() == b.hash.back(); }

  T find_prime() {
    auto is_prime = [](T num) {
      for (T i = 2; i * i <= num; i++) {
        if (num % i == 0) {
          return false;
        }
      }
      return true;
    };

    mt19937 rng(time(0));
    T prime = rng() % (int)1e9 + 1e9;
    while (is_prime(prime) == false) {
      prime++;
    }
    return prime;
  }

  T get(int l, int r) { return (hash[r] + (mod - hash[l]) * pw[r - l]) % mod; }
};