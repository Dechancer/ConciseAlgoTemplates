template <class T>
struct StringHash {
  T base;
  const T mod;
  vector<T> hash;
  vector<T> pw;

  StringHash(T base) : base(base), mod(find_prime()) { pw.assign(1, T(1)); }
  StringHash(string& s, T base) : StringHash(base) {
    init_pw(s.size());
    hashing(s);
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

  void init_pw(int n) {
    if (n + 1 <= pw.size()) {
      return;
    }
    for (int i = pw.size() - 1; i < n; i++) {
      pw.push_back(pw[i] * base % mod);
    }
  }

  vector<T>& hashing(string& s) {
    init_pw(s.size());
    hash.resize(s.size() + 1, T());
    for (int i = 0; i < s.size(); i++) {
      hash[i + 1] = (hash[i] * base + s[i]) % mod;
    }
    return hash;
  }

  T get(int l, int r) { return (hash[r] + (mod - hash[l]) * pw[r - l]) % mod; }
};