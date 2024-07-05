struct Z {
  vector<int> z;

  Z() {}
  Z(const string& s) { init(s); }

  vector<int>& init(const string& s) {
    int n = s.size();
    z.resize(n + 1);
    z[0] = n;
    for (int i = 1, j = 1; i < n; i++) {
      z[i] = max(0, min(j + z[j] - i, z[i - j]));
      while (i + z[i] < n and s[z[i]] == s[i + z[i]]) {
        z[i]++;
      }
      if (i + z[i] > j + z[j]) {
        j = i;
      }
    }
    return z;
  }
};