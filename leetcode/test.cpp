#include <iostream>
#include <queue>
#include <vector>
#include <stdio.h>

class comp {
public:
  comp() {}
  bool operator() (const int a, const int b) {
    return a > b;
  }
};

int main() {
  int arrays[] = {10, 60, 50, 20};
  std::priority_queue<int, std::vector<int>, comp> pq;
  for(int i = 0; i < 4; ++ i) {
    pq.push(arrays[i]);
  }

  while(!pq.empty()) {
    printf("%d", pq.top());
    pq.pop();
  }
}
