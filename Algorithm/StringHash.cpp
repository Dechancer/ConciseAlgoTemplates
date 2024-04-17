struct StringHash : vector<ull> {
  const ull base;
  vector<ull> pw;
  StringHash& hash = *this;

  StringHash() : base(findPrime()) {}
  StringHash(const string& s) : base(findPrime()) { init(s); }

  ull findPrime() {
    auto isPrime = [](ull num) {
      for (ull i = 2; i * i <= num; i++) {
        if (num % i == 0) {
          return false;
        }
      }
      return true;
    };

    mt19937_64 rng(time(0));
    ull prime = rng() % (int)1e9 + 1e9;
    while (isPrime(prime) == false) {
      prime++;
    }
    return prime;
  }

  vector<ull>& init(const string& s) {
    int n = s.size();
    pw.resize(n + 1, 1);
    for (int i = 0; i < n; i++) {
      pw[i + 1] = pw[i] * base;
    }
    hash.resize(n + 1);
    for (int i = 0; i < n; i++) {
      hash[i + 1] = hash[i] * base + s[i];
    }
    return hash;
  }

  ull get(int l, int r) { return hash[r] - hash[l] * pw[r - l]; }
};