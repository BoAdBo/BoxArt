class Solution {
public:
  int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    // first build a graph, suppose it will be sparse,
    // so using a adjacency linked list here, of course we can used
    // other sparse matrix representation

    std::vector<std::vector<int>> wordGraph;
    // Do we need an extra node for initial state
    // No duplicates in the wordList, all words length are the same
    bool beginFound = (std::find(
                         std::cbegin(wordList),
                         std::cend(wordList),
                         beginWord) != std::cend(wordList));

    bool endFound = (std::find(
                       std::cbegin(wordList),
                       std::cend(wordList),
                       endWord) != std::cend(wordList));
    int beginIndex, endIndex;

    if (!beginFound) {
      wordList.push_back(std::move(beginWord));
      auto iterBegin = wordList.cend() - 1;
    }
    if (!endFound) {
      wordList.push_back(std::move(endWord));
      auto iterEnd = wordList.cend() - 1;
    }
    wordGraph.resize(wordList.size());

    // build wordGraph, since symmetric
    for (std::size_t i = 0; i < wordList.size(); ++ i) {
      for (std::size_t j = i + 1; j < wordList.size(); ++ j) {
        if (distance(wordList[i], wordList[j]) == 1) {
          wordGraph[i].push_back(j);
          wordGraph[j].push_back(i);
        }
      }
    }

    // bfs from initial state to end state
    int state = std::distance(iterBegin, std::cend(wordList));
    int goal = std::distance(iterEnd, std::cend(wordList));
    std::vector<bool> visited(wordList.size(), false);
    std::queue<int> frontTier1;
    frontTier1.push(state);
    std::queue<int> frontTier2;
    std::queue<int> *frontTier = &frontTier1;
    std::queue<int> *another = &frontTier2;
    int distance = 0;
    while (true) {
      while (!frontTier->empty()) {
        state = frontTier->front();
        frontTier->pop();
        if (state == goal) return distance;
        for (int neighbour : wordGraph[state]) {
          if (!visited[neighbour])
            another->push(neighbour);
        }
      }
      ++distance; // next front tier, distance + 1
      std::swap(frontTier, another);
      // not found
      if (frontTier->empty()) return 0;
    }
  }

  int distance(const std::string& s1, const std::string& s2) {
    assert(s1.size() == s2.size());
    int counter = 0;
    for (std::size_t i = 0; i < s1.size(); ++ i)
      if (s1[i] != s2[i]) ++counter;
    return counter;
  }
};
