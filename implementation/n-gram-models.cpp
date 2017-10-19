#include "n-gram-models.h"

// int count_string(const words target, const words corpus) {
//   int count = 0;
//   for(int i = 0; i < corpus.size(); ++i) {
//     if(target[0] == corpus[i]) {
//       std::cout << "hit" << '\n';
//       bool is_matched = true;
//       int j = 1;
//       for(int ii = i+1; j < target.size() && ii < corpus.size(); ++ j, ++ ii) {
//         if(target[j] != corpus[ii]) {
//           is_matched = false;
//         }
//       }
//       if(is_matched && j+1 == target.size()) {
//         count++;
//       }
//     }
//   }
//   return count;
// }

int count_string(const words& target, const words::iterator iter_corpus, int matched_num, const words & corpus) {
  if(target.size() == matched_num) {
    return count_string(target, iter_corpus - matched_num+1, 0, corpus) + 1;
  }

  if(iter_corpus == corpus.end()) {
    return 0;
  }

  if(target[matched_num] == *iter_corpus) {
    count_string(target, iter_corpus+1, matched_num+1, corpus);
  }
  else {// since we have moved from matched_num from previous iter_corpus, come back after the origin + 1
    count_string(target, iter_corpus - matched_num+1, 0, corpus);
  }
}

/*
  The condition probablity of n gram model

  The implementation is simply count the two strings and divide, which require whoever calls it give the context and the word to it.
 */

double n_gram_next_word(const words & next_word, const words & context, const words & corpus, int n) {
  words word_context = next_word;
  words::const_iterator begin = context.begin();
  words::const_iterator end = context.end();
  word_context.insert(word_context, begin, end);

  int dividend = count_string(word_context);
  int divider = count_string(context);

  return result = (double) dividend / (double);
}
