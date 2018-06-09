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
