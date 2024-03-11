template <class T>
struct StringHash {
  T base;
  const array<T, 2> mod;
  vector<array<T, 2>> val;
  vector<array<T, 2>> pw;

  StringHash(T base) : base(base), mod(find_prime()) {
    pw.assign(1, {T(1), T(1)});
  }
  StringHash(string& s, T base) : StringHash(base) {
    calc_pw(s.size());
    hashing(s);
  }

  auto& operator[](int i) { return val[i]; }
  bool operator==(auto& b) { return val.back() == b.val.back(); }

  auto find_prime() {
    auto is_prime = [](T num) {
      for (T i = 2; i * i <= num; i++) {
        if (num % i == 0) {
          return false;
        }
      }
      return true;
    };

    mt19937 rng(time(0));
    array<T, 2> prime{T(), T()};
    while (prime[0] == prime[1]) {
      for (auto& p : prime) {
        p = rng() % (int)1e9 + 1e9;
        while (is_prime(p) == false) {
          p++;
        }
      }
    }
    return prime;
  }

  void calc_pw(int n) {
    if (n + 1 > pw.size()) {
      int prev = pw.size() - 1;
      pw.reserve(n + 1);
      for (int i = prev; i < n; i++) {
        for (int j = 0; j < 2; j++) {
          pw[i + 1][j] = pw[i][j] * base % mod[j];
        }
      }
    }
  }

  auto& hashing(string& s) {
    calc_pw(s.size());
    val.resize(s.size() + 1, {T(), T()});
    for (int i = 0; i < s.size(); i++) {
      for (int j = 0; j < 2; j++) {
        val[i + 1][j] = (val[i][j] * base + s[i]) % mod[j];
      }
    }
    return val;
  }

  auto get(int l, int r) {
    array<T, 2> res;
    for (int i = 0; i < 2; i++) {
      res[i] = (val[r][i] + (mod[i] - val[l][i]) * pw[r - l][i]) % mod[i];
    }
    return res;
  }
};