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

#include "include/predefined.hpp"
#include "113/113.cpp"
int main() {
  Solution test;
  //  TreeNode *root = nullptr;
  TreeNode *root = new TreeNode(1);
  TreeNode *root_right = new TreeNode(2);
  TreeNode *root_right_left = new TreeNode(3);
  root->right = root_right;
  root->right->left = root_right_left;

  auto targets = test.pathSum(root, 6);

  for (const auto & target : targets) {
    for (const auto & num : target) {
      std::cout << num << ' ';
    }
    std::cout << '\n';
  }

}
