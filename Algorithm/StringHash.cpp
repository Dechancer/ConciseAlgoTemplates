struct StringHash : vector<ll> {
  const int base;
  const int mod;
  vector<ll> pw;
  StringHash& hash = *this;

  StringHash() : base(findPrime(1e4)), mod(findPrime(1e9)) {}
  StringHash(const string& s) : StringHash() { init(s); }

  ll findPrime(int mag) {
    auto isPrime = [](ll num) {
      for (ll i = 2; i * i <= num; i++) {
        if (num % i == 0) {
          return false;
        }
      }
      return true;
    };

    mt19937 rng(time(0));
    ll prime = rng() % mag + mag;
    while (isPrime(prime) == false) {
      prime++;
    }
    return prime;
  }

  vector<ll>& init(const string& s) {
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

  ll get(int l, int r) { return (hash[r] + (mod - hash[l]) * pw[r - l]) % mod; }
};