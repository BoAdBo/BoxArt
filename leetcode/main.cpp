// //#include "215/215.cpp"
// #include <iostream>
// #include <string>
// #include <sstream>
// #include <cassert>
// #include <vector>
// #include <map>

// using std::vector;
// using std::string;
// using std::map;
// std::ostream & operator<<(std::ostream &os, const vector<string> &hs) {
//   for (const auto & h : hs) {
//     os << h << " ";
//   }
//   return os;
// }


// class Solution {
// public:
//   vector<string> subdomainVisits(vector<string>& cpdomains) {
//     vector<string> res;

//     for (const auto &cpdomain : cpdomains)
//       countDomain(cpdomain);

//     for (std::map<vector<string>, int>::const_iterator iter = countMap.begin(); iter != countMap.end(); ++ iter)
//       res.emplace_back(std::to_string(iter->second) + " " + bind(iter->first, '.'));

//     return res;
//   }

// private:
//   map<vector<string>, int> countMap;
//   void countDomain(const std::string &s) {
//     // first split into number and domain
//     vector<string> num_domain = split(s, ' ');
//     assert(num_domain.size() == 2);

//     string num = num_domain[0], domain = num_domain[1];
//     int count = stoi(num);

//     vector<string> subDomain = split(domain, '.');
//     for ( size_t i = 0; i < subDomain.size(); ++ i) {
//       vector<string> tmp(subDomain.begin() + i, subDomain.end());
//       auto iter = countMap.find(tmp);
//       if (iter == countMap.end()) {
//         countMap[tmp] = count;
//       }
//       else {
//         countMap[tmp] += count;
//       }

//     }
//   }

//   // similar to split, just glue strings with delim
//   static std::string bind(const vector<string> & strs, char delim) {
//     string res;
//     for (const auto& str : strs)
//       res += (str + delim);
//     // erase the final dot
//     res.pop_back();
//     return res;
//   }

//   static std::vector<std::string> split(const std::string &s, char delim) {
//     std::stringstream ss(s);
//     std::vector<std::string> elems;
//     std::string item;
//     while (std::getline(ss, item, delim)) {
//       elems.emplace_back(item);
//     }

//     return elems;
//   }
// };

// int main() {
//   Solution Testing;
//   vector<string> str = {"900 google.com", "800 planlab.com"};
//   std::cout << Testing.subdomainVisits(str) << "\n";

// }
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>

struct Counter {
  int value;

  Counter() : value(0)
  { }

  void increment() {
    ++value;
  }
};

void hello() {
  std::cout << "Hello from thread: " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
  Counter counter;
  std::vector<std::thread> threads;

  for ( size_t i = 0; i < 5; ++ i ) {
    threads.push_back(std::thread([&counter]() {
                                    for ( int i = 0; i < 100; ++ i ) {
                                      counter.increment();
                                    }
                                  }));
  }

  for ( auto &thread : threads ) {
    thread.join();
  }

  std::cout << counter.value << '\n';

  return 0;
}
