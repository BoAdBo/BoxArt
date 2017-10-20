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

typedef std::string word;

typedef std::vector<std::string> words;
typedef std::vector<std::string> sentence;
typedef std::vector<sentence> corpus;
//int count_string(std::vector<std::string>, std::vector<std::string>);
int count_string(const words & target, words::const_iterator, int, const words &);
double probablity(const words &);
double n_gram_next_word(const word &, words::const_iterator, const words &, int); // the condition expression

void test_print(const words &);

#endif
