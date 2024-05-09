struct MP {
  string pat;
  vector<int> pi, match;

  MP() {}
  MP(const string& s) { init(s); }

  vector<int>& init(const string& s) {
    pat = s;
    pi.resize(pat.size());
    for (int i = 1, j = 0; i < pat.size(); i++) {
      while (j and pat[i] != pat[j]) {
        j = pi[j - 1];
      }
      j += pat[i] == pat[j];
      pi[i] = j;
    }
    return pi;
  }

  auto& run(const string& s) {
    match.resize(s.size());
    for (int i = 0, j = 0; i < s.size(); i++) {
      while (j and s[i] != pat[j]) {
        j = pi[j - 1];
      }
      j += s[i] == pat[j];
      match[i] = j;
      if (j == pat.size()) {
        j = pi[j - 1];
      }
    }
    return match;
  }
};