// a * x + b * y = c;
// solution(x, y) exists only when: c = k * gcd(a, b);
// general solution:
// xi = x0 * k + i * b / gcd(a, b);
// yi = y0 * k - i * a / gcd(a, b);

ll exgcd(ll a, ll b, ll& x, ll& y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  ll res = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return res;
}