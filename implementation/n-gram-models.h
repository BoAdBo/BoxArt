/*
  This is an implementation on n-gram-models.


 */
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#ifndef N_GRAM_MODELS
#define N_GRAM_MODELS
const int n = 2; // The parameter n in n-gram-models
typedef std::vector<std::string> words;
//int count_string(std::vector<std::string>, std::vector<std::string>);
int count_string(const words & target, const words::iterator, int, const words &);
double probablity(const words &);
double n_gram_next_word(const words &, const words &, const words & corpus, int); // the condition expression

#endif
