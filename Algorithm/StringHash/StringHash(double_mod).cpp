template <class T>
struct StringHash {
  T base;
  const array<T, 2> mod;
  vector<array<T, 2>> hash;
  vector<array<T, 2>> pw;

  StringHash(T base) : base(base), mod(find_prime()) {
    pw.assign(1, {T(1), T(1)});
  }
  StringHash(string& s, T base) : StringHash(base) {
    init_pw(s.size());
    hashing(s);
  }

  auto& operator[](int i) { return hash[i]; }
  bool operator==(auto& b) { return hash.back() == b.hash.back(); }

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

  void init_pw(int n) {
    if (n + 1 <= pw.size()) {
      return;
    }
    for (int i = pw.size() - 1; i < n; i++) {
      pw.push_back(array<T, 2>());
      for (int j = 0; j < 2; j++) {
        pw[i + 1][j] = pw[i][j] * base % mod[j];
      }
    }
  }

  auto& hashing(string& s) {
    init_pw(s.size());
    hash.resize(s.size() + 1, {T(), T()});
    for (int i = 0; i < s.size(); i++) {
      for (int j = 0; j < 2; j++) {
        hash[i + 1][j] = (hash[i][j] * base + s[i]) % mod[j];
      }
    }
    return hash;
  }

  auto get(int l, int r) {
    array<T, 2> res;
    for (int i = 0; i < 2; i++) {
      res[i] = (hash[r][i] + (mod[i] - hash[l][i]) * pw[r - l][i]) % mod[i];
    }
    return res;
  }
};