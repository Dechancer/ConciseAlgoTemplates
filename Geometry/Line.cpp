template <class T>
struct Line {
  Point<T> a, b;
  Line(Point<T> a = {}, Point<T> b = {}) : a(a), b(b) {}

  friend bool operator<(const Line& u, const Line& v) {
    return u.a != v.a ? u.a < v.a : u.b < v.b;
  }

  Line rotate(T r, Point<T> pivot) {
    return Line(pivot, pivot + (b - a).rotate(r));
  }
  Line getVerticalLine(Point<T> p) { return rotate(pi / 2, p); }
  Line getParallelLine(Point<T> p) { return rotate(0, p); }
  friend bool isParallel(Line u, Line v) {
    return isParallel(u.b - u.a, v.b - v.a);
  }
  friend bool isPerpendicular(Line u, Line v) {
    return isPerpendicular(u.b - u.a, v.b - v.a);
  }
  friend bool isCollinear(Line u, Line v) {
    return cross(u.a, u.b, v.a) == 0 and cross(u.a, u.b, v.b) == 0;
  }
  bool pointOnLine(Point<T> p) { return cross(a, b, p) == 0; }
  bool pointOnLineLeft(Point<T> p) { return cross(a, b, p) > 0; }
  bool pointOnLineRight(Point<T> p) { return cross(a, b, p) < 0; }
  bool pointOnSegment(Point<T> p) {
    return pointOnLine(p) and min(a.x, b.x) <= p.x and p.x <= max(a.x, b.x) and
           min(a.y, b.y) <= p.y and p.y <= max(a.y, b.y);
  }
  friend bool lineIntersectLine(Line u, Line v) { return !isParallel(u, v); }
  friend bool lineIntersectSegment(Line u, Line v) {
    if (isParallel(u, v))
      return u.pointOnSegment(v.a) or u.pointOnSegment(v.b);
    return cross(u.b - u.a, v.a - u.a) * cross(u.b - u.a, v.b - u.b) <= 0;
  }
  friend bool segmentIntersectSegment(Line u, Line v) {
    return lineIntersectSegment(u, v) and lineIntersectSegment(v, u);
  }
  T pointToLine(Point<T> p) { return abs(cross(a, b, p)) / (b - a).len(); }
  T pointToSegment(Point<T> p) {
    T res = min(dist(a, p), dist(b, p));
    Line l = getVerticalLine(p);
    if (lineIntersectSegment(l, *this))
      res = min(res, pointToLine(p));
    return res;
  }
  friend T segmentToSegment(Line u, Line v) {
    if (segmentIntersectSegment(u, v))
      return 0;
    return min({u.pointToSegment(v.a), u.pointToSegment(v.b),
                v.pointToSegment(u.a), v.pointToSegment(u.b)});
  }
  friend Point<T> intersection(Line u, Line v) {
    return u.a + (u.b - u.a) * (cross(v.b - v.a, u.a - v.a) /
                                cross(v.b - v.a, u.a - u.b));
  }
};