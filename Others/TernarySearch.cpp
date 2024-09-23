// a conservative way to do float search is to run a constant times loop
template <class T>
T ternarySearch(T l, T r, auto&& pred, T eps = 1) {
  while (l + eps < r) {
    T mid = (l + r) / 2;
    T m0 = mid - eps, m1 = mid + eps;
    if (pred(m0, m1))
      // if m1 is better
      l = mid;
    else
      r = mid;
  }
  return pred(l, r) ? r : l;
}