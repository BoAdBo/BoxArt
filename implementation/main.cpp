#include "n-gram-models.h"

void get_test(words & target, words & corpus, const std::string & file_target, const std::string & file_corpus) {
  std::ifstream input_file;
  input_file.open(file_target.c_str());

  std::string temp;
  while(input_file >> temp) {
    target.push_back(temp);
  }

  input_file.close();

  input_file.open(file_corpus.c_str());
  while(input_file >> temp) {
    corpus.push_back(temp);
  }

  input_file.close();
  return;
}

int main(int argc, char * argv[]) {
  std::string file_target = argv[1];
  std::string file_corpus = argv[2];

  std::vector<std::string> target;
  std::vector<std::string> corpus;
  get_test(target, corpus, file_target, file_corpus);
  //std::cout << file_target << " " << file_corpus << '\n';

  // for(int i = 0; i < target.size(); ++ i) {
  //   std::cout << target[i] << " ";
  // }
  // std::cout << "\n";

  // for(int i = 0; i < corpus.size(); ++ i) {
  //   std::cout << corpus[i] << " ";
  // }
  // std::cout << "\n";
  std::cout << count_string(target, corpus.begin(), 0, corpus);
}
