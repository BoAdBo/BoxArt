#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <iostream>
#include <array>

template <typename N>
struct multiply_2x2 {
  using matrix = std::array<N, 4>;
  matrix operator() (const matrix &A, const matrix &B) {
    return { A[0] * B[0] + A[1] * B[2], A[0] * B[1] + A[1] * B[3],
             A[2] * B[0] + A[3] * B[2], A[2] * B[1] + A[3] * B[3]};
  }
};

template <typename N>
std::array<N, 4> identity_element(const multiply_2x2<N> &)
{ return { N(1), N(0), N(0), N(1) }; }

template <typename N>
inline bool odd(N n) {
  return (n & 0x1);
}

// template <typename InputIt, typename BinaryOperation>
// List foldr(InputIt first, InputIt last, BinaryOperation f) {
template <typename R, typename N, typename BinaryOperation>
R power_native(R Base, N n, BinaryOperation f) {
  if ( n == 0 ) { return identity_element(f); }
  R acc = Base;
  while ( n > 1 ) {
    acc = f(acc, Base);
    n--;
  }
  return acc;
}

template <typename R, typename N, typename BinaryOperation>
R power(R Base, N n, BinaryOperation f) {
  if ( n == 0 ) { return identity_element(f); }
  R acc = Base;

  while ( true ) {
    if ( odd(n) ) {
      acc = f(acc, Base);
      if ( n == 1 ) {
        return acc;
      }
    }
    // half n, double Base
    n >>= 1;
    Base = f(Base, Base);
  }

  return acc;
}

template <typename R, typename N>
R fibonacci(N n) {
  if ( n == 0 ) return R(0);
  return power(std::array<R, 4>{ 1, 1, 1, 0 }, N(n - 1), multiply_2x2<R>())[0];
}

template <typename R, typename N>
R fibonacci_naive(N n) {
  if ( n == 0 ) { return R(0); }
  else {
    // should have default constructor and constructor of int like type
    R a(1), b(0), tmp;
    while ( --n > 0 ) {
      tmp = a;
      a = a + b;
      b = tmp;
    }
    return a;
  }
}
#include <boost/multiprecision/gmp.hpp>

using namespace boost::multiprecision;

int main() {
  mpz_int v1, v2, v;

  auto start = std::chrono::high_resolution_clock::now();
  v1 = fibonacci<mpz_int, int>(100000); // prints 1000!
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << diff.count() << '\n';

  start = std::chrono::high_resolution_clock::now();
  v2 = fibonacci_naive<mpz_int, int>(100000); // prints 1000!
  end = std::chrono::high_resolution_clock::now();
  diff = end - start;
  std::cout << diff.count() << '\n';

  if ( v1 == v2 ) {
    std::cout << "success\n";
  }

  // Access the underlying representation:
  mpz_t z;
  mpz_init(z);
  mpz_set(z, v.backend().data());

  //std::cout << fibonacci(50) << '\n';
  //std::cout << fibonacci<int>(0) << '\n';
}

// struct Counter {
//   std::mutex mutex;
//   int value;

//   Counter() : value(0)
//   { }

//   void increment() {
//     //mutex.lock();
//     ++value;
//     //mutex.unlock();
//   }
// };

// void hello() {
//   std::cout << "Hello from thread: " << std::this_thread::get_id() << std::endl;
//   std::this_thread::sleep_for(std::chrono::seconds(1));
// }

// int main() {
//   Counter counter;
//   std::vector<std::thread> threads;

//   for ( size_t i = 0; i < 5; ++ i ) {
//     threads.push_back(std::thread([&counter]() {
//                                     for ( int i = 0; i < 100; ++ i ) {
//                                       counter.increment();
//                                     }
//                                     //std::cout << counter.value << std::endl;
//                                   }));
//   }

//   unsigned int n = std::thread::hardware_concurrency();
//   std::cout << n << " concurrent threads are supported.\n";

//   for ( auto &thread : threads ) {
//     thread.join();
//   }

//   return 0;
// }
