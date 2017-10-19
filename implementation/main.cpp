#include "n-gram-models.h"

int main(int argc, char * argv[]) {
  std::vector<std::string> target;
  std::vector<std::string> corpus;
  target.push_back("hello");
  corpus.push_back("you");
  corpus.push_back("hello");
  std::cout << count_string(target, corpus) ;
}
