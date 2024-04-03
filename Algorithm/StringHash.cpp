struct StringHash : vector<ll> {
  ll base;
  const ll mod;
  vector<ll> pw;
  StringHash& hash = *this;

  StringHash(ll base) : base(base), mod(findPrime()) { pw.assign(1, 1); }
  StringHash(const string& s, ll base) : StringHash(base) { init(s); }

  ll findPrime() {
    auto isPrime = [](ll num) {
      for (ll i = 2; i * i <= num; i++) {
        if (num % i == 0) {
          return false;
        }
      }
      return true;
    };

    mt19937_64 rng(time(0));
    ll prime = rng() % (int)1e9 + 1e9;
    while (isPrime(prime) == false) {
      prime++;
    }
    return prime;
  }

  vector<ll>& init(const string& s) {
    int n = s.size(), m = pw.size();
    if (n >= m) {
      pw.resize(n + 1);
      for (int i = m - 1; i < n; i++) {
        pw[i + 1] = pw[i] * base % mod;
      }
    }
    hash.resize(n + 1);
    for (int i = 0; i < n; i++) {
      hash[i + 1] = (hash[i] * base + s[i]) % mod;
    }
    return hash;
  }

  ll get(int l, int r) { return (hash[r] + (mod - hash[l]) * pw[r - l]) % mod; }
};