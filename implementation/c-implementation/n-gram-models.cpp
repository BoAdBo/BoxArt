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

// Note const words::iterator returns a const pointer, can modify what it points to

int count_string(const words& target, words::const_iterator iter_corpus, int matched_num, const words & corpus) {
  if(target.size() == matched_num) {
    return count_string(target, iter_corpus - matched_num+1, 0, corpus) + 1;
  }

  if(iter_corpus == corpus.end()) {
    return 0;
  }

  //*iter_corpus = "test";

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
  n > 1
 */

double n_gram_next_word(const word & next_word, words::const_iterator iter_sentence, const words & corpus, int n) {
  words word_context;
  words context;
  double result = 0.0;
  n--;

  //words::const_iterator end = context.end();
  //word_context.insert(word_context, begin, end);

  word_context.insert(word_context.begin(), next_word);
  while(n > 0) {
    if(iter_sentence != corpus.begin()) {
      word_context.insert(word_context.begin(), *iter_sentence);
      context.insert(context.begin(), *iter_sentence);
    }
    else {
      // reach before the beginning of sentence, insert with <s>
      // therefore need n of <s> at least before the sentence
      while(n > 0) {
        word_context.insert(word_context.begin(), "<s>");
        context.insert(context.begin(), "<s>");
        n--;
      }
      break;
    }
    n--;
    iter_sentence--;
  }

  test_print(word_context);
  test_print(context);

  int dividend = count_string(word_context, corpus.begin(), 0, corpus);
  int divider = count_string(context, corpus.begin(), 0, corpus);

  std::cout << dividend << " " << divider << '\n';

  return result = (double) dividend / (double) divider;
}

void test_print(const words & test) {
  std::cout << test.size() << '\n';
  for(int i = 0; i < test.size(); ++ i) {
    std::cout << test[i] << " ";
  }
  std::cout << '\n';
}
