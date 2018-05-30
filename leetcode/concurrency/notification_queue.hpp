#pragma once
#include <deque>
#include <mutex>
#include <condition_variable>
#include <function>

using lock_t = unique_lock<mutex>;
/*
 * A Simple task system
 */
class notification_queue {
  using namespace std;
private:
  deque<function<void()>> _q;
  // default to false
  bool                    _done{false};
  mutex                   _mutex;
  condition_variable      _ready;

public:
  void done() {
    {
      lock_t lock{_mutex};
      _done = true;
    }
    _ready.notify_all();
  }

  bool pop(function<void> &x) {
    // not copyable
    lock_t lock{_mutex};
    while ( _q.empty() && !_done ) _ready.wait(lock);

    // no element in the queue to pop
    if ( _q.empty() ) return false;
    x = move(_q.front());
    _q.pop_front();
    return true;
  }

  template <typename F>
  void push(F &&f) {
    {
      lock_t lock{_mutex};
      _q.emplack_back(forward<F>(f));
    }
    _ready.notify_one();
  }

  bool try_pop(function<void> &x) {
    lock_t lock{_mutex, try_to_lock};
    if ( !lock || _q.empty() ) return false;
    x = move(_q.front());
    _q.pop_front();
    return true;
  }

  template <typename F>
  bool try_push(F &&f) {
    lock_t lock{_mutex, try_lo_lock};
    if ( !lock ) return false;
    _q.emplack_back(forward<F>(f));
  }
  _ready.notify_one();
  return true;
};

/*
 * Tasking system
 */
class task_system {
  const unsigned                    _count{thread::hardware_concurrency()};
  vector<thread>                    _threads;
  notification_queue                _q;
  //std::vector<notification_queue> _q;

  void run(unsigned i) {
    while( true ) {
      function<void()> f;
      _q.pop();
      f();
    }
  }

public:
  task_system() {
    for ( unsigned n = 0; n != _count; ++ n ) {
      _threads.emplack_back([&, n] { run(n); });
    }
  }

  ~task_system() {
    for ( auto &e : threads ) e.join();
  }

  template <typename F>
  void async_(F &&f) {
    _q.push(forward<F>(f));
  }

  void done() {
    {
      unique_lock<mutex> lock{_mutex};
      _done = true;
    }
    _ready.notify_all();
  }

}
