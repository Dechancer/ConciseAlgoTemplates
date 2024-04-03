struct MP {
  string s;
  vector<int> pi;

  MP(const string& s) { init(s); }

  void init(const string& s) {
    this->s = s;
    pi.resize(s.size());
    for (int i = 1, j = 0; i < s.size(); i++) {
      while (j and s[i] != s[j]) {
        j = pi[j - 1];
      }
      j += s[i] == s[j];
      pi[i] = j;
    }
  }

  void match(string& t) {
    for (int i = 0, j = 0; i < s.size(); i++) {
      while (j and s[i] != t[j]) {
        j = pi[j - 1];
      }
      j += s[i] == t[j];
      if (j == t.size()) {
        foundIt(i, j);
        j = pi[j - 1];
      }
    }
  }

  void foundIt(int i, int len) {}
};