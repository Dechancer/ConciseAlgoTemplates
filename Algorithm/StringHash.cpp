struct StringHash : vector<int> {
  const ll base;
  const ll mod;
  vector<int> pw;
  StringHash& hash = *this;

  StringHash() : base(findPrime(1e4)), mod(findPrime(1e9)) {}
  StringHash(const string& s) : StringHash() { init(s); }

  int findPrime(int mag) {
    auto isPrime = [](int num) {
      for (ll i = 2; i * i <= num; i++) {
        if (num % i == 0)
          return false;
      }
      return true;
    };

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int prime = rng() % mag + mag;
    while (isPrime(prime) == false) {
      prime++;
    }
    return prime;
  }

  vector<int>& init(const string& s) {
    int n = s.size();
    pw.resize(n + 1, 1);
    for (int i = 0; i < n; i++) {
      pw[i + 1] = pw[i] * base % mod;
    }
    hash.resize(n + 1);
    for (int i = 0; i < n; i++) {
      hash[i + 1] = (hash[i] * base + s[i]) % mod;
    }
    return hash;
  }

  int get(int l, int r) {
    return (hash[r] + (mod - hash[l]) * pw[r - l]) % mod;
  }
};