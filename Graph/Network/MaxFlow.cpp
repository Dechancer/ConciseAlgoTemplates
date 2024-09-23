template <class T>
struct Net {
  struct edge {
    int to;
    T cap;
    edge(int to, T cap) : to(to), cap(cap) {}
  };

  const T inf = numeric_limits<T>::max();
  int n;
  vector<edge> e;
  vector<vector<int>> adj;
  vector<int> cur, h;

  Net() {}
  Net(int n) { init(n); }

  void init(int n) {
    this->n = n;
    e.clear();
    adj.assign(n, {});
    cur.resize(n);
    h.resize(n);
  }

  void addEdge(int u, int v, T c) {
    adj[u].push_back(e.size());
    e.emplace_back(v, c);
    adj[v].push_back(e.size());
    e.emplace_back(u, 0);
  }

  bool bfs(int s, int t) {
    h.assign(n, -1);
    h[s] = 0;
    queue q(deque(1, s));
    while (q.size()) {
      int u = q.front();
      q.pop();
      for (int i : adj[u]) {
        auto [v, c] = e[i];
        if (c > 0 and h[v] == -1) {
          h[v] = h[u] + 1;
          if (v == t)
            return true;
          q.push(v);
        }
      }
    }
    return false;
  }
  T dfs(int u, int t, T f) {
    if (u == t)
      return f;

    T r = f;
    for (int& i = cur[u]; i < adj[u].size(); i++) {
      int j = adj[u][i];
      auto [v, c] = e[j];
      if (c > 0 and h[v] == h[u] + 1) {
        T a = dfs(v, t, min(r, c));
        e[j].cap -= a;
        e[j ^ 1].cap += a;
        r -= a;
        if (r == 0)
          return f;
      }
    }
    return f - r;
  }
  T flow(int s, int t) {
    T f = 0;
    while (bfs(s, t)) {
      cur.assign(n, 0);
      f += dfs(s, t, inf);
    }
    return f;
  }

  vector<bool> minCut() {
    vector<bool> c(n);
    for (int i = 0; i < n; i++) {
      c[i] = (h[i] != -1);
    }
    return c;
  }

  struct Edge {
    int from, to;
    T cap, flow;
  };
  vector<Edge> edges() {
    vector<Edge> a;
    for (int i = 0; i < e.size(); i += 2) {
      Edge x;
      x.from = e[i + 1].to;
      x.to = e[i].to;
      x.cap = e[i].cap + e[i + 1].cap;
      x.flow = e[i + 1].cap;
      a.push_back(x);
    }
    return a;
  }
};