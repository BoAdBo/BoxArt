// fastest 12ms code from server
static auto _ = []() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}();

class Solution {
public:
  static const int MAXN = 5000;
  int head[MAXN], cnt = 0;
  int vis[MAXN], in[MAXN];
  void init() {
    cnt = 0;
    memset(in, 0, sizeof(in));
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
  }

  struct Edge {
    int from;
    int to;
    int next;
  } edge[MAXN * 2];

  void add(int from, int to) {
    edge[cnt].from = from;
    edge[cnt].to = to;
    edge[cnt].next = head[from];
    head[from] = cnt++;
  }

  vector<int> findOrder(int numCourses, vector<pair<int, int>> &prerequisites) {
    vector<int> ans;
    init();
    int n = prerequisites.size();
    for (int i = 0; i < n; ++i) {
      add(prerequisites[i].second, prerequisites[i].first);
    }
    for (int i = 0; i < n; ++i) {
      ++in[prerequisites[i].first];
    }
    queue<int> bfs;
    for (int i = 0; i < numCourses; ++i) {
      if (in[i] == 0)
        bfs.push(i);
    }
    while (!bfs.empty()) {
      int node = bfs.front();
      bfs.pop();
      ans.push_back(node);
      for (int i = head[node]; i != -1; i = edge[i].next) {
        --in[edge[i].to];
        if (in[edge[i].to] <= 0)
          bfs.push(edge[i].to);
        if (edge[i].from != node)
          break;
      }
    }
    if (ans.size() != numCourses)
      return vector<int>();
    return ans;
  }
};
