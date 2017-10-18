#include "n-gram-models.h"

int count_string(const string * target, const string * corpus, int matched_count, int need_match) {
  if(matched_count < need_match) {
    if(target == *corpus) {
      return count_string(target, corpus+1, matched_count, need_match) + 1;
    }
    else {
      return count_string(target, corpus+1, 0, need_match);
    }
  }
  else {
    
  }
}
