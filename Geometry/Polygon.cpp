template <class T>
struct Polygon {
  int n;
  vector<Point<T>> p;

  Polygon() {}
  Polygon(int n) { init(vector(n, Point<T>())); }
  Polygon(const vector<Point<T>>& p) { init(p); }

  void init(const vector<Point<T>>& p) {
    n = p.size();
    this->p = p;
  }
  // run getHull first
  void norm() {
    int i = 0;
    for (int j = 0; j < n; j++) {
      if (p[j].y < p[i].y or (p[j].y == p[i].y and p[j].x < p[i].x))
        i = j;
    }
    rotate(p.begin(), p.begin() + i, p.end());
  }
  void polarSort(Point<T> pivot = {}) {
    auto quad = [](auto a) {
      if (a.x > 0 and a.y >= 0)
        return 1;
      if (a.x <= 0 and a.y > 0)
        return 2;
      if (a.x < 0 and a.y <= 0)
        return 3;
      if (a.x >= 0 and a.y < 0)
        return 4;
      return 5;
    };
    sort(p.begin(), p.end(), [=](auto a, auto b) {
      a -= pivot, b -= pivot;
      if (quad(a) != quad(b))
        return quad(a) < quad(b);
      return cross(a, b) > 0;
    });
  }
  // run getHull first
  bool pointInPolygon(Point<T> a) {
    if (cross(p[0], p[1], a) < 0 or cross(p[0], p[n - 1], a) > 0)
      return false;

    int l = 0, r = n - 1;
    while (l < r) {
      int mid = (l + r + 1) / 2;
      if (cross(p[0], p[mid], a) > 0)
        l = mid;
      else
        r = mid - 1;
    }
    Line line(p[l], p[l + 1]);
    return line.pointOnLineLeft(a) or line.pointOnSegment(a);
  }
  // run getHull first
  friend bool polygonIntersectPolygon(Polygon& a, Polygon& b) {
    return any_of(a.p.begin(), a.p.end(),
                  [&](auto& x) { return b.pointInPolygon(x); }) or
           any_of(b.p.begin(), b.p.end(),
                  [&](auto& x) { return a.pointInPolygon(x); });
  }
  // run getHull first
  T getPerimeter() {
    T res{};
    for (int i = 0; i < n; i++) {
      res += dist(p[i], p[(i + 1) % n]);
    }
    return res;
  }
  // area shouldn't be taken as abs-val when calcs the center
  // area should be taken as abs-val when calcs the area
  T getArea() {
    T res{};
    for (int i = 0; i < n; i++) {
      res += cross(p[i], p[(i + 1) % n]);
    }
    return res / 2;
  }
  // run getHull first
  Point<T> getCenter() {
    Point<T> res;
    T area = getArea();
    if (area == 0)
      return res;

    for (int i = 0; i < n; i++) {
      res += (p[i] + p[(i + 1) % n]) * cross(p[i], p[(i + 1) % n]);
    }
    return res / 6 / area;
  }
  auto& getHull(const T eps = 0) {
    vector<Point<T>> h, stk;
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    h.clear();

    auto stkR = [&](int i) { return stk.rbegin()[i]; };
    auto handle = [&]() {
      stk.clear();
      for (auto& a : p) {
        while (stk.size() >= 2 and cross(stkR(1), stkR(0), a) <= eps) {
          stk.pop_back();
        }
        stk.push_back(a);
      }
      h.insert(h.end(), stk.begin(), stk.end() - 1);
    };
    handle();
    reverse(p.begin(), p.end());
    handle();
    swap(p, h);
    n = p.size();
    return p;
  }
  // shouldn't run getHull at the beginning
  bool isConvex() {
    int prev = n;
    getHull(-eps);
    return prev == n;
  }
  // run getHull first
  auto getAntiPodal() {
    vector ap(n, 0);
    for (int i = 0, j = 1; i < n; i++) {
      auto &a = p[i], &b = p[(i + 1) % n];
      while (cross(a, b, p[j]) < cross(a, b, p[(j + 1) % n])) {
        j = (j + 1) % n;
      }
      ap[i] = j;
    }
    return ap;
  }
  // return the square of diameter
  T getDiameter() {
    T res{};
    auto ap = getAntiPodal();
    for (int i = 0; i < n; i++) {
      res = max(res, (p[ap[i]] - p[i]).square());
    }
    return res;
  }
  auto getRectangularCover() {
    T res = numeric_limits<T>::max();
    array<Point<T>, 4> pos;
    auto ap = getAntiPodal();
    for (int i = 0, l = ap[0], r = 0; i < n; i++) {
      auto &a = p[i], &b = p[(i + 1) % n];
      while (dot(b, a, p[l]) < dot(b, a, p[(l + 1) % n])) {
        l = (l + 1) % n;
      }
      while (dot(a, b, p[r]) < dot(a, b, p[(r + 1) % n])) {
        r = (r + 1) % n;
      }

      Line D(a, b);
      Line L = D.getVerticalLine(p[l]), R = D.getVerticalLine(p[r]);
      Line U = D.getParallelLine(p[ap[i]]);

      Point<T> lowleft = intersection(L, D), lowright = intersection(R, D);
      Point<T> upleft = intersection(L, U), upright = intersection(R, U);
      T length = dist(lowleft, lowright), width = dist(lowleft, upleft);
      if (length * width < res) {
        res = length * width;
        pos = {lowleft, lowright, upright, upleft};
      }
    }
    return pair(res, pos);
  }
  // run getHull first
  friend auto minkowski(Polygon& a, Polygon& b) {
    vector<Point<T>> res;
    auto &p = a.p, &q = b.p;
    int n = a.n, m = b.n;
    int i = 0, j = 0;
    while (i < n or j < m) {
      res.push_back(p[i % n] + q[j % m]);
      T c = cross(p[(i + 1) % n] - p[i % n], q[(j + 1) % m] - q[j % m]);
      i += c >= 0 and i < n;
      j += c <= 0 and j < m;
    }
    return Polygon(res);
  }
  friend T dist(Polygon a, Polygon b) {
    if (polygonIntersectPolygon(a, b))
      return 0;

    for (auto& p : b.p) {
      p = -p;
    }

    auto mk = minkowski(a, b);
    T res = numeric_limits<T>::max();
    for (int i = 0; i < mk.p.size(); i++) {
      Line l(mk.p[i], mk.p[(i + 1) % mk.p.size()]);
      res = min(res, l.pointToSegment({}));
    }
    return res;
  }
};