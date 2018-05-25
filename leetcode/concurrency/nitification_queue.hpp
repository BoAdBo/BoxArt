#pragma once
#include <deque>
#include <mutex>
#include <condition_variable>
#include <function>

class notification_queue {
  using namespace std;
private:
  deque<function<void()>> _q;
  mutex                   _mutex;
  condition_variable      _ready;

public:

};
