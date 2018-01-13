class Solution {
 public:
  bool find_cycle(int numCourses, const vector<list<int>> &adj, bool *visited, bool *recur_stack) {
    
  }

  bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<list<int>> adj = adj_list(numCourses, prerequisites);
    bool *visited = new bool

    for(int i = 0; i < numCourses; ++i) {
      if(find_cycle(numCourses, adj, )) {
        
      }
    }
  }

  vector<list<int>> adj_list(int numCourses, vector<pair<int, int>> &prerequisites) {
    vector<list<int>> adj(numCourses);
    for(int i = 0; i < prerequisites.size(); ++i) {
      adj[prerequisites[i].first].push_back(prerequisites[i].second);
    }

    return adj;
  }
};
