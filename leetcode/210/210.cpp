class Solution {
 public:
  vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
    // We first need to construct graph, and the number of dependency of the course
    // adjency list based
    std::vector<std::vector<int>> adjList(numCourses);
    std::vector<int> numDependency(numCourses, 0);

    for (const auto& pair : prerequisites) {
      // since we are looking from dependency-free to dependency-non-free
      adjList[pair.second].push_back(pair.first);
      ++numDependency[pair.first];
    }

    std::queue<int> dependencyFree;
    std::vector<int> order;
    // find dependency-free
    for (int i = 0; i < numCourses; ++ i) {
      if (numDependency[i] == 0) {
        dependencyFree.push(i);
      }
    }

    while (!dependencyFree.empty()) {
      // since freeOne means that no one can reach them, no need to
      // keep a note about visited
      int freeOne = dependencyFree.front();
      dependencyFree.pop();
      order.push_back(freeOne);
      for (int neighbor : adjList[freeOne]) {
        --numDependency[neighbor];
        if (numDependency[neighbor] == 0) {
          dependencyFree.push(neighbor);
        }
      }
    }

    // no way to reach such order
    if (order.size() < numCourses) return {};
    else return order;
  }
};
