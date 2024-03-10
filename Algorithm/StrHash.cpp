template <class T>
struct StrHash {
  T base;
  const T mod;
  vector<T> pw;

  StrHash(T base, int n) : StrHash(base) {
    pw.resize(n + 1);
    pw[0] = 1;
    for (int i = 0; i < n; i++) {
      pw[i + 1] = pw[i] * base % mod;
    }
  }

  StrHash(T base) : base(base), mod(find_prime()) {}

  T find_prime() {
    mt19937 rng(time(0));
    T prime = rng() % (int)1e9 + 1e9;
    while (is_prime(prime) == false) {
      prime++;
    }
    return prime;
  }

  bool is_prime(T num) {
    for (T i = 2; i * i <= num; i++) {
      if (num % i == 0) {
        return false;
      }
    }
    return true;
  }

  auto hashing(string& s) {
    vector hash(s.size() + 1, T());
    for (int i = 0; i < s.size(); i++) {
      hash[i + 1] = (hash[i] * base + s[i]) % mod;
    }
    return hash;
  }

  auto multi_hashing(string& s, const vector<T>& mods) {
    vector hashs(mods.size(), vector(s.size() + 1, T()));
    for (int i = 0; i < mods.size(); i++) {
      for (int j = 0; j < s.size(); j++) {
        hashs[i][j + 1] = (hashs[i][j] * base + s[j]) % mods[i];
      }
    }
    return hashs;
  }

  ll val(vector<ll>& hash, int l, int r) {
    return (hash[r] + (mod - hash[l]) * pw[r - l]) % mod;
  }
};