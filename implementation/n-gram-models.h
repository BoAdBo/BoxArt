/*
  This is an implementation on n-gram-models.


 */
#include <iostream>
#include <list>
#include <vector>
const int n = 2; // The parameter n in n-gram-models
int count_string(std::vector<std::string>, std::vector<std::string>);
double probablity(const std::string &);
double n_gram(const std::string &, int n);


