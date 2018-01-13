#include <vector>
#include <list>
#include <iostream>
using namespace std;

class Solution {
public:
  bool find_cycle(int numCourses, const vector<list<int> > &adj, bool *visited, bool *recur_stack, int current) {
    if(!visited[current]) {
      visited[current] = true;
      recur_stack[current] = true;
      list<int>::const_iterator i = adj[current].begin();
      while(i != adj[current].end()) {
        // visit descendants, if it's already been visited, which means that there is no path that include *i to current, no back edge
        if(!visited[*i]) {
          if(find_cycle(numCourses, adj, visited, recur_stack, *i)) {
            return true;
          }
        }

        // if the neighbour of current node is in the stack, there is a back edge from current node to its ancestor
        else if(recur_stack[*i]) {
          return true;
        }
        i++;
      }
    }

    recur_stack[current] = false;
    return false;
  }

  bool canFinish(int numCourses, vector<pair<int, int> >& prerequisites) {
    vector<list<int> > adj = adj_list(numCourses, prerequisites);

    // for(unsigned int i = 0; i < adj.size(); ++ i) {
    //   list<int>::const_iterator iter = adj[i].begin();
    //   while(iter != adj[i].end()) {
    //     cout << *iter << " ";

    //     ++iter;
    //   }
    //   cout << endl;

    // }

    bool *visited = new bool[numCourses];
    bool *recur_stack = new bool[numCourses];

    for(int i = 0; i < numCourses; ++ i) {
      visited[i] = false;
      recur_stack[i] = false;
    }

    for(int i = 0; i < numCourses; ++i) {
      if(find_cycle(numCourses, adj, visited, recur_stack, i)) {
        return false;
      }
    }

    return true;
  }

  vector<list<int> > adj_list(int numCourses, vector<pair<int, int> > &prerequisites) {
    vector<list<int> > adj(numCourses);
    for(unsigned int i = 0; i < prerequisites.size(); ++i) {
      adj[prerequisites[i].first].push_back(prerequisites[i].second);
    }

    return adj;
  }
};

int main() {
  Solution sol;
  vector<pair<int, int> > prerequisites;
  prerequisites.push_back(pair<int,int>(0,1));
  prerequisites.push_back(pair<int,int>(1,0));

  cout << sol.canFinish(2, prerequisites);
}
