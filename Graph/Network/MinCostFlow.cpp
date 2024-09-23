template <class T>
struct Net {
  struct edge {
    int to;
    T cap, cost;
    edge(int to, T cap, T cost) : to(to), cap(cap), cost(cost) {}
  };

  const T inf = numeric_limits<T>::max();
  int n;
  vector<edge> e;
  vector<vector<int>> g;
  vector<T> h, dist;
  vector<int> pre;

  Net() {}
  Net(int n) { init(n); }

  void init(int n) {
    this->n = n;
    e.clear();
    g.assign(n, {});
    h.resize(n);
    dist.resize(n);
    pre.resize(n);
  }

  void addEdge(int u, int v, T cap, T cost) {
    g[u].push_back(e.size());
    e.emplace_back(v, cap, cost);
    g[v].push_back(e.size());
    e.emplace_back(u, 0, -cost);
  }

  bool bfs(int s, int t) {
    dist.assign(n, inf);
    pre.assign(n, -1);
    priority_queue q{greater(), vector{pair(T(), s)}};
    dist[s] = 0;
    while (q.size()) {
      auto [d, u] = q.top();
      q.pop();
      if (dist[u] < d)
        continue;
      for (int& i : g[u]) {
        auto& [v, cap, cost] = e[i];
        if (cap > 0 and dist[v] > d + cost + h[u] - h[v]) {
          dist[v] = d + cost + h[u] - h[v];
          pre[v] = i;
          q.emplace(dist[v], v);
        }
      }
    }
    return dist[t] != inf;
  }

  T dfs(int s, int t) {
    T aug = inf;
    for (int u = t; u != s; u = e[pre[u] ^ 1].to) {
      aug = min(aug, e[pre[u]].cap);
    }
    for (int u = t; u != s; u = e[pre[u] ^ 1].to) {
      e[pre[u]].cap -= aug;
      e[pre[u] ^ 1].cap += aug;
    }
    for (int u = 0; u < n; u++) {
      h[u] += dist[u];
    }
    return aug;
  }

  pair<T, T> flow(int s, int t) {
    T flow = 0, cost = 0;
    h.assign(n, 0);
    while (bfs(s, t)) {
      T aug = dfs(s, t);
      flow += aug;
      cost += aug * h[t];
    }
    return {flow, cost};
  }

  T flow(int s, int t, T flow) {
    T cost = 0;
    h.assign(n, 0);
    while (flow > 0 and bfs(s, t)) {
      T aug = dfs(s, t);
      flow -= aug;
      cost += aug * h[t];
    }
    return flow > 0 ? -1 : cost;
  }
};