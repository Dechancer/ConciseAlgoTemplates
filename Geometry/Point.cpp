template <class T>
struct Point {
  T x, y;
  Point(T x = 0, T y = 0) : x(x), y(y) {}

  template <class U>
  operator Point<U>() {
    return Point<U>(U(x), U(y));
  }
  Point& operator+=(Point b) { return x += b.x, y += b.y, *this; }
  Point& operator-=(Point b) { return x -= b.x, y -= b.y, *this; }
  Point& operator*=(T t) { return x *= t, y *= t, *this; }
  Point& operator/=(T t) { return x /= t, y /= t, *this; }
  Point operator-() { return Point(-x, -y); }
  friend Point operator+(Point a, Point b) { return a += b; }
  friend Point operator-(Point a, Point b) { return a -= b; }
  friend Point operator*(Point a, T t) { return a *= t; }
  friend Point operator*(T t, Point b) { return b *= t; }
  friend Point operator/(Point a, T t) { return a /= t; }
  friend Point operator/(T t, Point b) { return b /= t; }
  friend bool operator==(Point a, Point b) { return a.x == b.x and a.y == b.y; }
  friend istream& operator>>(istream& is, Point& a) { return is >> a.x >> a.y; }
  friend ostream& operator<<(ostream& os, Point& a) {
    return os << '(' << a.x << ',' << a.y << ')';
  }
  friend bool operator<(const Point& a, const Point& b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
  }

  int sign() { return y > 0 or (y == 0 and x > 0) ? 1 : -1; }
  T square() { return x * x + y * y; }
  T len() { return sqrt(square()); }
  Point rotate(T r) {
    return Point(x * cos(r) - y * sin(r), x * sin(r) + y * cos(r));
  }

  friend T dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
  friend T dot(Point a, Point b, Point c) { return dot(b - a, c - a); }
  friend T cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
  friend T cross(Point a, Point b, Point c) { return cross(b - a, c - a); }
  friend T dist(Point a, Point b) { return (a - b).len(); }
  // caution, range: [0, pi]
  friend T radian(Point a, Point b) {
    return acos(dot(a, b) / a.len() / b.len());
  }
  friend bool isParallel(Point a, Point b) { return cross(a, b) == 0; }
  friend bool isPerpendicular(Point a, Point b) { return dot(a, b) == 0; }
  // return the square of dist between the closest points in the plane
  friend T colsestPoint(vector<Point>& a) {
    vector<Point> b(a.size());
    sort(a.begin(), a.end());
    auto divide = [&](auto&& self, auto l, auto r) -> T {
      if (l + 1 == r)
        return numeric_limits<T>::max();

      auto mid = l + (r - l) / 2;
      T midx = mid->x;
      T d = min(self(self, l, mid), self(self, mid, r));
      inplace_merge(l, mid, r, [&](auto& a, auto& b) { return a.y < b.y; });

      b.clear();
      auto square = [](T x) { return x * x; };
      for (auto i = l; i < r; i++) {
        if (square(i->x - midx) < d)
          b.push_back(*i);
      }
      for (int i = 0; i < b.size(); i++) {
        for (int j = i + 1; j < b.size() and square(b[j].y - b[i].y) < d; j++) {
          d = min(d, (b[j] - b[i]).square());
        }
      }
      return d;
    };
    return divide(divide, a.begin(), a.end());
  }
};