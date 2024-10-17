template <class T>
T randomPrime(T mag) {
  mt19937 rng(random_device{}());

  auto isPrime = [](T num) {
    for (T i = 2; i * i <= num; i++) {
      if (num % i == 0) {
        return false;
      }
    }
    return true and num > 1;
  };

  T p = rng() % mag + mag;
  while (isPrime(p) == false) {
    p++;
  }
  return p;
}

template <class T, auto base>
struct StringHash {
  vector<T> pw, hash;

  StringHash() : pw(1, T(1)) {}
  StringHash(const string& s) : StringHash() { init(s); }

  vector<T>& init(const string& s) {
    int n = s.size();
    while (pw.size() <= n) {
      pw.emplace_back(pw.back() * base);
    }
    hash.resize(n + 1);
    for (int i = 0; i < n; i++) {
      hash[i + 1] = hash[i] * base + s[i];
    }
    return hash;
  }

  T get(int l, int r) { return hash[r] - hash[l] * pw[r - l]; }
};