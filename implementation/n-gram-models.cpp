#include "n-gram-models.h"

int count_string(std::vector<std::string> target, std::vector<std::string> corpus) {
  int count = 0;
  for(int i = 0; i < corpus.size(); ++i) {
    if(target[0] == corpus[i]) {
      //std::cout << "hit" << '\n';
      bool is_matched = true;
      int j = 1;
      for(int ii = i+1; j < target.size() && ii < corpus.size(); ++ j, ++ ii) {
        if(target[j] != corpus[ii]) {
          is_matched = false;
        }
      }
      if(is_matched && j+1 == target.size()) {
        count++;
      }
    }
  }
  return count;
}

int main(int argc, char * argv[]) {
  std::vector<std::string> target;
  std::vector<std::string> corpus;
  target.push_back("hello");
  target.push_back("good");
  target.push_back("hell");

  corpus.push_back("you");
  corpus.push_back("hello");
  corpus.push_back("good");
  corpus.push_back("hell");
  corpus.push_back("hello");
  corpus.push_back("good");
  std::cout << count_string(target, corpus) ;
}
