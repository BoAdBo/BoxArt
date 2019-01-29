// #include <iostream>
// #include <condition_variable>
// #include <thread>
// #include <chrono>

// std::condition_variable cv;
// std::mutex cv_m; // This mutex is used for three purposes:
//                  // 1) to synchronize accesses to i
//                  // 2) to synchronize accesses to std::cerr
//                  // 3) for the condition variable cv
// int i = 0;

// void waits()
// {
//     std::unique_lock<std::mutex> lk(cv_m);
//     std::cerr << "Waiting... \n";
//     cv.wait(lk, []{return i == 1;});
//     std::cerr << "...finished waiting. i == 1\n";
// }


// void signals()
// {
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     {
//         std::lock_guard<std::mutex> lk(cv_m);
//         std::cerr << "Notifying...\n";
//     }
//     cv.notify_all();

//     std::this_thread::sleep_for(std::chrono::seconds(1));

//     {
//         std::lock_guard<std::mutex> lk(cv_m);
//         i = 1;
//         std::cerr << "Notifying again...\n";
//     }
//     cv.notify_all();
// }

// int main()
// {
//     std::thread t1(waits), t2(waits), t3(waits), t4(signals);
//     t1.join();
//     t2.join();
//     t3.join();
//     t4.join();
// =======
// #include "include/predefined.hpp"
// #include "72/72.cpp"

// int main() {
//   Solution test;
//   string a = "abs";
//   string b = "abc";

//   cout << test.minDistance(a, b) << '\n';
// >>>>>>> d84eb18b19abbd29b89b740c705fb687173d87eb
// }

// #include "include/predefined.hpp"
// #include "23/23.hpp"
// int main() {
//   Solution test;
//   ListNode *head1 = new ListNode(1);
//   head1->next = new ListNode(4);
//   head1->next->next = new ListNode(5);
//   ListNode *head2 = new ListNode(1);
//   head2->next = new ListNode(3);
//   head2->next->next = new ListNode(4);
//   ListNode *head3 = new ListNode(2);
//   head3->next = new ListNode(6);
//   std::vector<ListNode*> vec = {head1, head2, head3};
//   auto result = test.mergeKLists(vec);
//   while (result != nullptr) {
//     std::cout << result->val << ' ';
//     result = result->next;
//   }
//   std::cout << '\n';
// }

static const auto io_sync_off =
  []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return nullptr;
  }();

#include "include/predefined.hpp"
#include "57/57.hpp"

int main() {
  std::vector<Interval> intervals = {Interval(1, 2), Interval(3, 5),
                                     Interval(6, 7), Interval(8, 10),
                                     Interval(12, 16)};
  // std::vector<Interval> intervals = {};
  // std::vector<Interval> intervals = {Interval(1, 4)};
  Interval newInterval(4, 8);
  Solution test;
  auto vec = test.insert(intervals, newInterval);
  for (auto &v : vec) {
    std::cout << v.start << ' ' << v.end << '\n';
  }
}
