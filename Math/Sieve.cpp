vector<int> minp, prime;
void sieve(int n) {
  minp.assign(n + 1, 0);
  prime.clear();

  for (int i = 2; i <= n; i++) {
    if (minp[i] == 0) {
      minp[i] = i;
      prime.emplace_back(i);
    }

    for (int j = 0; i * prime[j] <= n; j++) {
      minp[i * prime[j]] = prime[j];
      if (prime[j] == minp[i])
        break;
    }
  }
}