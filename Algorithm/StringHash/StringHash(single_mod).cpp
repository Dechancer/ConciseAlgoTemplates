template <class T>
struct StringHash {
  T base;
  const T mod;
  vector<T> val;
  vector<T> pw;

  StringHash(T base) : base(base), mod(find_prime()) { pw.assign(1, T(1)); }
  StringHash(string& s, T base) : StringHash(base) {
    calc_pw(s.size());
    hashing(s);
  }

  T& operator[](int i) { return val[i]; }
  bool operator==(auto& b) { return val.back() == b.val.back(); }

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

  void calc_pw(int n) {
    if (n + 1 > pw.size()) {
      for (int i = pw.size() - 1; i < n; i++) {
        pw.push_back(pw[i] * base % mod);
      }
    }
  }

  vector<T>& hashing(string& s) {
    calc_pw(s.size());
    val.resize(s.size() + 1, T());
    for (int i = 0; i < s.size(); i++) {
      val[i + 1] = (val[i] * base + s[i]) % mod;
    }
    return val;
  }

  T get(int l, int r) { return (val[r] + (mod - val[l]) * pw[r - l]) % mod; }
};